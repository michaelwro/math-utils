/**
 * @file quaternion_to_euler_test.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "Attitude/Euler321.h"
#include "Attitude/quaternion_to_euler.h"
#include "Attitude/Quaternion.h"
#include "conversions.h"
#include "TestTools/Euler321Near.h"

#include <cmath>
#include <gtest/gtest.h>
#include <string>

using MathUtils::Conversions::deg2rad;
using MathUtils::Euler321;
using MathUtils::quaternion_to_euler;
using MathUtils::Quaternion;
using MathUtils::TestTools::Euler321Near;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-quaternion_to_euler.xml");

// =================================================================================================
TEST(QuaternionToEulerTest, RollOnly)
{
    // roll about x-axis
    const double angle = deg2rad(15.0);

    const double angle_div2 = 0.5 * angle;
    const Quaternion q {std::cos(angle_div2), 1.0*std::sin(angle_div2), 0.0, 0.0};
    const Euler321 expected(0.0, 0.0, angle);

    const Euler321 result = quaternion_to_euler(q);

    EXPECT_TRUE(Euler321Near(result, expected, 1e-8));
}

// =================================================================================================
TEST(QuaternionToEulerTest, PitchOnly)
{
    // pitch about y-axis
    const double angle = deg2rad(-32.0);

    const double angle_div2 = 0.5 * angle;
    const Quaternion q {std::cos(angle_div2), 0.0, 1.0*std::sin(angle_div2), 0.0};
    const Euler321 expected(0.0, angle, 0.0);

    const Euler321 result = quaternion_to_euler(q);

    EXPECT_TRUE(Euler321Near(result, expected, 1e-8));
}

// =================================================================================================
TEST(QuaternionToEulerTest, YawOnly)
{
    // yaw about z-axis
    const double angle = deg2rad(-170.0);

    const double angle_div2 = 0.5 * angle;
    Quaternion q {std::cos(angle_div2), 0.0, 0.0, 1.0*std::sin(angle_div2)};

    const Euler321 expected(angle, 0.0, 0.0);

    const Euler321 result = quaternion_to_euler(q);

    EXPECT_TRUE(Euler321Near(result, expected, 1e-8));
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
