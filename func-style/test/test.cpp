#include "Duck/DecoyDuck.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Duck/Duck.h"
#include "Duck/Fly/FlyNoWay.h"
#include "Duck/Quack/MuteQuack.h"

using namespace testing;

class MockFlyBehavior : public IFlyBehavior
{
public:
	MOCK_METHOD(void, Fly, (), (override));
	MOCK_METHOD(size_t, GetFlyCount, (), (const override));
};

class MockQuackBehavior : public IQuackBehavior
{
public:
	MOCK_METHOD(void, Quack, (), (override));
	MOCK_METHOD(bool, CanQuack, (), (const override));
};

class MockDanceBehavior : public IDanceBehavior
{
public:
	MOCK_METHOD(void, Dance, (), (override));
};

class MockDuck : public Duck
{
public:
	MockDuck(std::unique_ptr<IFlyBehavior>&& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quackBehavior,
		std::unique_ptr<IDanceBehavior>&& danceBehavior)
		: Duck(std::move(flyBehavior), std::move(quackBehavior), std::move(danceBehavior))
	{
	}

	MOCK_METHOD(void, Display, (), (const, override));
};

TEST(DuckTest, FlyingDuckQuacksAfterEverySecondFlight)
{
	auto flyBehavior = std::make_unique<NiceMock<MockFlyBehavior>>();
	auto quackBehavior = std::make_unique<NiceMock<MockQuackBehavior>>();
	auto danceBehavior = std::make_unique<NiceMock<MockDanceBehavior>>();

	EXPECT_CALL(*quackBehavior, CanQuack())
		.WillRepeatedly(Return(true));

	ON_CALL(*flyBehavior, GetFlyCount())
		.WillByDefault(Invoke([]() {
			static size_t count = 0;
			return count++;
		}));

	EXPECT_CALL(*quackBehavior, Quack())
		.Times(2);

	MockDuck duck(std::move(flyBehavior), std::move(quackBehavior), std::move(danceBehavior));

	duck.Fly();
	duck.Fly();
	duck.Fly();
}

int main(int argc, char** argv)
{
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}