#include "Observer.h"
#include "WeatherData.h"
#include "gtest/gtest.h"

#include <map>
#include <string>
#include <vector>

class MockMultiSubjectObserver : public IObserver<SWeatherInfo>
{
public:
	void Update(const SWeatherInfo& data, IObservable<SWeatherInfo>* subject) override
	{
		receivedData[subject].emplace_back(data);
	}

	std::map<IObservable<SWeatherInfo>*, std::vector<SWeatherInfo>> receivedData;
};

class MultiSubjectObserverTest : public ::testing::Test
{
protected:
	CWeatherData indoorStation{"Indoor"};
	CWeatherData outdoorStation{"Outdoor"};

	std::shared_ptr<MockMultiSubjectObserver> observer;

	void SetUp() override
	{
		observer = std::make_shared<MockMultiSubjectObserver>();
		indoorStation.RegisterObserver(observer, 10);
		outdoorStation.RegisterObserver(observer, 20);
	}
};

TEST_F(MultiSubjectObserverTest, ReceivesNotificationsFromMultipleSubjects)
{
	indoorStation.SetMeasurements(20, 50, 750);
	outdoorStation.SetMeasurements(5, 90, 740);

	ASSERT_TRUE(observer->receivedData.count(&indoorStation));
	ASSERT_TRUE(observer->receivedData.count(&outdoorStation));

	ASSERT_EQ(observer->receivedData[&indoorStation].size(), 1);
	ASSERT_EQ(observer->receivedData[&outdoorStation].size(), 1);
}

TEST_F(MultiSubjectObserverTest, DistinguishesNotificationSources)
{
	indoorStation.SetMeasurements(22, 55, 752);
	outdoorStation.SetMeasurements(7, 85, 745);

	ASSERT_EQ(observer->receivedData[&indoorStation][0].temperature, 22);
	ASSERT_EQ(observer->receivedData[&indoorStation][0].humidity, 55);
	ASSERT_EQ(observer->receivedData[&indoorStation][0].stationName, "Indoor");

	ASSERT_EQ(observer->receivedData[&outdoorStation][0].temperature, 7);
	ASSERT_EQ(observer->receivedData[&outdoorStation][0].humidity, 85);
	ASSERT_EQ(observer->receivedData[&outdoorStation][0].stationName, "Outdoor");
}

TEST_F(MultiSubjectObserverTest, UpdatingOneStationDoesNotAffectOther)
{
	indoorStation.SetMeasurements(20, 50, 750);
	outdoorStation.SetMeasurements(5, 90, 740);

	indoorStation.SetMeasurements(21, 51, 751);

	ASSERT_EQ(observer->receivedData[&indoorStation].size(), 2);
	ASSERT_EQ(observer->receivedData[&indoorStation][1].temperature, 21);

	ASSERT_EQ(observer->receivedData[&outdoorStation].size(), 1);
	ASSERT_EQ(observer->receivedData[&outdoorStation][0].temperature, 5);
}

TEST_F(MultiSubjectObserverTest, CorrectlyRemovesObserverFromOneSubject)
{
	indoorStation.RemoveObserver(observer);

	indoorStation.SetMeasurements(23, 58, 755);
	outdoorStation.SetMeasurements(8, 88, 748);

	ASSERT_EQ(observer->receivedData[&indoorStation].size(), 0);

	ASSERT_EQ(observer->receivedData[&outdoorStation].size(), 1);
	ASSERT_EQ(observer->receivedData[&outdoorStation][0].temperature, 8);
}
