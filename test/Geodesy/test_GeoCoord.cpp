/**
 * @file test_GeoCoord.cpp
 * @author Michael Wrona
 * @date 2023-03-27
 */

#include "Geodesy/GeoCoord.h"

#include <gtest/gtest.h>
#include <string>


namespace {

const std::string test_reports_file = std::string("TESTRESULTS-geokcoord.xml");


// ====================================================================================================================
int main(int argc, char** argv)
{
  ::testing::GTEST_FLAG(output) = std::string("xml:") + test_reports_file;
  ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}  // namespace
