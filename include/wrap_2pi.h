/**
 * @file wrap_2pi.h
 * @author Michael Wrona
 * @date 2023-03-29
 */

#ifndef MATHUTILS_WRAP2PI_H_
#define MATHUTILS_WRAP2PI_H_

#include "constants.h"

#include <cassert>
#include <cmath>
#include <type_traits>

namespace MathUtils {

/**
 * @brief Wrap an angle within [0, 2pi) radians (360 deg).
 *
 * @tparam T Data type.
 * @param angle_rad Angle in [rad].
 * @return Angle in [rad].
 *
 * @ref https://stackoverflow.com/a/11498248
 */
template<typename T>
T wrap_2pi(T angle_rad)
{
  static_assert(std::is_fundamental<T>::value, "Fundamental types only");

  angle_rad = std::fmod(angle_rad, Constants::TWO_PI);

  if (angle_rad < 0.0)
  {
    angle_rad += Constants::TWO_PI;
  }

  return angle_rad;
}

}  // namespace MathUtils

#endif  // MATHUTILS_WRAP2PI_H_
