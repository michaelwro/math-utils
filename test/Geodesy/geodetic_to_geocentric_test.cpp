/**
 * @file geodetic_to_geocentric_test.cpp
 * @author Michael Wrona
 * @date 2023-04-28
 */

#include "Geodesy/geodetic_to_geocentric.h"
#include "Geodesy/GeoCoord.h"
#include "conversions.h"

#include <gtest/gtest.h>

#include <string>

using MathUtils::Conversions::deg2rad;
using MathUtils::GeoCoord;
using MathUtils::geodetic_to_geocentric;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-geod_to_geoc.xml");


class GeodeticToGeocentricTest : public ::testing::Test {
public:
    GeodeticToGeocentricTest() = default;
    ~GeodeticToGeocentricTest() = default;

protected:
    void SetUp() override {}
    void TearDown() override {}

public:
    // from https://www.mathworks.com/help/aerotbx/ug/geod2geoc.html
    const double mathworks_lat_gd = deg2rad(45);
    const double mathworks_alt_gd = 0;
    const GeoCoord mathworks_lla_gd {mathworks_lat_gd, 0.0, mathworks_alt_gd};

    const double mathworks_res_lat_gc = deg2rad(44.8076);
    const double mathworks_res_geoc_rad = 6.3675e6;
};

// =================================================================================================
TEST_F(GeodeticToGeocentricTest, MathWorksExampleGeoCoordInput)
{
    const auto [gc, rad] = geodetic_to_geocentric(mathworks_lla_gd);

    EXPECT_NEAR(gc, mathworks_res_lat_gc, 1e-4);
    EXPECT_NEAR(rad, mathworks_res_geoc_rad, 1e2);
}

// =================================================================================================
TEST_F(GeodeticToGeocentricTest, MathWorksExampleScalarInput)
{
    const auto [gc, rad] = geodetic_to_geocentric(mathworks_lat_gd, mathworks_alt_gd);

    EXPECT_NEAR(gc, mathworks_res_lat_gc, 1e-4);
    EXPECT_NEAR(rad, mathworks_res_geoc_rad, 1e2);
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
