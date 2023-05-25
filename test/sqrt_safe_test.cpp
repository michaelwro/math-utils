/**
 * @file sqrt_safe_test.cpp
 * @author Michael Wrona
 * @date 2023-05-20
 */

#include "sqrt_safe.h"

#include <cmath>
#include <gtest/gtest.h>

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-SqrtSafe.xml");

// =================================================================================================
TEST(SafeSqrtTest, ValidInput)
{
    const double val = 123.4;

    EXPECT_DOUBLE_EQ(MathUtils::sqrt_safe(val), std::sqrt(val));
}

// =================================================================================================
TEST(SafeSqrtDeathTest, NegativeInput)
{
    EXPECT_DEBUG_DEATH({
        double res = MathUtils::sqrt_safe(-1.0);
        EXPECT_DOUBLE_EQ(res, 0.0);
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
