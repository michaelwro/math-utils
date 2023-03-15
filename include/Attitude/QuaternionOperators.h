/**
 * @file QuaternionOperators.h
 * @author Michael Wrona
 * @date 2023-03-15
 * @brief Quaternion operator overloads.
 */

#ifndef MATHUTILS_ATTITUDE_QUATERNION_OPERATORS_H_
#define MATHUTILS_ATTITUDE_QUATERNION_OPERATORS_H_

#include "Attitude/Quaternion.h"

namespace MathUtils {

/**
 * @brief Compute the quaternion product. Normalizes result.
 *
 * @details `q_a_c = q_a_b * q_b_c`
 *
 * "Analytical Mechanics of Aerospace Systems" equation 3.97.
 *
 * @param q_b First quaternion.
 * @param q_c Second quaternion.
 * @return Quaternion product q_b * q_c.
 */
Quaternion operator*(const Quaternion& q_b, const Quaternion& q_c);

}  // namespace MathUtils

#endif  // MATHUTILS_ATTITUDE_QUATERNION_OPERATORS_H_
