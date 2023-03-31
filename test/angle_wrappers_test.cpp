/**
 * @file test_angle_wrappers.cpp
 * @author Michael Wrona
 * @date 2023-03-29
 */

#include "constants.h"
#include "wrap_pi.h"
#include "wrap_2pi.h"

#include <gtest/gtest.h>
#include <string>

using namespace MathUtils::Constants;
using MathUtils::wrap_pi;
using MathUtils::wrap_2pi;

namespace {

constexpr double TOL = 1e-12;  // abs tolerance

const std::string test_reports_file = std::string("TESTRESULTS-angle_wrappers.xml");

// =================================================================================================
TEST(AngleWrappersTest, wrapPiTest1)
{
  EXPECT_NEAR(wrap_pi(PI_DIV2 + (3.0 * TWO_PI)), PI_DIV2, TOL);
}

// =================================================================================================
TEST(AngleWrappersTest, wrapPiTest2)
{
  EXPECT_NEAR(wrap_pi(PI_DIV2 - (3.0 * TWO_PI)), PI_DIV2, TOL);
}

// =================================================================================================
TEST(AngleWrappersTest, wrapPiTest3)
{
  EXPECT_NEAR(wrap_pi(-PI_DIV2), -PI_DIV2, TOL);
}

// =================================================================================================
TEST(AngleWrappersTest, wrapPiTest4)
{
  EXPECT_NEAR(wrap_pi(PI_DIV4), PI_DIV4, TOL);
}

// =================================================================================================
TEST(AngleWrappersTest, wrap2PiTest1)
{
  EXPECT_NEAR(wrap_2pi(PI_DIV4), PI_DIV4, TOL);
}

// =================================================================================================
TEST(AngleWrappersTest, wrap2PiTest2)
{
  EXPECT_NEAR(wrap_2pi(-PI_DIV2), 3.0*PI_DIV2, TOL);
}

// =================================================================================================
TEST(AngleWrappersTest, wrap2PiTest3)
{
  EXPECT_NEAR(wrap_2pi(PI_DIV2 + (3.0 * TWO_PI)), PI_DIV2, TOL);
}

// =================================================================================================
TEST(AngleWrappersTest, wrap2PiTest4)
{
  EXPECT_NEAR(wrap_2pi(-PI_DIV2 - (3.0 * TWO_PI)), 3.0 * PI_DIV2, TOL);
}

// =================================================================================================
int main(int argc, char** argv)
{
  ::testing::GTEST_FLAG(output) = std::string("xml:") + test_reports_file;
  ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}  // namespace
