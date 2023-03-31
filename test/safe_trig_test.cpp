/**
 * @file test_safe_trig.cpp
 * @author Michael Wrona
 * @date 2023-03-25
 */

#include "acos_safe.h"
#include "asin_safe.h"
#include "constants.h"

#include <cmath>
#include <gtest/gtest.h>


namespace {

const std::string test_reports_file = std::string("TESTRESULTS-SafeTrig.xml");

// =================================================================================================
TEST(SafeTrigTest, ArccosineNormal)
{
    const double res = MathUtils::acos_safe(0.0);

    EXPECT_DOUBLE_EQ(res, MathUtils::Constants::PI_DIV2);
}

// =================================================================================================
TEST(SafeTrigDeathTest, ArccosineUpperLimit)
{
    double res{};

    EXPECT_DEBUG_DEATH({
        res = MathUtils::acos_safe(23.0);
        EXPECT_DOUBLE_EQ(res, 0.0);
    }, "");

}

// =================================================================================================
TEST(SafeTrigDeathTest, ArccosineLowerLimit)
{
    double res{};

    EXPECT_DEBUG_DEATH({
        res = MathUtils::acos_safe(-12.0);
        EXPECT_DOUBLE_EQ(res, MathUtils::Constants::PI);
    }, "");

}

// =================================================================================================
TEST(SafeTrigTest, ArcsineNormal)
{

    const double res = MathUtils::asin_safe(0.0);

    EXPECT_DOUBLE_EQ(res, 0.0);
}

// =================================================================================================
TEST(SafeTrigDeathTest, ArcsineUpperLimit)
{

    double res{};

    EXPECT_DEBUG_DEATH({
        res = MathUtils::asin_safe(23.0);
        EXPECT_DOUBLE_EQ(res, MathUtils::Constants::PI_DIV2);
    }, "");

}

// =================================================================================================
TEST(SafeTrigDeathTest, ArcsineLowerLimit)
{

    double res{};

    EXPECT_DEBUG_DEATH({
        res = MathUtils::asin_safe(-12.0);
        EXPECT_DOUBLE_EQ(res, -MathUtils::Constants::PI_DIV2);
    }, "");

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
