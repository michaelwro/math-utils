/**
 * @file test_MatrixMath.cpp
 * @author Michael Wrona
 * @date 2023-03-18
 *
 * @details NOTE: Gtest death tests cannot test the two-argument `Matrix<rows,cols>` constructor.
 */

#include "LinAlg/Matrix.h"
#include "LinAlg/Vector.h"
#include "TestTools/MatrixNear.h"
#include "TestTools/VectorNear.h"

#include <gtest/gtest.h>
#include <initializer_list>
#include <string>

using MathUtils::Matrix;
using MathUtils::TestTools::MatrixNear;
using MathUtils::TestTools::VectorNear;
using MathUtils::Vector;

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
  Matrix<3,3> mat1_plus_scalar {{3, 4, 5}, {6, 7, 8}, {9, 10, 11}};
  Matrix<3,3> mat1_minus_scalar {{-1, 0, 1}, {2, 3, 4}, {5, 6, 7}};
  Matrix<3,3> mat1_times_scalar {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
  Matrix<3,3> mat1_div_scalar {{0.5, 1.0, 1.5}, {2.0, 2.5, 3.0}, {3.5, 4.0, 4.5}};
  Matrix<3,3> mat1_plus_eye {{2, 2, 3}, {4, 6, 6}, {7, 8, 10}};

  Matrix<3,3> mat2 {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
  const double mat2_trace = 15;

  const Matrix<3,3> mat1_plus_mat2 {{10, 10, 10}, {10, 10, 10}, {10, 10, 10}};
  const Matrix<3,3> mat1_minus_mat2 {{-8, -6, -4}, {-2, 0, 2}, {4, 6, 8}};
  const Matrix<3,3> mat1_times_mat2 {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};

};

// ====================================================================================================================
TEST_F(MatrixMathTest, Trace)
{
  EXPECT_DOUBLE_EQ(trace(mat1), mat1_trace);
}

// ====================================================================================================================
TEST_F(MatrixMathTest, IdentityAddition)
{
  Matrix<3,3> mat = Matrix<3,3>::identity() + mat1;

  EXPECT_TRUE(MatrixNear(mat, mat1_plus_eye));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, ScalarAddInPlace)
{
  mat1 += scalar;

  EXPECT_TRUE(MatrixNear(mat1, mat1_plus_scalar));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, MatrixAddInPlace)
{
  mat1 += mat2;

  EXPECT_TRUE(MatrixNear(mat1, mat1_plus_mat2));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, ScalarSubtractInPlace)
{
  mat1 -= scalar;

  EXPECT_TRUE(MatrixNear(mat1, mat1_minus_scalar));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, MatrixSubtractInPlace)
{
  mat1 -= mat2;

  EXPECT_TRUE(MatrixNear(mat1, mat1_minus_mat2));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, ScalarMultiplyInPlace)
{
  mat1 *= scalar;

  EXPECT_TRUE(MatrixNear(mat1, mat1_times_scalar));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, MatrixMultiplyInPlace)
{
  mat1 *= mat2;

  EXPECT_TRUE(MatrixNear(mat1, mat1_times_mat2));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, ScalarDivideInPlace)
{
  mat1 /= scalar;

  EXPECT_TRUE(MatrixNear(mat1, mat1_div_scalar));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, SmallScalarDivideInPlaceAsserts)
{
  ASSERT_DEBUG_DEATH({
    mat1 /= 0ul;
  }, "");
}

// ====================================================================================================================
TEST_F(MatrixMathTest, ScalarMatrixMultiply)
{
  Matrix<3,3> res = scalar * mat1;

  EXPECT_TRUE(MatrixNear(res, mat1_times_scalar));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, MatrixScalarMultiply)
{
  Matrix<3,3> res = mat1 * scalar;

  EXPECT_TRUE(MatrixNear(res, mat1_times_scalar));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Multiply2x2)
{
  const Matrix<2,2> m1 {{1, 2}, {3, 4}};
  const Matrix<2,2> m2 {{5, 6}, {7, 8}};

  const Matrix<2,2> result = m1 * m2;
  const Matrix<2,2> expected {{19, 22}, {43, 50}};

  EXPECT_TRUE(MatrixNear(expected, result));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Multiply3x3)
{
  const Matrix<3,3> result = mat1 * mat2;

  EXPECT_TRUE(MatrixNear(mat1_times_mat2, result));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Multiply3x2And2x2)
{
  const Matrix<3,2> mat1 {{1, 2}, {3, 4}, {5, 6}};
  const Matrix<2,2> mat2 {{4, 3}, {2, 1}};

  const Matrix<3,2> result = mat1 * mat2;
  const Matrix<3,2> expected {{8, 5}, {20, 13}, {32, 21}};

  EXPECT_TRUE(MatrixNear(expected, result));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, MultiplyThree2x2)
{
  const Matrix<2,2> m1 {{1, 2}, {3, 4}};
  const Matrix<2,2> m2 {{5, 6}, {7, 8}};
  const Matrix<2,2> m3 {{9, 10}, {11, 12}};

  const Matrix<2,2> result = m1 * m2 * m3;
  const Matrix<2,2> expected {{413, 454}, {937, 1030}};

  EXPECT_TRUE(MatrixNear(expected, result));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, MatrixVectorMultiplication2x2)
{
  Matrix<2,2> mat {{1, 2}, {3, 4}};
  Vector<2> vec {3, 4};

  Vector<2> expected {11, 25};

  Vector<2> res = mat * vec;

  EXPECT_TRUE(VectorNear(expected, res));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, MatrixVectorMultiplication3x3)
{
  Matrix<3,3> mat {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Vector<3> vec {9, 8, 7};

  Vector<3> expected {46, 118, 190};

  Vector<3> res = mat * vec;

  EXPECT_TRUE(VectorNear(expected, res));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, NonSquareMatrixVectorMultiplication)
{
  Matrix<2,3> mat {{1, 2, 3}, {4, 5, 6}};
  Vector<3> vec {7, 8, 9};

  Vector<2> expected {50, 122};

  Vector<2> res = mat * vec;

  EXPECT_TRUE(VectorNear(expected, res));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Add2x2)
{
  const Matrix<2,2> m1 {{1, 2}, {3, 4}};
  const Matrix<2,2> m2 {{5, 6}, {7, 8}};

  const Matrix<2,2> result = m1 + m2;
  const Matrix<2,2> expected {{6, 8}, {10, 12}};

  EXPECT_TRUE(MatrixNear(expected, result));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Add3x3)
{
  const Matrix<3,3> result = mat1 + mat2;

  EXPECT_TRUE(MatrixNear(mat1_plus_mat2, result));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Add3x2)
{
  const Matrix<3,2> m1 {{1, 2}, {3, 4}, {5, 6}};
  const Matrix<3,2> m2 {{1, 2}, {3, 4}, {5, 6}};

  const Matrix<3,2> result = m1 + m2;
  const Matrix<3,2> expected {{2, 4}, {6, 8}, {10, 12}};

  EXPECT_TRUE(MatrixNear(expected, result));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Subtract2x2)
{
  const Matrix<2,2> m1 {{1, 2}, {3, 4}};
  const Matrix<2,2> m2 {{5, 6}, {7, 8}};

  const Matrix<2,2> result = m1 - m2;
  const Matrix<2,2> expected {{-4, -4}, {-4, -4}};

  EXPECT_TRUE(MatrixNear(expected, result));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Subtract3x3)
{
  const Matrix<3,3> result = mat1 - mat2;

  EXPECT_TRUE(MatrixNear(mat1_minus_mat2, result));
}

// ====================================================================================================================
TEST_F(MatrixMathTest, Subtract3x2)
{
  const Matrix<3,2> m1 {{1, 2}, {3, 4}, {5, 6}};
  const Matrix<3,2> m2 {{1, 3}, {5, 7}, {9, 11}};

  const Matrix<3,2> result = m1 - m2;
  const Matrix<3,2> expected {{0, -1}, {-2, -3}, {-4, -5}};

  EXPECT_TRUE(MatrixNear(expected, result));
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
