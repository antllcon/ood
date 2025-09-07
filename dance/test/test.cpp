#include "Duck/DecoyDuck.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Duck/Dance/IDanceBehavior.h"
#include "Duck/Duck.h"
#include "Duck/Fly/FlyNoWay.h"
#include "Duck/Quack/MuteQuack.h"

class MockDanceBehavior : public IDanceBehavior
{
public:
	MOCK_METHOD(void, Dance, (), (override));
};

// TODO: можно ли лучше?
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

TEST(DanceMockTest, CheckCall)
{
	auto mockDanceBehavior = std::make_unique<MockDanceBehavior>();
	MockDanceBehavior* mockPtr = mockDanceBehavior.get();

	EXPECT_CALL(*mockPtr, Dance()).Times(1);

	MockDuck duck(std::make_unique<FlyNoWay>(),
		std::make_unique<MuteQuack>(),
		std::move(mockDanceBehavior));

	duck.Dance();
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}