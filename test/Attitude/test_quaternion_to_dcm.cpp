/**
 * @file test_quaternion_to_dcm.cpp
 * @author Michael Wrona
 * @date 2023-03-19
 */

#include "Attitude/Quaternion.h"
#include "LinAlg/Matrix.h"
#include "Attitude/quaternion_to_dcm.h"
#include "TestTools/MatrixNear.h"

#include <gtest/gtest.h>
#include <string>

using MathUtils::Matrix;
using MathUtils::Quaternion;
using MathUtils::TestTools::MatrixNear;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-quaternion_to_dcm.xml");

// ====================================================================================================================
TEST(QuaternionToDCMTest, UnityQuatIsIdentityMatrix)
{
  Quaternion q;

  Matrix<3,3> dcm = MathUtils::quaternion_to_dcm(q);

  EXPECT_TRUE(MatrixNear(dcm, Matrix<3,3>::identity()));

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

