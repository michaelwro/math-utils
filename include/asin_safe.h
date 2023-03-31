/**
 * @file asin_safe.h
 * @author Michael Wrona
 * @date 2023-03-25
 */

#ifndef MATHUTILS_ASIN_SAFE_H_
#define MATHUTILS_ASIN_SAFE_H_

namespace MathUtils {

/**
 * @brief Compute arcsine with bounds checks. Limits output to [-pi/2, pi/2].
 *
 * @details If the input is greater than 1, pi/2 is returned. If the input is less than -1, -pi/2
 * is returned.
 *
 * @param val Value to take the arcsine of, in [rad].
 * @return Arcsine of `val`.
 */
double asin_safe(const double val) noexcept;

}  // MathUtils

#endif  // MATHUTILS_ASIN_SAFE_H_
