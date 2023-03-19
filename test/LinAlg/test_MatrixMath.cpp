/**
 * @file test_Matrix.cpp
 * @author Michael Wrona
 * @date 2023-03-18
 *
 * @details NOTE: Gtest death tests cannot test the two-argument `Matrix<rows,cols>` constructor.
 */

#include "LinAlg/Matrix.h"

// #include <functional>
#include <gtest/gtest.h>
#include <initializer_list>
#include <string>
// #include <sstream>

using MathUtils::Matrix;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-LinAlg-MatrixMath.xml");

class MatrixMathTest : public ::testing::Test
{
protected:
  void SetUp() override
  {}

  void TearDown() override
  {}

  /*
    np.set_printoptions(precision=16)
    mat1 = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    mat2 = np.array([[9, 8, 7], [6, 5, 4], [3, 2, 1]])
    scalar = 2
  */
  const double scalar = 2.0;

  Matrix<3,3> mat1 {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const double mat1_trace = 15;

  Matrix<3,3> mat2 {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
  const double mat2_trace = 15;

  const Matrix<3,3> mat1_times_mat2 {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};


};

// ====================================================================================================================
TEST_F(MatrixMathTest, Trace)
{
  EXPECT_DOUBLE_EQ(mat1.trace(), mat1_trace);
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Multiply2x2)
{
  const Matrix<2,2> m1 {{1, 2}, {3, 4}};
  const Matrix<2,2> m2 {{5, 6}, {7, 8}};

  const Matrix<2,2> result = m1 * m2;
  const Matrix<2,2> expected {{19, 22}, {43, 50}};

  for (std::size_t ii : {0, 1})
  {
    for (std::size_t jj : {0, 1})
    {
      EXPECT_DOUBLE_EQ(expected(ii, jj), result(ii, jj));
    }
  }
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Multiply3x3)
{
  const Matrix<3,3> result = mat1 * mat2;

  for (std::size_t ii : {0, 1, 2})
  {
    for (std::size_t jj : {0, 1, 2})
    {
      EXPECT_DOUBLE_EQ(mat1_times_mat2(ii, jj), result(ii, jj));
    }
  }
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Multiply3x2And2x2)
{

  const Matrix<3,2> mat1 {{1, 2}, {3, 4}, {5, 6}};
  const Matrix<2,2> mat2 {{4, 3}, {2, 1}};

  const Matrix<3,2> result = mat1 * mat2;
  const Matrix<3,2> expected {{8, 5}, {20, 13}, {32, 21}};

  for (std::size_t ii : {0, 1, 2})
  {
    for (std::size_t jj : {0, 1})
    {
      EXPECT_DOUBLE_EQ(expected(ii, jj), result(ii, jj));
    }
  }
}







// ====================================================================================================================
int main(int argc, char** argv)
{
  ::testing::GTEST_FLAG(output) = std::string("xml:") + test_reports_file;
  ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}
