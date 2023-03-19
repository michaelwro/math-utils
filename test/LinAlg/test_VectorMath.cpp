/**
 * @file test_VectorMath.cpp
 * @author Michael Wrona
 * @date 2023-03-10
 */

#include "LinAlg/Vector.h"

#include <cmath>
#include <gtest/gtest.h>
#include <initializer_list>
#include <string>
#include <utility>

using namespace MathUtils;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-VectorMath.xml");

class VectorMathTest : public ::testing::Test
{
protected:
  void SetUp() override
  {}

  void TearDown() override
  {}

  /*
    np.set_printoptions(precision=16)
    vec1 = np.array([1, 2, 3])
    vec2 = np.array([4, 5, 6])
    scalar = 4
   */
  const double scalar = 4;  ///< Scalar under test

  Vector<3> vec1 {1, 2, 3};  ///< Vector #1 under test
  const Vector<3> vec1_normalized {0.2672612419124244, 0.5345224838248488, 0.8017837257372732};
  const Vector<3> vec1_plus_scalar {5, 6, 7};
  const Vector<3> vec1_minus_scalar {-3, -2, -1};
  const Vector<3> vec1_times_scalar {4, 8, 12};
  const Vector<3> vec1_div_scalar {0.25, 0.5, 0.75};
  const double vec1_magnitude = std::sqrt(14.0);
  const double vec1_sum = 6.0;

  Vector<3> vec2 {4, 5, 6};  ///< Vector #2 under test
  const Vector<3> vec2_normalized {0.4558423058385518, 0.5698028822981898, 0.6837634587578276};
  const Vector<3> vec2_plus_scalar {8, 9, 10};
  const Vector<3> vec2_minus_scalar {0, 1, 2};
  const Vector<3> vec2_times_scalar {16, 20, 24};
  const Vector<3> vec2_div_scalar {1.0, 1.25, 1.5};
  const double vec2_magnitude = std::sqrt(77.0);
  const double vec2_sum = 15;

  const double vec1_dot_vec2 = 32;
  const Vector<3> vec1_cross_vec2 {-3, 6, -3};
  const Vector<3> vec1_plus_vec2 {5, 7, 9};
  const Vector<3> vec1_minus_vec2 {-3, -3, -3};
  const Vector<3> vec1_times_vec2 {4, 10, 18};
};


// ====================================================================================================================
TEST_F(VectorMathTest, Magnitude)
{
  double mag = vec1.magnitude();

  EXPECT_DOUBLE_EQ(mag, vec1_magnitude);
}

