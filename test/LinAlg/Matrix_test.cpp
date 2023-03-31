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
#include <sstream>
#include <stdexcept>
#include <string>

using MathUtils::Matrix;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-Matrix.xml");

// =================================================================================================
TEST(MatrixTest, DefaultConstructorZerosElements)
{
    Matrix<2,2> mat;

    EXPECT_DOUBLE_EQ(mat(0,0), 0.0);
    EXPECT_DOUBLE_EQ(mat(0,1), 0.0);
    EXPECT_DOUBLE_EQ(mat(1,0), 0.0);
    EXPECT_DOUBLE_EQ(mat(1,1), 0.0);
}

// =================================================================================================
TEST(MatrixTest, OneDimInitListConstruction)
{
    Matrix<2,2> mat {
        1, 2,
        3, 4
    };

    EXPECT_DOUBLE_EQ(mat(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mat(0,1), 2.0);
    EXPECT_DOUBLE_EQ(mat(1,0), 3.0);
    EXPECT_DOUBLE_EQ(mat(1,1), 4.0);
}

// =================================================================================================
TEST(MatrixTest, TwoDimInitListConstruction)
{
    Matrix<3,2> mat{
        {1, 2},
        {3, 4},
        {5, 6}
    };

    EXPECT_DOUBLE_EQ(mat(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mat(0,1), 2.0);
    EXPECT_DOUBLE_EQ(mat(1,0), 3.0);
    EXPECT_DOUBLE_EQ(mat(1,1), 4.0);
    EXPECT_DOUBLE_EQ(mat(2,0), 5.0);
    EXPECT_DOUBLE_EQ(mat(2,1), 6.0);
}

// =================================================================================================
TEST(MatrixTest, CopyConstruct)
{
    Matrix<2,2> mat {{1, 2}, {3, 4}};
    Matrix<2,2> mat2(mat);

    EXPECT_DOUBLE_EQ(mat2(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mat2(0,1), 2.0);
    EXPECT_DOUBLE_EQ(mat2(1,0), 3.0);
    EXPECT_DOUBLE_EQ(mat2(1,1), 4.0);
}

// =================================================================================================
TEST(MatrixTest, CopyAssign)
{
    Matrix<2,2> mat {{1, 2}, {3, 4}};
    Matrix<2,2> mat2;

    mat2= mat;

    EXPECT_DOUBLE_EQ(mat2(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mat2(0,1), 2.0);
    EXPECT_DOUBLE_EQ(mat2(1,0), 3.0);
    EXPECT_DOUBLE_EQ(mat2(1,1), 4.0);
}

// =================================================================================================
TEST(MatrixTest, MoveAssign)
{
    Matrix<2,2> mat {{1, 2}, {3, 4}};
    Matrix<2,2> mat2;

    mat2 = std::move(mat);

    EXPECT_DOUBLE_EQ(mat2(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mat2(0,1), 2.0);
    EXPECT_DOUBLE_EQ(mat2(1,0), 3.0);
    EXPECT_DOUBLE_EQ(mat2(1,1), 4.0);
}

// =================================================================================================
TEST(MatrixTest, MoveConstruct)
{
    Matrix<2,2> mat {{1, 2}, {3, 4}};
    Matrix<2,2> mat2(std::move(mat));

    EXPECT_DOUBLE_EQ(mat2(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mat2(0,1), 2.0);
    EXPECT_DOUBLE_EQ(mat2(1,0), 3.0);
    EXPECT_DOUBLE_EQ(mat2(1,1), 4.0);
}

// =================================================================================================
TEST(MatrixDeathTest, GetInvalidRowIndexAsserts)
{
    Matrix<2,2> mat;

    EXPECT_DEBUG_DEATH({
        mat(3, 0);
    }, "");
}

// =================================================================================================
TEST(MatrixDeathTest, GetInvalidColumnIndexAsserts)
{
    Matrix<2,2> mat;

    EXPECT_DEBUG_DEATH({
        mat(0, 4);
    }, "");
}

// =================================================================================================
TEST(MatrixDeathTest, ModifyInvalidRowIndexAsserts)
{
    Matrix<2,2> mat;

    EXPECT_DEBUG_DEATH({
        mat(3, 0) = 123;
    }, "");
}

// =================================================================================================
TEST(MatrixDeathTest, ModifyInvalidColumnIndexAsserts)
{
    Matrix<2,2> mat;

    EXPECT_DEBUG_DEATH({
        mat(0, 4) = 456;
    }, "");
}

// =================================================================================================
TEST(MatrixTest, RowGetter)
{
    Matrix<4,3> mat;
    EXPECT_EQ(mat.rows(), 4);
}

// =================================================================================================
TEST(MatrixTest, ColGetter)
{
    Matrix<4,3> mat;
    EXPECT_EQ(mat.cols(), 3);
}

// =================================================================================================
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

// =================================================================================================
TEST(MatrixTest, Identity)
{
    Matrix<2,2> mat = Matrix<2,2>::identity();
    EXPECT_DOUBLE_EQ(mat(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(mat(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat(1, 1), 1.0);
}

// // =================================================================================================
// TEST(MatrixTest, NegateUnaryLvalue)
// {
//     Matrix<2,2> mat {{1, 2}, {3, 4}};

//     Matrix<2,2> mat_neg = -mat;

//     EXPECT_DOUBLE_EQ(mat_neg(0, 0), -1);
//     EXPECT_DOUBLE_EQ(mat_neg(0, 1), -2);
//     EXPECT_DOUBLE_EQ(mat_neg(1, 0), -3);
//     EXPECT_DOUBLE_EQ(mat_neg(1, 1), -4);
// }


// =================================================================================================
int main(int argc, char** argv)
{
    ::testing::GTEST_FLAG(output) = std::string("xml:") + test_reports_file;
    ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}
