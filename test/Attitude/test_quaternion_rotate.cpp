/**
 * @file test_quaternion_rotate.cpp
 * @author Michael Wrona
 * @date 2023-03-15
 */

#include "Attitude/Quaternion.h"
#include "Attitude/quaternion_rotate.h"
#include "LinAlg/Vector.h"

#include <cmath>
#include <gtest/gtest.h>
#include <string>

using namespace MathUtils;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-quaternion_rotate.xml");

// ====================================================================================================================
TEST(QuaternionRotateTest, QuaternionRotate1)
{
  // Example 3.6 from "Analytical Mechanics of Aerospace Systems"
  Quaternion q_a_b({0.961798, -0.14565, 0.202665, 0.112505});
  Vector<3> v_b({1, -3, 2});

  Vector<3> v_a = quaternion_rotate(q_a_b, v_b);

  const double tol = 1e-6;

  EXPECT_NEAR(v_a(0), -0.42483130, tol);
  EXPECT_NEAR(v_a(1), -3.54136228, tol);
  EXPECT_NEAR(v_a(2), 1.13060413, tol);
}

// ====================================================================================================================
TEST(QuaternionRotateTest, QuaternionRotate2)
{
  // https://www.mathworks.com/help/aerotbx/ug/quat2dcm.html
  Quaternion q_a_b({1, 0, 1, 0});
  Vector<3> v_b({1, -3, 2});

  Vector<3> v_a = quaternion_rotate(q_a_b, v_b);

  EXPECT_DOUBLE_EQ(v_a(0), -2);
  EXPECT_DOUBLE_EQ(v_a(1), -3);
  EXPECT_DOUBLE_EQ(v_a(2), 1);
}


// ====================================================================================================================
int main(int argc, char** argv)
{
  ::testing::GTEST_FLAG(output) = std::string("xml:") + test_reports_file;
  ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}  // namespace
