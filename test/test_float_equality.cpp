/**
 * @file test_float_equality.cpp
 * @author Michael Wrona
 * @date 2023-03-17
 */

#include "float_equality.h"

#include <cmath>
#include <gtest/gtest.h>

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-float_equality.xml");

// ====================================================================================================================
TEST(FloatEquality, FloatFalse)
{
  float val1 = 123.0f;
  float val2 = 124.0f;
  EXPECT_FALSE(MathUtils::float_equality(val1, val2));
}

// ====================================================================================================================
TEST(FloatEquality, FloatFalseSmallNumber)
{
  float val1 = 12.0f;
  float val2 = 12.0f + 5e-6f;
  EXPECT_FALSE(MathUtils::float_equality(val1, val2));
}

// ====================================================================================================================
TEST(FloatEquality, FloatTrue)
{
  float val1 = -13.0f;
  float val2 = -13.0f;
  EXPECT_TRUE(MathUtils::float_equality(val1, val2));
}

// ====================================================================================================================
TEST(FloatEquality, FloatTrueSmallNumber)
{
  float val1 = 456.0f;
  float val2 = 456.0f + 1e-6f;
  EXPECT_TRUE(MathUtils::float_equality(val1, val2));
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
