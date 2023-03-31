/**
 * @file test_quaternion_rotate.cpp
 * @author Michael Wrona
 * @date 2023-03-15
 */

#include "Attitude/Quaternion.h"
#include "Attitude/quaternion_rotate.h"
#include "LinAlg/Vector.h"
#include "TestTools/VectorNear.h"

#include <cmath>
#include <gtest/gtest.h>
#include <string>

using MathUtils::Quaternion;
using MathUtils::TestTools::VectorNear;
using MathUtils::Vector;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-quaternion_rotate.xml");

// =================================================================================================
TEST(QuaternionRotateTest, QuaternionRotate1)
{
    // Example 3.6 from "Analytical Mechanics of Aerospace Systems"
    Quaternion q_a_b({0.961798, -0.14565, 0.202665, 0.112505});
    Vector<3> v_b({1, -3, 2});

    Vector<3> v_a = MathUtils::quaternion_rotate(q_a_b, v_b);

    const double tol = 1e-6;

    const Vector<3> expected {-0.42483130, -3.54136228, 1.13060413};
    EXPECT_TRUE(VectorNear(v_a, expected, tol));
}

// =================================================================================================
TEST(QuaternionRotateTest, QuaternionRotate2)
{
    // https://www.mathworks.com/help/aerotbx/ug/quat2dcm.html
    Quaternion q_a_b({1, 0, 1, 0});
    Vector<3> v_b({1, -3, 2});

    Vector<3> v_a = MathUtils::quaternion_rotate(q_a_b, v_b);

    const Vector<3> expected {-2, -3, 1};
    EXPECT_TRUE(VectorNear(v_a, expected));
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
