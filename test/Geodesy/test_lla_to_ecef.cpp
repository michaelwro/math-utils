/**
 * @file test_lla_to_ecef.cpp
 * @author Michael Wrona
 * @date 2023-03-29
 */

#include "Geodesy/GeoCoord.h"
#include "Geodesy/lla_to_ecef.h"
#include "TestTools/VectorNear.h"
#include "conversions.h"
#include "wrap_pi.h"

#include <gtest/gtest.h>
#include <string>

using MathUtils::wrap_pi;
using MathUtils::lla_to_ecef;
using MathUtils::Conversions::deg2rad;
using MathUtils::GeoCoord;
using MathUtils::Vector;
using MathUtils::TestTools::VectorNear;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-lla_to_ecef.xml");

// ====================================================================================================================
TEST(LlaToEcefTest, ValladoExample3_2)
{
  GeoCoord ascension_island_lla {
    deg2rad(-7.0 - (54.0 / 60.0) - (23.886 / 3600.0)),
    wrap_pi(deg2rad(345.0 + (35.0 / 60.0) + (51.0 / 3600.0))),
    56.0
  };

  const Vector<3> pos_ecef_m = lla_to_ecef(ascension_island_lla);

  const Vector<3> vallado {
    6119.400'269'32e3,
    -1571.479'555'45e3,
    -871.561'180'90e3
  };

  EXPECT_TRUE(VectorNear(vallado, pos_ecef_m, 1e-5));
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
