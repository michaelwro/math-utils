/**
 * @file quaternion_to_euler.h
 * @author Michael Wrona
 * @date 2023-04-02
 */

#pragma once

#include "Attitude/Euler321.h"
#include "Attitude/Quaternion.h"

namespace MathUtils {

/**
 * @brief Convert a quaternion to 321 Euler angles.
 *
 * @details No pitch singularity checks.
 *
 * @param q Quaternion to convert.
 * @return Quaternion converted to 321 Euler angles [rad].
 *
 * @ref https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles#Quaternion_to_Euler_angles_(in_3-2-1_sequence)_conversion
 */
Euler321 quaternion_to_euler(const Quaternion& q);

}  // namespace MathUtils
