#include "Observer.h"
#include "Statistics.h"
#include "gtest/gtest.h"

TEST(WindDirectionTest, CalculatesCorrectAverage)
{
	CWindDirectionCounter counter1;
	counter1.Update(80.0);
	counter1.Update(100.0);
	EXPECT_NEAR(counter1.GetAverage(), 90.0, std::numeric_limits<double>::epsilon());

	CWindDirectionCounter counter2;
	counter2.Update(260.0);
	counter2.Update(280.0);
	EXPECT_NEAR(counter2.GetAverage(), 270.0, std::numeric_limits<double>::epsilon());

	CWindDirectionCounter counter3;
	counter3.Update(359.0);
	counter3.Update(1.0);
	EXPECT_NEAR(counter3.GetAverage(), 360.0, std::numeric_limits<double>::epsilon());

	CWindDirectionCounter counter4;
	counter4.Update(179.0);
	counter4.Update(181.0);
	EXPECT_NEAR(counter4.GetAverage(), 180.0, std::numeric_limits<double>::epsilon());

	CWindDirectionCounter counter5;
	counter5.Update(89.0);
	counter5.Update(91.0);
	EXPECT_NEAR(counter5.GetAverage(), 90.0, std::numeric_limits<double>::epsilon());
}
