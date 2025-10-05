#include "Observer.h"
#include "Statistics.h"
#include "gtest/gtest.h"
#include <Displays.h>

TEST(WindDirectionTest, CalculatesCorrectAverage)
{
	CWindDirectionCounter counter3;
	counter3.Update(80.0);
	counter3.Update(100.0);
	EXPECT_NEAR(counter3.GetAverage(), 90.0, std::numeric_limits<double>::epsilon());

	CWindDirectionCounter counter4;
	counter4.Update(260.0);
	counter4.Update(280.0);
	EXPECT_NEAR(counter4.GetAverage(), 270.0, std::numeric_limits<double>::epsilon());
}
