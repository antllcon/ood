#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <memory>
#include <set>

#include "Observer.h"
#include "WeatherData.h"

class CTestRemoveObserver : public IObserver<SWeatherInfo>
	, public std::enable_shared_from_this<CTestRemoveObserver>
{
public:
	CTestRemoveObserver(CObservable<SWeatherInfo>& observable)
		: m_observable(observable)
	{
	}

	void Update(SWeatherInfo const& data) override
	{
		m_observable.RemoveObserver(shared_from_this());
		updated = true;
	}

	bool updated = false;

private:
	CObservable<SWeatherInfo>& m_observable;
};

TEST(WeatherStationTest, ObserverCanRemoveItselfSafely)
{
	CWeatherData wd;

	auto obs1 = std::make_shared<CTestRemoveObserver>(wd);
	auto obs2 = std::make_shared<CDisplay>();

	wd.RegisterObserver(obs1);
	wd.RegisterObserver(obs2);

	wd.SetMeasurements(25.0, 0.6, 750);
	EXPECT_TRUE(obs1->updated);

	obs1->updated = false;

	wd.SetMeasurements(30.0, 0.7, 755);
	EXPECT_FALSE(obs1->updated);
}
