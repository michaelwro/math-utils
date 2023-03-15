/**
 * @file test_Quaternion.cpp
 * @author Michael Wrona
 * @date 2023-03-10
 * @brief Quaternion class unit tests.
 */

#include "Attitude/Quaternion.h"

#include <cmath>
#include <gtest/gtest.h>
#include <initializer_list>
#include <string>
#include <utility>

using MathUtils::Quaternion;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-Quaternion.xml");

// ====================================================================================================================
TEST(Attitude_Quaternion, DefaultConstructorIsUnityQuaternion)
{
  Quaternion quat;

  EXPECT_DOUBLE_EQ(quat(0), 1.0);
  EXPECT_DOUBLE_EQ(quat(1), 0.0);
  EXPECT_DOUBLE_EQ(quat(2), 0.0);
  EXPECT_DOUBLE_EQ(quat(3), 0.0);
}

// ====================================================================================================================
TEST(Attitude_Quaternion, FourArgConstructionNormalizes)
{
  const double val = 1.0;
  const double magn = std::sqrt(4.0 * val * val);

  Quaternion quat(val, val, val, val);

  EXPECT_DOUBLE_EQ(quat(0), val / magn);
  EXPECT_DOUBLE_EQ(quat(1), val / magn);
  EXPECT_DOUBLE_EQ(quat(2), val / magn);
  EXPECT_DOUBLE_EQ(quat(3), val / magn);

}

// ====================================================================================================================
TEST(Attitude_Quaternion, ListInitConstructionNormalizes)
{
  const double val = 1.0;
  const double magn = std::sqrt(4.0 * val * val);

  Quaternion quat({val, val, val, val});

  EXPECT_DOUBLE_EQ(quat(0), val / magn);
  EXPECT_DOUBLE_EQ(quat(1), val / magn);
  EXPECT_DOUBLE_EQ(quat(2), val / magn);
  EXPECT_DOUBLE_EQ(quat(3), val / magn);
}

// ====================================================================================================================
TEST(Attitude_Quaternion, AssertsInvalidLengthInitializerList)
{
  std::initializer_list<double> vals = {1, 2, 3};

  ASSERT_DEBUG_DEATH({
    Quaternion quat(vals);
  }, "");
}

// ====================================================================================================================
TEST(Attitude_Quaternion, CopyConstructs)
{
  Quaternion q1 {1, 1, 1, 1};
  Quaternion q2(q1);

  EXPECT_DOUBLE_EQ(q1(0), q2(0));
  EXPECT_DOUBLE_EQ(q1(1), q2(1));
  EXPECT_DOUBLE_EQ(q1(2), q2(2));
  EXPECT_DOUBLE_EQ(q1(3), q2(3));
}

// ====================================================================================================================
TEST(Attitude_Quaternion, CopyAssigns)
{
  Quaternion q1 {1, 1, 1, 1};
  Quaternion q2;

  q2 = q1;

  EXPECT_DOUBLE_EQ(q1(0), q2(0));
  EXPECT_DOUBLE_EQ(q1(1), q2(1));
  EXPECT_DOUBLE_EQ(q1(2), q2(2));
  EXPECT_DOUBLE_EQ(q1(3), q2(3));
}

// ====================================================================================================================
TEST(Attitude_Quaternion, MoveAssigns)
{
  const double val = 1.0;
  const double magn = std::sqrt(4.0 * val * val);

  Quaternion q1 {val, val, val, val};
  Quaternion q2;

  q2 = std::move(q1);

  EXPECT_DOUBLE_EQ(q2(0), val / magn);
  EXPECT_DOUBLE_EQ(q2(1), val / magn);
  EXPECT_DOUBLE_EQ(q2(2), val / magn);
  EXPECT_DOUBLE_EQ(q2(3), val / magn);
}

// ====================================================================================================================
TEST(Attitude_Quaternion, InitializerListAssigns)
{
  const double val = 1.0;
  const double magn = std::sqrt(4.0 * val * val);

  Quaternion quat;
  quat = {val, val, val, val};

  EXPECT_DOUBLE_EQ(quat(0), val / magn);
  EXPECT_DOUBLE_EQ(quat(1), val / magn);
  EXPECT_DOUBLE_EQ(quat(2), val / magn);
  EXPECT_DOUBLE_EQ(quat(3), val / magn);
}

// ====================================================================================================================
TEST(Attitude_Quaternion, AssertsInvalidLengthInitializerListAssignment)
{
  std::initializer_list<double> vals = {1, 2, 3};

  ASSERT_DEBUG_DEATH({
    Quaternion quat;
    quat = vals;
  }, "");
}

// ====================================================================================================================
TEST(Attitude_Quaternion, Conjugate)
{
  Quaternion q(0.5, 0.5, -0.5, -0.5);

  Quaternion qt = q.conjugate();

  EXPECT_DOUBLE_EQ(0.5, qt(0));
  EXPECT_DOUBLE_EQ(-0.5, qt(1));
  EXPECT_DOUBLE_EQ(0.5, qt(2));
  EXPECT_DOUBLE_EQ(0.5, qt(3));
}

// ====================================================================================================================
TEST(Attitude_Quaternion, Invert)
{
  Quaternion q(-0.5, -0.5, -0.5, 0.5);

  q.invert();

  EXPECT_DOUBLE_EQ(-0.5, q(0));
  EXPECT_DOUBLE_EQ(0.5, q(1));
  EXPECT_DOUBLE_EQ(0.5, q(2));
  EXPECT_DOUBLE_EQ(-0.5, q(3));
}

// ====================================================================================================================
TEST(Attitude_Quaternion, ForcePositiveRotation)
{
  const double val = 1.0;
  const double magn = std::sqrt(4.0 * val * val);

  Quaternion quat(-val, val, val, val);
  quat.force_positive_rotation();

  EXPECT_DOUBLE_EQ(quat(0), val / magn);
  EXPECT_DOUBLE_EQ(quat(1), -val / magn);
  EXPECT_DOUBLE_EQ(quat(2), -val / magn);
  EXPECT_DOUBLE_EQ(quat(3), -val / magn);
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
