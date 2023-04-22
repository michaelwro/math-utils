/**
 * @file test_Vector.cpp
 * @author Michael Wrona
 * @date 2023-03-08
 */

#include "LinAlg/Vector.h"

#include <cmath>
#include <gtest/gtest.h>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <utility>

using MathUtils::Vector;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-Vector.xml");

// =================================================================================================
TEST(VectorTest, DefaultConstructorZerosElements)
{
    Vector<3> vec;

    EXPECT_DOUBLE_EQ(vec(0), 0.0);
    EXPECT_DOUBLE_EQ(vec(1), 0.0);
    EXPECT_DOUBLE_EQ(vec(2), 0.0);
}

// =================================================================================================
TEST(VectorTest, InitListConstruction)
{
    Vector<4> vec {1, 2, 3, 4};
    EXPECT_DOUBLE_EQ(vec(0), 1);
    EXPECT_DOUBLE_EQ(vec(1), 2);
    EXPECT_DOUBLE_EQ(vec(2), 3);
    EXPECT_DOUBLE_EQ(vec(3), 4);
}

// =================================================================================================
TEST(VectorTest, ThrowsInvalidLengthInitializerList)
{
    std::initializer_list<double> vals = {1, 2, 3, 4};

    EXPECT_THROW({
        Vector<3> vec(vals);
    }, std::length_error);
}

// =================================================================================================
TEST(VectorTest, CopyConstruction)
{
    Vector<2> vec {-1, -2};
    Vector<2> vec2(vec);

    EXPECT_DOUBLE_EQ(vec2(0), -1);
    EXPECT_DOUBLE_EQ(vec2(1), -2);
}

// =================================================================================================
TEST(VectorTest, CopyAssigns)
{
    Vector<3> vec({1, 3, 2});
    Vector<3> vec2;

    vec2 = vec;

    EXPECT_DOUBLE_EQ(vec2(0), 1);
    EXPECT_DOUBLE_EQ(vec2(1), 3);
    EXPECT_DOUBLE_EQ(vec2(2), 2);
}

// =================================================================================================
TEST(VectorTest, MoveAssigns)
{
    Vector<4> vec {4, 3, 2, 1};
    Vector<4> vec2;

    vec2 = std::move(vec);

    EXPECT_DOUBLE_EQ(vec2(0), 4);
    EXPECT_DOUBLE_EQ(vec2(1), 3);
    EXPECT_DOUBLE_EQ(vec2(2), 2);
    EXPECT_DOUBLE_EQ(vec2(3), 1);
}

// =================================================================================================
TEST(VectorTest, MoveConstruct)
{
    Vector<4> vec {4, 3, 2, 1};
    Vector<4> vec2(std::move(vec));

    EXPECT_DOUBLE_EQ(vec2(0), 4);
    EXPECT_DOUBLE_EQ(vec2(1), 3);
    EXPECT_DOUBLE_EQ(vec2(2), 2);
    EXPECT_DOUBLE_EQ(vec2(3), 1);
}

// =================================================================================================
TEST(VectorTest, InitializerListAssign)
{
    Vector<4> vec;

    vec = {1, 3, 2, 4};

    EXPECT_DOUBLE_EQ(vec(0), 1);
    EXPECT_DOUBLE_EQ(vec(1), 3);
    EXPECT_DOUBLE_EQ(vec(2), 2);
    EXPECT_DOUBLE_EQ(vec(3), 4);
}

// =================================================================================================
TEST(VectorTest, InitListAssignThrowsIncompatibleSize)
{
    Vector<3> vec;
    std::initializer_list<double> four_vals = {1, 3, 2, 4};

    EXPECT_THROW({
        vec = four_vals;
    }, std::length_error);
}

// =================================================================================================
TEST(VectorTest, ParenthesisAccessorModifiesValues)
{
    Vector<3> vec {1, 2, 3};

    vec(0) = 4;
    vec(1) = 5;
    vec(2) = 6;

    EXPECT_DOUBLE_EQ(vec(0), 4);
    EXPECT_DOUBLE_EQ(vec(1), 5);
    EXPECT_DOUBLE_EQ(vec(2), 6);
}

// =================================================================================================
TEST(VectorTest, InvalidAtAccessorIndexThrows)
{
    Vector<3> vec {1, 2, 3};

    EXPECT_THROW({
        double b = vec.at(3);
    }, std::out_of_range);
}

// =================================================================================================
TEST(VectorTest, InvalidAtModifierIndexThrows)
{
    Vector<3> vec {1, 2, 3};

    EXPECT_THROW({
        vec.at(3) = 34.0;
    }, std::out_of_range);
}

// =================================================================================================
TEST(VectorTest, SizeGetterReturnsCorrectLength)
{
    Vector<4> vec {1, 2, 3, 4};

    EXPECT_EQ(vec.size(), 4);
}

// =================================================================================================
TEST(VectorTest, Fill)
{
    Vector<3> vec {1, 1, 1};

    vec.fill(123.0);

    EXPECT_DOUBLE_EQ(vec(0), 123);
    EXPECT_DOUBLE_EQ(vec(1), 123);
    EXPECT_DOUBLE_EQ(vec(2), 123);
}

// =================================================================================================
TEST(VectorTest, PrintToStream)
{
    Vector<3> vec {12, 34, 56};

    std::stringstream ss;
    ss << vec << "\n";

    EXPECT_TRUE(ss.str().find("12") != std::string::npos);
    EXPECT_TRUE(ss.str().find("34") != std::string::npos);
    EXPECT_TRUE(ss.str().find("56") != std::string::npos);
}

// =================================================================================================
int main(int argc, char** argv)
{
    ::testing::GTEST_FLAG(output) = std::string("xml:") + test_reports_file;
    ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}  // namespace
