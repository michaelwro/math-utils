/**
 * @file acos_safe.h
 * @author Michael Wrona
 * @date 2023-03-25
 */

#ifndef MATHUTILS_ACOS_SAFE_H_
#define MATHUTILS_ACOS_SAFE_H_

namespace MathUtils {

/**
 * @brief Compute arcosine with bounds checks. Limits output to [pi, 0].
 *
 * @details If the input is greater than 1, 0 is returned. If the input is less than -1, pi
 * is returned.
 *
 * @param val Value to take the arccosine of, in [rad].
 * @return Arccosine of `val`.
 */
double acos_safe(const double val) noexcept;

}  // MathUtils

#endif  // MATHUTILS_ACOS_SAFE_H_
