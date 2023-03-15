/**
 * @file QuaternionMath.h
 * @author Michael Wrona
 * @date 2023-03-15
 * @brief Quaternion math functions.
 */

#ifndef MATHUTILS_ATTITUDE_QUATERNION_MATH_H_
#define MATHUTILS_ATTITUDE_QUATERNION_MATH_H_

#include "Attitude/Quaternion.h"
#include "LinAlg/Vector.h"

namespace MathUtils {

/**
 * @brief Rotate a vector defined by a quaternion.
 *
 * @details Sequence loos like `q_a = rotate(q_a_b, v_b)`
 *
 * Equation from "Analytical Mechanics of Aerospace Systems" (H. Schaub et. al.).
 *
 * @param q_a_b Quaternion rotation defining the rotation from frame "B" to "A."
 * @param v_b Vector in frame "B."
 * @return Vector rotated to frame "A."
 */
Vector<3> quatrotate(const Quaternion& q_a_b, const Vector<3>& v_b);

}  // namespace MathUtils

#endif  // MATHUTILS_ATTITUDE_QUATERNION_MATH_H_
