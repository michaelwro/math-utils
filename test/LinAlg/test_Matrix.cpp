/**
 * @file test_Matrix.cpp
 * @author Michael Wrona
 * @date 2023-03-18
 *
 * @details NOTE: Gtest death tests cannot test the two-argument `Matrix<rows,cols>` constructor.
 */

#include "LinAlg/Matrix.h"

#include <functional>
#include <gtest/gtest.h>
#include <initializer_list>
#include <string>
#include <sstream>

using MathUtils::Matrix;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-LinAlg-Matrix.xml");

// ====================================================================================================================
TEST(MatrixTest, DefaultConstructorZerosElements)
{
  Matrix<2,2> mat;

  EXPECT_DOUBLE_EQ(mat(0,0), 0.0);
  EXPECT_DOUBLE_EQ(mat(0,1), 0.0);
  EXPECT_DOUBLE_EQ(mat(1,0), 0.0);
  EXPECT_DOUBLE_EQ(mat(1,1), 0.0);
}

// ====================================================================================================================
TEST(MatrixTest, OneDimInitListConstruction)
{
  Matrix<2,2> mat({
    1, 2,
    3, 4
  });

  EXPECT_DOUBLE_EQ(mat(0,0), 1.0);
  EXPECT_DOUBLE_EQ(mat(0,1), 2.0);
  EXPECT_DOUBLE_EQ(mat(1,0), 3.0);
  EXPECT_DOUBLE_EQ(mat(1,1), 4.0);
}

// ====================================================================================================================
TEST(MatrixTest, TwoDimInitListConstruction)
{
  Matrix<3,2> mat({
    {1, 2},
    {3, 4},
    {5, 6}
  });

  EXPECT_DOUBLE_EQ(mat(0,0), 1.0);
  EXPECT_DOUBLE_EQ(mat(0,1), 2.0);
  EXPECT_DOUBLE_EQ(mat(1,0), 3.0);
  EXPECT_DOUBLE_EQ(mat(1,1), 4.0);
  EXPECT_DOUBLE_EQ(mat(2,0), 5.0);
  EXPECT_DOUBLE_EQ(mat(2,1), 6.0);
}

// ====================================================================================================================
TEST(MatrixTest, CopyConstruct)
{
  Matrix<2,2> mat( {{1, 2}, {3, 4}} );
  Matrix<2,2> mat2(mat);

  EXPECT_DOUBLE_EQ(mat2(0,0), 1.0);
  EXPECT_DOUBLE_EQ(mat2(0,1), 2.0);
  EXPECT_DOUBLE_EQ(mat2(1,0), 3.0);
  EXPECT_DOUBLE_EQ(mat2(1,1), 4.0);
}

// ====================================================================================================================
TEST(MatrixTest, CopyAssign)
{
  Matrix<2,2> mat( {{1, 2}, {3, 4}} );
  Matrix<2,2> mat2;

  mat2= mat;

  EXPECT_DOUBLE_EQ(mat2(0,0), 1.0);
  EXPECT_DOUBLE_EQ(mat2(0,1), 2.0);
  EXPECT_DOUBLE_EQ(mat2(1,0), 3.0);
  EXPECT_DOUBLE_EQ(mat2(1,1), 4.0);
}

// ====================================================================================================================
TEST(MatrixTest, MoveAssign)
{
  Matrix<2,2> mat( {{1, 2}, {3, 4}} );
  Matrix<2,2> mat2;

  mat2 = std::move(mat);

  EXPECT_DOUBLE_EQ(mat2(0,0), 1.0);
  EXPECT_DOUBLE_EQ(mat2(0,1), 2.0);
  EXPECT_DOUBLE_EQ(mat2(1,0), 3.0);
  EXPECT_DOUBLE_EQ(mat2(1,1), 4.0);
}

// ====================================================================================================================
TEST(MatrixDeathTest, GetElementAssertsInvalidRowIndex)
{
  Matrix<2,2> mat;

  ASSERT_DEBUG_DEATH({
    mat(3, 2);
  }, "");
}

// ====================================================================================================================
TEST(MatrixDeathTest, GetElementAssertsInvalidColumnIndex)
{
  Matrix<2,2> mat;

  ASSERT_DEBUG_DEATH({
    mat(0, 3);
  }, "");
}

// ====================================================================================================================
TEST(MatrixDeathTest, ModifyElementAssertsInvalidRowIndex)
{
  Matrix<2,2> mat;

  ASSERT_DEBUG_DEATH({
    mat(3, 2) = 123;
  }, "");
}

// ====================================================================================================================
TEST(MatrixDeathTest, ModifyElementAssertsInvalidColumnIndex)
{
  Matrix<2,2> mat;

  ASSERT_DEBUG_DEATH({
    mat(0, 3) = 123;
  }, "");
}

// ====================================================================================================================
TEST(MatrixTest, RowsGetter)
{
  Matrix<4,3> mat;
  EXPECT_EQ(mat.rows(), 4);
}

// ====================================================================================================================
TEST(MatrixTest, ColsGetter)
{
  Matrix<4,3> mat;
  EXPECT_EQ(mat.cols(), 3);
}

// ====================================================================================================================
TEST(MatrixTest, PrintToStream)
{
  Matrix<2,2> mat({{1, 2}, {3, 4}});

  std::stringstream ss;
  ss << mat << "\n";

  EXPECT_TRUE(ss.str().find("1") != std::string::npos);
  EXPECT_TRUE(ss.str().find("2") != std::string::npos);
  EXPECT_TRUE(ss.str().find("3") != std::string::npos);
  EXPECT_TRUE(ss.str().find("4") != std::string::npos);
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
