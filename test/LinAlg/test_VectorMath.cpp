/**
 * @file test_VectorMath.cpp
 * @author Michael Wrona
 * @date 2023-03-10
 * @brief Vector math unit tests.
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
    vec1 = np.array([1, 2, 3])
    vec2 = np.array([4, 5, 6])
    scalar = 4
   */
  Vector<3> vec1 {1, 2, 3};  ///< Vector #1 under test
  Vector<3> vec2 {4, 5, 6};  ///< Vector #2 under test
  double scalar = 4;  ///< Scalar under test
};


// ====================================================================================================================
TEST_F(VectorMathTest, CrossProduct)
{
  const Vector<3> numpy_result {-3, 6, -3};

  const Vector<3> res = cross(vec1, vec2);

  EXPECT_DOUBLE_EQ(res(0), numpy_result(0));
  EXPECT_DOUBLE_EQ(res(1), numpy_result(1));
  EXPECT_DOUBLE_EQ(res(2), numpy_result(2));
}

// ====================================================================================================================
TEST_F(VectorMathTest, DotProduct)
{
  const double numpy_result = 32;

  const double res = dot(vec1, vec2);

  EXPECT_DOUBLE_EQ(res, numpy_result);
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
