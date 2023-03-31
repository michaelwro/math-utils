/**
 * @file QuaternionNear.h
 * @author Michael Wrona
 * @date 2023-03-19
 */

#ifndef MATHUTILS_GTEST_TOOLS_QUATERNION_NEAR_H_
#define MATHUTILS_GTEST_TOOLS_QUATERNION_NEAR_H_

#include "Attitude/Quaternion.h"

#include <cmath>
#include <gtest/gtest.h>
#include <iomanip>
#include <limits>
#include <sstream>

namespace MathUtils {
namespace TestTools {

/**
 * @brief Check two MathUtils::Quaternion for equality.
 *
 * @param q1 First quaternion.
 * @param q2 Second quaternion.
 * @param tol Absolute tolerance for each element. Defaults to 1e-14.
 * @returns Test assertion success or failure.
 *
 * @ref https://stackoverflow.com/a/7121785
 */

::testing::AssertionResult QuaternionNear(const MathUtils::Quaternion& q1,
    const MathUtils::Quaternion& q2,
    const double tol=1e-14)
{
    bool success = true;
    std::stringstream error_msgs;

    for (std::size_t ii = 0; ii < 4; ii++) {
        const double diff = std::abs(q1(ii) - q2(ii));

        if (diff > tol) {
            success = false;
            error_msgs << "\nElement (" << ii << ") differs by " << std::scientific << diff;
        }
    }

    if (!success) {
        return ::testing::AssertionFailure() << "Quaternions are not equal." << error_msgs.str();
    }

    return ::testing::AssertionSuccess();
}

}  // namespace TestTools
}  // namespace MathUtils

#endif  // MATHUTILS_GTEST_TOOLS_QUATERNION_NEAR_H_
