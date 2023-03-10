/**
 * @file test_VectorMath.cpp
 * @author Michael Wrona
 * @date 2023-03-10
 * @brief Vector math unit tests.
 */

#include "LinAlg/Vector.h"
#include "LinAlg/VectorMath.h"

#include <cmath>
#include <gtest/gtest.h>
#include <initializer_list>
#include <string>
#include <utility>

using namespace MathUtils;

namespace {


const std::string test_reports_file = std::string("TESTRESULTS-LinAlg-VectorMath.xml");

class LinAlg_VectorMath : public ::testing::Test
{

protected:
  void SetUp() override
  {}

  void TearDown() override
  {}

  /*
    vec1 = np.array([1, 2, 3])
    vec2 = np.array([4, 5, 6])
    scalar = 4
   */
  LinAlg::Vector<3> vec1 {1, 2, 3};  ///< Vector #1 under test
  LinAlg::Vector<3> vec2 {4, 5, 6};  ///< Vector #2 under test
  double scalar = 4;  ///< Scalar under test
};

// ====================================================================================================================
TEST_F(LinAlg_VectorMath, CrossProduct)
{
  /**
    np.cross(vec1,vec2)
    array([-3,  6, -3])
   */

  const LinAlg::Vector<3> numpy_result {-3, 6, -3};

  const LinAlg::Vector<3> res = LinAlg::cross(vec1, vec2);

  EXPECT_DOUBLE_EQ(res(0), numpy_result(0));
  EXPECT_DOUBLE_EQ(res(1), numpy_result(1));
  EXPECT_DOUBLE_EQ(res(2), numpy_result(2));
}

// ====================================================================================================================
TEST_F(LinAlg_VectorMath, DotProduct)
{
  /*
    np.dot(vec1,vec2)
    32
   */

  const double numpy_result = 32;

  const double res = LinAlg::dot(vec1, vec2);

  EXPECT_DOUBLE_EQ(res, numpy_result);
}

// ====================================================================================================================
TEST_F(LinAlg_VectorMath, Add)
{
  /*
    vec1 + vec2
    array([5, 7, 9])
   */

  const LinAlg::Vector<3> numpy_result {5, 7, 9};

  const LinAlg::Vector<3> res = vec1 + vec2;

  EXPECT_DOUBLE_EQ(res(0), numpy_result(0));
  EXPECT_DOUBLE_EQ(res(1), numpy_result(1));
  EXPECT_DOUBLE_EQ(res(2), numpy_result(2));
}

// ====================================================================================================================
TEST_F(LinAlg_VectorMath, Subtract)
{
  /*
    vec1 - vec2
    array([-3 -3, -3])
   */

  const LinAlg::Vector<3> numpy_result {-3, -3, -3};

  const LinAlg::Vector<3> res = vec1 - vec2;

  EXPECT_DOUBLE_EQ(res(0), numpy_result(0));
  EXPECT_DOUBLE_EQ(res(1), numpy_result(1));
  EXPECT_DOUBLE_EQ(res(2), numpy_result(2));
}

// ====================================================================================================================
TEST_F(LinAlg_VectorMath, VectorScalarMultiplication)
{
  /*
    vec1 * scalar
    array([ 4,  8, 12])
   */

  const LinAlg::Vector<3> numpy_result {4, 8, 12};

  const LinAlg::Vector<3> res = vec1 * scalar;

  EXPECT_DOUBLE_EQ(res(0), numpy_result(0));
  EXPECT_DOUBLE_EQ(res(1), numpy_result(1));
  EXPECT_DOUBLE_EQ(res(2), numpy_result(2));
}

// ====================================================================================================================
TEST_F(LinAlg_VectorMath, ScalarVectorMultiplication)
{
  /*
    scalar * vec2
    array([16, 20, 24])
   */

  const LinAlg::Vector<3> numpy_result {16, 20, 24};

  const LinAlg::Vector<3> res = scalar * vec2;

  EXPECT_DOUBLE_EQ(res(0), numpy_result(0));
  EXPECT_DOUBLE_EQ(res(1), numpy_result(1));
  EXPECT_DOUBLE_EQ(res(2), numpy_result(2));
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
