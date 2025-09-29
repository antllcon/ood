#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "WeatherData.h"

using namespace ::testing;

class MockObserver : public IObserver<SWeatherInfo>
{
public:
	MockObserver(const std::string& name)
		: m_name(name)
	{
	}

	MOCK_METHOD(void, Update, (SWeatherInfo const& data), (override));
	const std::string& GetName() const
	{
		return m_name;
	}

private:
	std::string m_name;
};

class MockWeatherData : public CObservable<SWeatherInfo>
{
public:
	void SetData(double temp, double humidity, double pressure)
	{
		m_info.temperature = temp;
		m_info.humidity = humidity;
		m_info.pressure = pressure;
		NotifyObservers();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		return m_info;
	}

private:
	SWeatherInfo m_info = {0, 0, 0};
};

struct ObserverPriorityTest : Test
{
	MockWeatherData subject;
	SWeatherInfo testData = {25.0, 60.0, 760.0};
};

// Тестирование оповещения в порядке убывания приоритета
TEST_F(ObserverPriorityTest, NotifyObserversByPriority)
{
	InSequence s;

	auto obsHigh = std::make_shared<MockObserver>("High");
	auto obsMedium = std::make_shared<MockObserver>("Medium");
	auto obsLow = std::make_shared<MockObserver>("Low");
	auto obsDefault = std::make_shared<MockObserver>("Default");

	subject.RegisterObserver(obsMedium, 50);
	subject.RegisterObserver(obsHigh, 100);
	subject.RegisterObserver(obsDefault);
	subject.RegisterObserver(obsLow, 10);

	EXPECT_CALL(*obsHigh, Update(Truly([&](const SWeatherInfo& data) {
		return data.temperature == testData.temperature;
	})));
	EXPECT_CALL(*obsMedium, Update(Truly([&](const SWeatherInfo& data) {
		return data.temperature == testData.temperature;
	})));
	EXPECT_CALL(*obsLow, Update(Truly([&](const SWeatherInfo& data) {
		return data.temperature == testData.temperature;
	})));
	EXPECT_CALL(*obsDefault, Update(Truly([&](const SWeatherInfo& data) {
		return data.temperature == testData.temperature;
	})));

	subject.SetData(testData.temperature, testData.humidity, testData.pressure);
}

// Тестирование оповещения для одинаковых приоритетов (порядок не гарантирован, но должны быть оповещены)
TEST_F(ObserverPriorityTest, NotifyObserversWithSamePriority)
{
	auto obsA = std::make_shared<MockObserver>("A");
	auto obsB = std::make_shared<MockObserver>("B");
	auto obsC = std::make_shared<MockObserver>("C");

	subject.RegisterObserver(obsA, 5);
	subject.RegisterObserver(obsC);
	subject.RegisterObserver(obsB, 5);

	EXPECT_CALL(*obsA, Update(_)).Times(1);
	EXPECT_CALL(*obsB, Update(_)).Times(1);
	EXPECT_CALL(*obsC, Update(_)).Times(1);

	subject.SetData(testData.temperature, testData.humidity, testData.pressure);
}

// Тестирование повторной регистрации
TEST_F(ObserverPriorityTest, RegisterObserverTwiceDoesNothing)
{
	auto obs = std::make_shared<MockObserver>("TestObs");

	subject.RegisterObserver(obs, 1);
	subject.RegisterObserver(obs, 5);

	EXPECT_CALL(*obs, Update(_)).Times(1);

	subject.SetData(testData.temperature, testData.humidity, testData.pressure);

	auto obsHigh = std::make_shared<MockObserver>("High");
	subject.RegisterObserver(obsHigh, 100);

	InSequence s;
	EXPECT_CALL(*obsHigh, Update(_));
	EXPECT_CALL(*obs, Update(_));

	subject.SetData(30.0, 70.0, 770.0);
}

// Тестирование снятия регистрации
TEST_F(ObserverPriorityTest, RemoveObserverWorks)
{
	auto obs1 = std::make_shared<MockObserver>("Obs1");
	auto obs2 = std::make_shared<MockObserver>("Obs2");

	subject.RegisterObserver(obs1, 10);
	subject.RegisterObserver(obs2, 50);

	subject.RemoveObserver(obs1);

	EXPECT_CALL(*obs1, Update(_)).Times(0);
	EXPECT_CALL(*obs2, Update(_)).Times(1);

	subject.SetData(testData.temperature, testData.humidity, testData.pressure);
}

// Тестирование снятия регистрации несуществующего наблюдателя
TEST_F(ObserverPriorityTest, RemoveNonExistingObserverDoesNothing)
{
	auto obs1 = std::make_shared<MockObserver>("Obs1");
	auto obsNonExisting = std::make_shared<MockObserver>("NonExisting");

	subject.RegisterObserver(obs1, 10);

	subject.RemoveObserver(obsNonExisting);

	EXPECT_CALL(*obs1, Update(_)).Times(1);
	subject.SetData(testData.temperature, testData.humidity, testData.pressure);
}

// Тестирование снятия регистрации и повторной регистрации
TEST_F(ObserverPriorityTest, RemoveAndRegisterAgain)
{
	InSequence s;

	auto obs = std::make_shared<MockObserver>("TestObs");
	auto obsLow = std::make_shared<MockObserver>("Low");

	subject.RegisterObserver(obs, 10);
	subject.RegisterObserver(obsLow, 5);

	EXPECT_CALL(*obs, Update(_));
	EXPECT_CALL(*obsLow, Update(_));
	subject.SetData(10, 10, 10);

	subject.RemoveObserver(obs);

	auto obsHigh = std::make_shared<MockObserver>("High");
	subject.RegisterObserver(obs, 100);
	subject.RegisterObserver(obsHigh, 50);

	EXPECT_CALL(*obs, Update(_));
	EXPECT_CALL(*obsHigh, Update(_));
	EXPECT_CALL(*obsLow, Update(_));
	subject.SetData(20, 20, 20);
}

// TEST_F(ObserverPriorityTest, NotifyDoesNotCallDeletedObserver)
//{
//	auto obs1 = std::make_shared<MockObserver>("Obs1");
//	auto obs2 = std::make_shared<MockObserver>("Obs2");
//
//	subject.RegisterObserver(obs1, 10);
//	subject.RegisterObserver(obs2, 5);
//
//	EXPECT_CALL(*obs1, Update(_)).Times(1);
//	EXPECT_CALL(*obs2, Update(_)).Times(1);
//	subject.SetData(1, 1, 1);
//
//	obs1.reset();
//
//	EXPECT_CALL(*obs2, Update(_)).Times(1);
//	subject.SetData(2, 2, 2);
// }
