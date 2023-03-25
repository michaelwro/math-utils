/**
 * @file test_Quaternion.cpp
 * @author Michael Wrona
 * @date 2023-03-10
 */

#include "Attitude/Quaternion.h"
#include "LinAlg/Vector.h"
#include "TestTools/VectorNear.h"

#include <cmath>
#include <gtest/gtest.h>
#include <initializer_list>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

using MathUtils::Quaternion;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-Quaternion.xml");

// ====================================================================================================================
TEST(QuaternionTest, DefaultCtorIsUnityQuaternion)
{
  Quaternion quat;

  EXPECT_DOUBLE_EQ(quat(0), 1.0);
  EXPECT_DOUBLE_EQ(quat(1), 0.0);
  EXPECT_DOUBLE_EQ(quat(2), 0.0);
  EXPECT_DOUBLE_EQ(quat(3), 0.0);
}

// ====================================================================================================================
TEST(QuaternionTest, FourArgCtorNormalizes)
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
TEST(QuaternionTest, ListInitCtorNormalizes)
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
TEST(QuaternionTest, CtorThrowsInvalidLengthInitializerList)
{
  std::initializer_list<double> vals = {1, 2, 3};

  EXPECT_THROW({
    Quaternion quat(vals);
  }, std::length_error);
}

// ====================================================================================================================
TEST(QuaternionTest, CopyConstruct)
{
  Quaternion q1 {1, 1, 1, 1};
  Quaternion q2(q1);

  EXPECT_DOUBLE_EQ(q1(0), q2(0));
  EXPECT_DOUBLE_EQ(q1(1), q2(1));
  EXPECT_DOUBLE_EQ(q1(2), q2(2));
  EXPECT_DOUBLE_EQ(q1(3), q2(3));
}

// ====================================================================================================================
TEST(QuaternionTest, CopyAssign)
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
TEST(QuaternionTest, MoveAssign)
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
TEST(QuaternionTest, MoveConstruct)
{
  const Quaternion q1 {1, 1, 1, 1};
  const Quaternion q1_copy(q1);
  const Quaternion q2(std::move(q1));

  EXPECT_DOUBLE_EQ(q1_copy(0), q2(0));
  EXPECT_DOUBLE_EQ(q1_copy(1), q2(1));
  EXPECT_DOUBLE_EQ(q1_copy(2), q2(2));
  EXPECT_DOUBLE_EQ(q1_copy(3), q2(3));
}

// ====================================================================================================================
TEST(QuaternionTest, InitializerListAssign)
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
TEST(QuaternionDeathTest, InvalidIndexAsserts)
{
  EXPECT_DEBUG_DEATH({
    Quaternion quat;
    quat(4);
  }, "");
}

// ====================================================================================================================
TEST(QuaternionTest, InvalidLengthAssignmentThrows)
{
  std::initializer_list<double> vals = {1, 2, 3};

  EXPECT_THROW({
    Quaternion quat;
    quat = vals;
  }, std::length_error);
}

// ====================================================================================================================
TEST(QuaternionTest, Conjugate)
{
  Quaternion q(0.5, 0.5, -0.5, -0.5);

  Quaternion qt = q.conjugate();

  EXPECT_DOUBLE_EQ(0.5, qt(0));
  EXPECT_DOUBLE_EQ(-0.5, qt(1));
  EXPECT_DOUBLE_EQ(0.5, qt(2));
  EXPECT_DOUBLE_EQ(0.5, qt(3));
}

// ====================================================================================================================
TEST(QuaternionTest, Invert)
{
  Quaternion q(-0.5, -0.5, -0.5, 0.5);

  q.invert();

  EXPECT_DOUBLE_EQ(-0.5, q(0));
  EXPECT_DOUBLE_EQ(0.5, q(1));
  EXPECT_DOUBLE_EQ(0.5, q(2));
  EXPECT_DOUBLE_EQ(-0.5, q(3));
}

// ====================================================================================================================
TEST(QuaternionTest, ForcePositiveRotation)
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
TEST(QuaternionDeathTest, ZeroMagnitudeAsserts)
{
  EXPECT_DEBUG_DEATH({
    Quaternion q(0,0,0,0);
  }, "");
}

// ====================================================================================================================
TEST(QuaternionTest, EigenAxis)
{
  const double sqrt_two = std::sqrt(2.0);

  Quaternion q(1.0/sqrt_two, 1.0/sqrt_two, 0, 0);

  EXPECT_TRUE(MathUtils::TestTools::VectorNear(q.eigen_axis(), MathUtils::Vector<3>{1, 0, 0}));
}

// ====================================================================================================================
TEST(QuaternionDeathTest, AssertZeroAngleEigenAxis)
{
  EXPECT_DEBUG_DEATH({
    Quaternion q(1, 0, 0, 0);
    q.eigen_axis();
  }, "");
}

// ====================================================================================================================
TEST(QuaternionTest, PrintToStream)
{
  Quaternion q {1, 2, 3, 4};

  std::stringstream ss;
  ss << q << "\n";

  EXPECT_TRUE(ss.str().find("0.18") != std::string::npos);
  EXPECT_TRUE(ss.str().find("0.36") != std::string::npos);
  EXPECT_TRUE(ss.str().find("0.54") != std::string::npos);
  EXPECT_TRUE(ss.str().find("0.73") != std::string::npos);
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
