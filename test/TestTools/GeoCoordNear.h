/**
 * @file GeoCoordNear.h
 * @author Michael Wrona
 * @date 2023-03-28
 */

#ifndef MATHUTILS_GTEST_TOOLS_GEOCOORD_NEAR_H_
#define MATHUTILS_GTEST_TOOLS_GEOCOORD_NEAR_H_

#include "Geodesy/GeoCoord.h"

#include <gtest/gtest.h>

namespace MathUtils {
namespace TestTools {

/**
 * @brief Check two MathUtils::GeoCoord for equality.
 *
 * @param mat1 First coord.
 * @param mat2 Second coord.
 * @param tol Absolute tolerance for each element. Defaults to 1e-14.
 * @returns Test assertion success or failure.
 */
::testing::AssertionResult GeoCoordNear(const MathUtils::GeoCoord& c1,
    const MathUtils::GeoCoord& c2, const double tol=1e-14);

}  // namespace TestTools
}  // namespace MathUtils

#endif  // MATHUTILS_GTEST_TOOLS_GEOCOORD_NEAR_H_
