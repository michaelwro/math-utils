/**
 * @file Euler321_test.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "Attitude/Euler321.h"
#include "TestTools/Euler321Near.h"
#include "conversions.h"

#include <cmath>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <utility>

using MathUtils::Conversions::deg2rad;
using MathUtils::Euler321;
using MathUtils::TestTools::Euler321Near;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-Euler321.xml");

// =================================================================================================
TEST(Euler321Test, DefaultConstruct)
{
    Euler321 euler;

    EXPECT_DOUBLE_EQ(euler.yaw(), 0.0);
    EXPECT_DOUBLE_EQ(euler.pitch(), 0.0);
    EXPECT_DOUBLE_EQ(euler.roll(), 0.0);
}

// =================================================================================================
TEST(Euler321Test, CopyConstruct)
{
    Euler321 euler_orig(1, 2, 3);
    Euler321 euler(euler_orig);

    EXPECT_DOUBLE_EQ(euler.yaw(), 1.0);
    EXPECT_DOUBLE_EQ(euler.pitch(), 2.0);
    EXPECT_DOUBLE_EQ(euler.roll(), 3.0);
}

// =================================================================================================
TEST(Euler321Test, InitListConstruct)
{
    Euler321 euler({1, 2, 3});

    EXPECT_DOUBLE_EQ(euler.yaw(), 1.0);
    EXPECT_DOUBLE_EQ(euler.pitch(), 2.0);
    EXPECT_DOUBLE_EQ(euler.roll(), 3.0);
}

// =================================================================================================
TEST(Euler321Test, InitListConstructThrowsInvalidLength)
{
    std::initializer_list<double> vals = {1, 2, 3, 4};

    EXPECT_THROW({
        Euler321 euler(vals);
    }, std::length_error);
}

// =================================================================================================
TEST(Euler321Test, MoveConstruct)
{
    Euler321 euler_orig(1, 2, 3);
    Euler321 euler(std::move(euler_orig));

    EXPECT_DOUBLE_EQ(euler.yaw(), 1.0);
    EXPECT_DOUBLE_EQ(euler.pitch(), 2.0);
    EXPECT_DOUBLE_EQ(euler.roll(), 3.0);
}

// =================================================================================================
TEST(Euler321Test, CopyAssign)
{
    Euler321 euler_orig(1, 2, 3);
    Euler321 euler = euler_orig;

    EXPECT_DOUBLE_EQ(euler.yaw(), 1.0);
    EXPECT_DOUBLE_EQ(euler.pitch(), 2.0);
    EXPECT_DOUBLE_EQ(euler.roll(), 3.0);
}

// =================================================================================================
TEST(Euler321Test, MoveAssign)
{
    Euler321 euler_orig(1, 2, 3);
    Euler321 euler = std::move(euler_orig);

    EXPECT_DOUBLE_EQ(euler.yaw(), 1.0);
    EXPECT_DOUBLE_EQ(euler.pitch(), 2.0);
    EXPECT_DOUBLE_EQ(euler.roll(), 3.0);
}

// =================================================================================================
TEST(Euler321Test, InitListAssign)
{
    Euler321 euler;
    euler = {1, 2, 3};

    EXPECT_DOUBLE_EQ(euler.yaw(), 1.0);
    EXPECT_DOUBLE_EQ(euler.pitch(), 2.0);
    EXPECT_DOUBLE_EQ(euler.roll(), 3.0);
}

// =================================================================================================
TEST(Euler321Test, InitListAssignThrowsInvalidLength)
{
    std::initializer_list<double> vals = {1, 2};

    EXPECT_THROW({
        Euler321 euler;
        euler = vals;
    }, std::length_error);
}

// =================================================================================================
TEST(Euler321Test, ValueModifiers)
{
    Euler321 euler;
    euler.yaw() = 3;
    euler.pitch() = 2;
    euler.roll() = 1;

    EXPECT_DOUBLE_EQ(euler.yaw(), 3);
    EXPECT_DOUBLE_EQ(euler.pitch(), 2);
    EXPECT_DOUBLE_EQ(euler.roll(), 1);
}

// =================================================================================================
TEST(Euler321Test, PrintToStream)
{
    Euler321 euler(3.33, 2.22, 1.11);

    std::stringstream ss;
    ss << euler << "\n";

    EXPECT_TRUE(ss.str().find("3.3") != std::string::npos);
    EXPECT_TRUE(ss.str().find("2.2") != std::string::npos);
    EXPECT_TRUE(ss.str().find("1.1") != std::string::npos);

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

