#include "Observer.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <string>
#include <vector>

class TestSubject : public CObservable<int>
{
public:
	void ChangeData(int newData)
	{
		m_data = newData;
		NotifyObservers();
	}

protected:
	int GetChangedData() const override
	{
		return m_data;
	}

private:
	int m_data = 0;
};

class MockObserver : public IObserver<int>
{
public:
	MockObserver(const int id, std::vector<int>& notificationOrder)
		: m_id(id)
		, m_notificationOrder(notificationOrder)
	{
	}

	void Update(int const& data) override
	{
		m_notificationOrder.emplace_back(m_id);
		m_updateCount++;
	}

	int getUpdateCount() const
	{
		return m_updateCount;
	}

private:
	int m_id;
	std::vector<int>& m_notificationOrder;
	int m_updateCount = 0;
};

class ObserverPatternTest : public ::testing::Test
{
protected:
	TestSubject subject;
	std::vector<int> notificationOrder;
};

TEST_F(ObserverPatternTest, NotifiesObserversInPriorityOrder)
{
	auto obs1 = std::make_shared<MockObserver>(1, notificationOrder);
	auto obs2 = std::make_shared<MockObserver>(2, notificationOrder);
	auto obs3 = std::make_shared<MockObserver>(3, notificationOrder);

	subject.RegisterObserver(obs1, 0);
	subject.RegisterObserver(obs2, 100);
	subject.RegisterObserver(obs3, 10);

	// Для чего
	subject.ChangeData(1337);

	std::vector<int> expectedOrder = {2, 3, 1};
	ASSERT_EQ(notificationOrder, expectedOrder);
}

TEST_F(ObserverPatternTest, IgnoresDuplicateRegistration)
{
	auto obs1 = std::make_shared<MockObserver>(1, notificationOrder);

	subject.RegisterObserver(obs1, 50);
	subject.RegisterObserver(obs1, 100);

	subject.ChangeData(1337);

	ASSERT_EQ(obs1->getUpdateCount(), 1);
	ASSERT_EQ(notificationOrder.size(), 1);
}

TEST_F(ObserverPatternTest, CorrectlyRemovesObserver)
{
	auto obs1 = std::make_shared<MockObserver>(1, notificationOrder);
	auto obs2 = std::make_shared<MockObserver>(2, notificationOrder);

	subject.RegisterObserver(obs1, 1);
	subject.RegisterObserver(obs2, 2);

	subject.RemoveObserver(obs1);
	subject.ChangeData(1337);

	std::vector<int> expectedOrder = {2};
	ASSERT_EQ(notificationOrder, expectedOrder);
}

TEST_F(ObserverPatternTest, HandlesObserverDestructionSafely)
{
	auto persistentObs = std::make_shared<MockObserver>(1, notificationOrder);
	subject.RegisterObserver(persistentObs, 10);

	{
		auto tempObs = std::make_shared<MockObserver>(99, notificationOrder);
		subject.RegisterObserver(tempObs, 100);
	}

	EXPECT_NO_THROW(subject.ChangeData(1337));

	std::vector<int> expectedOrder = {1};
	ASSERT_EQ(notificationOrder, expectedOrder);
}
