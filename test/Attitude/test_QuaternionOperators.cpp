/**
 * @file test_QuaternionOperators.cpp
 * @author Michael Wrona
 * @date 2023-03-15
 */

#include "Attitude/Quaternion.h"


#include <cmath>
#include <gtest/gtest.h>
#include <string>

using namespace MathUtils;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-QuaternionOperators.xml");

// ====================================================================================================================
TEST(QuaternionOperatorsTest, Multiply)
{
  // Quaternion q_a(1, 2, 3, 4);
  // Quaternion q_b(4, 3, 2, 1);

  // Quaternion prod = q_a * q_b;

  // std::cout << prod << "\n";

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