// ====================================================================================================================
TEST_F(VectorMathTest, Normalize)
{
  vec2.normalize();

  EXPECT_DOUBLE_EQ(vec2(0), vec2_normalized(0));
  EXPECT_DOUBLE_EQ(vec2(1), vec2_normalized(1));
  EXPECT_DOUBLE_EQ(vec2(2), vec2_normalized(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, SumElements)
{
  EXPECT_DOUBLE_EQ(vec1.sum(), vec1_sum);
}

// ====================================================================================================================
TEST_F(VectorMathTest, ScalarAddInPlace)
{
  vec2 += scalar;

  EXPECT_DOUBLE_EQ(vec2(0), vec2_plus_scalar(0));
  EXPECT_DOUBLE_EQ(vec2(1), vec2_plus_scalar(1));
  EXPECT_DOUBLE_EQ(vec2(2), vec2_plus_scalar(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, VectorAddInPlace)
{
  vec1 += vec2;

  EXPECT_DOUBLE_EQ(vec1(0), vec1_plus_vec2(0));
  EXPECT_DOUBLE_EQ(vec1(1), vec1_plus_vec2(1));
  EXPECT_DOUBLE_EQ(vec1(2), vec1_plus_vec2(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, ScalarSubtractInPlace)
{
  vec2 -= scalar;

  EXPECT_DOUBLE_EQ(vec2(0), vec2_minus_scalar(0));
  EXPECT_DOUBLE_EQ(vec2(1), vec2_minus_scalar(1));
  EXPECT_DOUBLE_EQ(vec2(2), vec2_minus_scalar(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, VectorSubtractInPlace)
{
  vec1 -= vec2;

  EXPECT_DOUBLE_EQ(vec1(0), vec1_minus_vec2(0));
  EXPECT_DOUBLE_EQ(vec1(1), vec1_minus_vec2(1));
  EXPECT_DOUBLE_EQ(vec1(2), vec1_minus_vec2(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, ScalarMultiplyInPlace)
{
  vec2 *= scalar;

  EXPECT_DOUBLE_EQ(vec2(0), vec2_times_scalar(0));
  EXPECT_DOUBLE_EQ(vec2(1), vec2_times_scalar(1));
  EXPECT_DOUBLE_EQ(vec2(2), vec2_times_scalar(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, ScalarDivideInPlace)
{
  vec1 /= scalar;

  EXPECT_DOUBLE_EQ(vec1(0), vec1_div_scalar(0));
  EXPECT_DOUBLE_EQ(vec1(1), vec1_div_scalar(1));
  EXPECT_DOUBLE_EQ(vec1(2), vec1_div_scalar(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, ScalarDivideInPlaceAssertsSmallNumber)
{
  EXPECT_DEBUG_DEATH({
    vec2 /= 0lu;
  }, "");
}

// ====================================================================================================================
TEST_F(VectorMathTest, Negate)
{
  Vector<3> vec1_before(vec1);

  vec1.negate();

  EXPECT_DOUBLE_EQ(vec1(0), -vec1_before(0));
  EXPECT_DOUBLE_EQ(vec1(1), -vec1_before(1));
  EXPECT_DOUBLE_EQ(vec1(2), -vec1_before(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, CrossProduct)
{
  const Vector<3> res = cross(vec1, vec2);

  EXPECT_DOUBLE_EQ(res(0), vec1_cross_vec2(0));
  EXPECT_DOUBLE_EQ(res(1), vec1_cross_vec2(1));
  EXPECT_DOUBLE_EQ(res(2), vec1_cross_vec2(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, DotProduct)
{
  const double res = dot(vec1, vec2);

  EXPECT_DOUBLE_EQ(res, vec1_dot_vec2);
}

// ====================================================================================================================
TEST_F(VectorMathTest, Add)
{
  Vector<3> res = vec1 + vec2;

  EXPECT_DOUBLE_EQ(res(0), vec1_plus_vec2(0));
  EXPECT_DOUBLE_EQ(res(1), vec1_plus_vec2(1));
  EXPECT_DOUBLE_EQ(res(2), vec1_plus_vec2(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, Subtract)
{
  const Vector<3> res = vec1 - vec2;

  EXPECT_DOUBLE_EQ(res(0), vec1_minus_vec2(0));
  EXPECT_DOUBLE_EQ(res(1), vec1_minus_vec2(1));
  EXPECT_DOUBLE_EQ(res(2), vec1_minus_vec2(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, VectorScalarMultiplication)
{
  const Vector<3> res = vec1 * scalar;

  EXPECT_DOUBLE_EQ(res(0), vec1_times_scalar(0));
  EXPECT_DOUBLE_EQ(res(1), vec1_times_scalar(1));
  EXPECT_DOUBLE_EQ(res(2), vec1_times_scalar(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, ScalarVectorMultiplication)
{
  const Vector<3> res = scalar * vec2;

  EXPECT_DOUBLE_EQ(res(0), vec2_times_scalar(0));
  EXPECT_DOUBLE_EQ(res(1), vec2_times_scalar(1));
  EXPECT_DOUBLE_EQ(res(2), vec2_times_scalar(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, Multiplication)
{
  const Vector<3> res = vec1 * vec2;

  EXPECT_DOUBLE_EQ(res(0), vec1_times_vec2(0));
  EXPECT_DOUBLE_EQ(res(1), vec1_times_vec2(1));
  EXPECT_DOUBLE_EQ(res(2), vec1_times_vec2(2));
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
