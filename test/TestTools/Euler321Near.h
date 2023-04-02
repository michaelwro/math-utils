/**
 * @file Euler321Near.h
 * @author Michael Wrona
 * @date 2023-04-02
 */

#ifndef MATHUTILS_GTEST_TOOLS_EULER321_NEAR_H_
#define MATHUTILS_GTEST_TOOLS_EULER321_NEAR_H_

#include "Attitude/Euler321.h"

#include <gtest/gtest.h>


namespace MathUtils {
namespace TestTools {

/**
 * @brief Check two MathUtils::Euler321 for equality.
 *
 * @param mat1 First Euler321.
 * @param mat2 Second Euler321.
 * @param tol Absolute tolerance for each element. Defaults to 1e-14.
 * @returns Test assertion success or failure.
 */
::testing::AssertionResult Euler321Near(const Euler321& e1,
    const Euler321& e2, const double tol=1e-14);

}  // namespace TestTools
}  // namespace MathUtils

#endif  // MATHUTILS_GTEST_TOOLS_EULER321_NEAR_H_
