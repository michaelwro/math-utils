/**
 * @file euler_to_dcm.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "Attitude/euler_to_dcm.h"
#include "Attitude/Euler321.h"
#include "conversions.h"
#include "LinAlg/Matrix.h"
#include "TestTools/MatrixNear.h"

#include <cmath>
#include <gtest/gtest.h>
#include <string>

using MathUtils::Conversions::deg2rad;
using MathUtils::euler_to_dcm;
using MathUtils::Euler321;
using MathUtils::Matrix;
using MathUtils::TestTools::MatrixNear;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-euler_to_dcm.xml");

// =================================================================================================
TEST(EulerToDCMTest, SchaubExample3_2)
{
    const Matrix<3,3> expected {
        {0.612372, 0.353553, 0.707107},
        {-0.78033, 0.126826, 0.612372},
        {0.126826, -0.926777, 0.353553}
    };

    const Euler321 angles {deg2rad(30.0), deg2rad(-45.0), deg2rad(60.0)};

    const Matrix<3,3> result = euler_to_dcm(angles);

    EXPECT_TRUE(MatrixNear(result, expected, 1e-2));
}

// =================================================================================================
TEST(EulerToDCMTest, MathWorksExample)
{
    //https://www.mathworks.com/help/aerotbx/ug/angle2dcm.html
    const Matrix<3,3> expected {
        {0.7036, 0.7036, -0.0998},
        {-0.7071, 0.7071, 0.0},
        {0.0706, 0.0706, 0.9950},
    };

    const Euler321 angles {0.7854,  0.1, 0.0};

    const Matrix<3,3> result = euler_to_dcm(angles);

    EXPECT_TRUE(MatrixNear(result, expected, 1e-4));
}

// =================================================================================================
TEST(EulerToDCMTest, RollAngle)
{
    const double roll = deg2rad(12.3456789);
    const double c = std::cos(roll);
    const double s = std::sin(roll);

    const Matrix<3,3> expected {
        {1.0, 0.0, 0.0},
        {0.0, c, s},
        {0.0, -s, c}
    };

    const Matrix<3,3> result = euler_to_dcm(Euler321{0.0, 0.0, roll});

    EXPECT_TRUE(MatrixNear(result, expected, 1e-6));
}

// =================================================================================================
TEST(EulerToDCMTest, PitchAngle)
{
    const double pitch = deg2rad(-12.3456789);
    const double c = std::cos(pitch);
    const double s = std::sin(pitch);

    const Matrix<3,3> expected {
        {c, 0.0, -s},
        {0.0, 1.0, 0.0},
        {s, 0.0, c}
    };

    const Matrix<3,3> result = euler_to_dcm(Euler321{0.0, pitch, 0.0});

    EXPECT_TRUE(MatrixNear(result, expected, 1e-6));
}

// =================================================================================================
TEST(EulerToDCMTest, YawAngle)
{
    const double yaw = deg2rad(98.7654321);
    const double c = std::cos(yaw);
    const double s = std::sin(yaw);

    const Matrix<3,3> expected {
        {c, s, 0.0},
        {-s, c, 0.0},
        {0.0, 0.0, 1.0}
    };

    const Matrix<3,3> result = euler_to_dcm(Euler321{yaw, 0.0, 0.0});

    EXPECT_TRUE(MatrixNear(result, expected, 1e-6));
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

