/**
 * @file test_dcm_to_quaternion.cpp
 * @author Michael Wrona
 * @date 2023-03-26
 */

#include "Attitude/Quaternion.h"
#include "LinAlg/Matrix.h"
#include "Attitude/dcm_to_quaternion.h"
#include "TestTools/QuaternionNear.h"

#include <cmath>
#include <gtest/gtest.h>
#include <string>

using MathUtils::Quaternion;
using MathUtils::TestTools::QuaternionNear;
using MathUtils::Matrix;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-dcm_to_quaternion_xml");

// ====================================================================================================================
TEST(DcmToQuaternionTest, SchaubTextbookExample)
{
  // Example 3.6 from "Analytical Mechanics of Aerospace Systems" (Schaub et. al.)
  const double tolerance = 1e-5;

  const Matrix<3,3> dcm {
    0.892539, 0.157379, -0.422618,
    -0.275451, 0.932257, -0.234570,
    0.357073, 0.325773, 0.875426
  };

  const Quaternion expected {0.961798, -0.14565, 0.202665, 0.112505};

  const Quaternion result = MathUtils::dcm_to_quaternion(dcm);

  EXPECT_TRUE(QuaternionNear(result, expected, tolerance));
}

// ====================================================================================================================
TEST(DcmToQuaternionTest, MathWorksExample1)
{
  // Example from https://www.mathworks.com/help/aerotbx/ug/dcm2quat.html
  const double tolerance = 1e-4;

  const Matrix<3,3> dcm {
    0, 1, 0,
    1, 0, 0,
    0, 0, -1
  };

  const Quaternion expected {0, 0.7071, 0.7071, 0};

  const Quaternion result = MathUtils::dcm_to_quaternion(dcm);

  EXPECT_TRUE(QuaternionNear(result, expected, tolerance));
}

// ====================================================================================================================
TEST(DcmToQuaternionTest, MathWorksExample2)
{
  // Example from https://www.mathworks.com/help/aerotbx/ug/dcm2quat.html
  const double tolerance = 1e-4;

  const Matrix<3,3> dcm {
    0.4330, 0.2500, -0.8660,
    0.1768, 0.9186, 0.3536,
    0.8839, -0.3062, 0.3536
  };

  const Quaternion expected {0.8224, 0.2006, 0.5320, 0.0223};

  const Quaternion result = MathUtils::dcm_to_quaternion(dcm);

  EXPECT_TRUE(QuaternionNear(result, expected, tolerance));
}

// ====================================================================================================================
TEST(DcmToQuaternionTest, MathWorksExample3)
{
  // Example from https://www.mathworks.com/help/aerotbx/ug/quat2dcm.html
  const double tolerance = 1e-4;

  const Matrix<3,3> dcm {
    0, 0, -1,
    0, 1, 0,
    1, 0, 0
  };

  const Quaternion expected {1, 0, 1, 0};

  const Quaternion result = MathUtils::dcm_to_quaternion(dcm);

  EXPECT_TRUE(QuaternionNear(result, expected, tolerance));
}

// ====================================================================================================================
TEST(DcmToQuaternionTest, MathWorksExample4)
{
  // Example from https://www.mathworks.com/help/aerotbx/ug/quat2dcm.html
  const double tolerance = 1e-4;

  const Matrix<3,3> dcm {
    0.8519, 0.3704, -0.3704,
    0.0741, 0.6148, 0.7852,
    0.5185, -0.6963, 0.4963
  };

  const Quaternion expected {1, 0.5, 0.3, 0.1};

  const Quaternion result = MathUtils::dcm_to_quaternion(dcm);

  EXPECT_TRUE(QuaternionNear(result, expected, tolerance));
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
