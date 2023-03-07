#include <gtest/gtest.h>
// #include <gtest/gtest-death-test.h>
#include "LinAlg/Vector.h"
#include <initializer_list>
#include <string>

using MathUtils::LinAlg::Vector;

// file to save test repots to
const std::string test_reports_file = std::string(MATHUTILS_TEST_REPORT_DIR) + "/LinAlg-Vector-report.xml";


// ====================================================================================================================
TEST(VectorTest, DefaultConstructorZerosElements)
{
  Vector<3> vec;

  EXPECT_DOUBLE_EQ(vec(0), 0.0);
  EXPECT_DOUBLE_EQ(vec(1), 0.0);
  EXPECT_DOUBLE_EQ(vec(2), 0.0);
}


// ====================================================================================================================
TEST(VectorTest, InitListConstructionWorks)
{
  Vector<4> vec = {1, 2, 3, 4};

  EXPECT_DOUBLE_EQ(vec(0), 1);
  EXPECT_DOUBLE_EQ(vec(1), 2);
  EXPECT_DOUBLE_EQ(vec(2), 3);
  EXPECT_DOUBLE_EQ(vec(3), 4);
}


// ====================================================================================================================
TEST(VectorTest, InitListConstructorAssertsInvalidSize)
{
  std::initializer_list<double> vals = {1, 2, 3, 4};

  ASSERT_DEBUG_DEATH({
    Vector<3> vec(vals);
    }, "");
}


// ====================================================================================================================
TEST(VectorTest, CopyConstructorWorks)
{
  Vector<2> vec = {-1, -2};
  Vector<2> vec2(vec);

  EXPECT_DOUBLE_EQ(vec2(0), -1);
  EXPECT_DOUBLE_EQ(vec2(1), -2);
}


// ====================================================================================================================
int main(int argc, char** argv)
{
  ::testing::GTEST_FLAG(output) = std::string("xml:") + test_reports_file;
  ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
