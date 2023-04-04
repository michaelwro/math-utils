/**
 * @file ecef_to_lla_test.cpp
 * @author Michael Wrona
 * @date 2023-04-04
 */

#include "conversions.h"
#include "Geodesy/ecef_to_lla.h"
#include "Geodesy/GeoCoord.h"
#include "LinAlg/Vector.h"
#include "TestTools/GeoCoordNear.h"

#include <gtest/gtest.h>

using MathUtils::Conversions::deg2rad;
using MathUtils::ecef_to_lla;
using MathUtils::GeoCoord;
using MathUtils::TestTools::GeoCoordNear;
using MathUtils::Vector;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-ecef_to_lla.xml");

// =================================================================================================
TEST(EcefToLlaTest, CompareAgainstOrigAlgorithm)
{
    // https://onlinegdb.com/75nsiXgfz
    const Vector<3> pos_m {6'378'137.0+10e3, -6'378'137.0-11e3, 6'378'137.0+12e3};

    const GeoCoord expected(
        0.6174137445601836,
        -0.7854764273524952,
        4695313.846401864
    );

    const GeoCoord result = ecef_to_lla(pos_m);

    EXPECT_TRUE(GeoCoordNear(result, expected, 5e-9));
}

// =================================================================================================
TEST(EcefToLlaTest, MathWorksExample1)
{
    // https://www.mathworks.com/help/aerotbx/ug/ecef2lla.html
    const Vector<3> pos_m {4510731.0, 4510731.0, 0.0};

    const GeoCoord expected(
        0.0,
        deg2rad(45.0),
        999.9564
    );

    const GeoCoord result = ecef_to_lla(pos_m);

    EXPECT_TRUE(GeoCoordNear(result, expected, 1e-3));
}

// =================================================================================================
TEST(EcefToLlaTest, MathWorksExample2)
{
    // https://www.mathworks.com/help/aerotbx/ug/ecef2lla.html
    const Vector<3> pos_m {0.0, 4507609.0, 4498719.0};

    const GeoCoord expected(
        deg2rad(45.1358),
        deg2rad(90.0),
        999.8659
    );

    const GeoCoord result = ecef_to_lla(pos_m);

    EXPECT_TRUE(GeoCoordNear(result, expected, 1e-3));
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
