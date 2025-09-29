#include "Duck/DecoyDuck.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Duck/Dance/DanceMinuet.h"
#include "Duck/Dance/IDanceBehavior.h"
#include "Duck/Duck.h"
#include "Duck/Fly/FlyNoWay.h"
#include "Duck/Quack/MuteQuack.h"

class MockDanceBehavior : public IDanceBehavior
{
public:
	MOCK_METHOD(void, Dance, (), (override));
};

class MockDanceMinuet : public IDanceBehavior
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

TEST(DanceMockTest, CheckCallDance)
{
	auto mockDanceBehavior = std::make_unique<MockDanceBehavior>();
	MockDanceBehavior* mockPtr = mockDanceBehavior.get();

	EXPECT_CALL(*mockPtr, Dance()).Times(1);

	MockDuck duck(std::make_unique<FlyNoWay>(),
		std::make_unique<MuteQuack>(),
		std::move(mockDanceBehavior));

	duck.Dance();
}

TEST(DuckMockTest, CheckCallDanceDouble)
{
	auto mockDanceBehavior1 = std::make_unique<MockDanceBehavior>();
	auto mockDanceBehavior2 = std::make_unique<MockDanceMinuet>();

	MockDanceBehavior* mockPtr1 = mockDanceBehavior1.get();
	MockDanceMinuet* mockPtr2 = mockDanceBehavior2.get();

	EXPECT_CALL(*mockPtr1, Dance()).Times(1);
	EXPECT_CALL(*mockPtr2, Dance()).Times(1);

	MockDuck duck(std::make_unique<FlyNoWay>(),
		std::make_unique<MuteQuack>(),
		std::move(mockDanceBehavior1));

	duck.Dance();
	duck.SetDanceBehavior(std::move(mockDanceBehavior2));
	duck.Dance();
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}