/**
 * @file range_constrain_test.cpp
 * @author Michael Wrona
 * @date 2023-05-20
 */

#include "range_constrain.h"

#include <cmath>
#include <gtest/gtest.h>

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-RangeConstrain.xml");

constexpr int lower = 0;
constexpr int upper = 10;

// =================================================================================================
TEST(RangeConstrainTest, LowerBound)
{
    constexpr int val = -1;

    EXPECT_EQ(MathUtils::range_constrain(val, lower, upper), lower);
}

// =================================================================================================
TEST(RangeConstrainTest, UpperBound)
{
    constexpr int val = 12;

    EXPECT_EQ(MathUtils::range_constrain(val, lower, upper), upper);
}

// =================================================================================================
TEST(RangeConstrainTest, WithinBounds)
{
    constexpr int val = 3;

    EXPECT_EQ(MathUtils::range_constrain(val, lower, upper), val);
}

// =================================================================================================
TEST(RangeConstrainTest, OnBounds)
{
    EXPECT_EQ(MathUtils::range_constrain(lower, lower, upper), lower);
    EXPECT_EQ(MathUtils::range_constrain(upper, lower, upper), upper);
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
