/**
 * @file dcm_to_euler_test.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "Attitude/dcm_to_euler.h"
#include "Attitude/Euler321.h"
#include "conversions.h"
#include "LinAlg/Matrix.h"
#include "TestTools/Euler321Near.h"

#include <gtest/gtest.h>
#include <string>

using MathUtils::Conversions::deg2rad;
using MathUtils::dcm_to_euler;
using MathUtils::Euler321;
using MathUtils::Matrix;
using MathUtils::TestTools::Euler321Near;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-dcm_to_euler.xml");

// =================================================================================================
TEST(DcmToEulerTest, SchaubExample3_2)
{
    const Matrix<3,3> dcm {
        {0.612372, 0.353553, 0.707107},
        {-0.78033, 0.126826, 0.612372},
        {0.126826, -0.926777, 0.353553}
    };

    const Euler321 expected {deg2rad(30.0), deg2rad(-45.0), deg2rad(60.0)};

    const Euler321 result = dcm_to_euler(dcm);

    EXPECT_TRUE(Euler321Near(result, expected, 1e-5));
}

// =================================================================================================
TEST(DcmToEulerTest, MathWorksExample)
{
    //https://www.mathworks.com/help/aerotbx/ug/angle2dcm.html
    const Matrix<3,3> dcm {
        {0.7036, 0.7036, -0.0998},
        {-0.7071, 0.7071, 0.0},
        {0.0706, 0.0706, 0.9950},
    };

    const Euler321 expected {0.7854,  0.1, 0.0};

    const Euler321 result = dcm_to_euler(dcm);

    EXPECT_TRUE(Euler321Near(result, expected, 1e-4));
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
