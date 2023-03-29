/**
 * @file wrap_pi.h
 * @author Michael Wrona
 * @date 2023-03-29
 */

#ifndef MATHUTILS_WRAPPI_H_
#define MATHUTILS_WRAPPI_H_

#include "constants.h"

#include <cassert>
#include <cmath>
#include <numeric>

namespace MathUtils {

/**
 * @brief Wrap an angle within [-pi/2, pi/2) radians (180 deg).
 *
 * @param angle_rad Angle in [rad].
 * @return Angle in [rad].
 *
 * @ref https://stackoverflow.com/a/11498248
 */
float wrap_pi(float angle_rad);

/**
 * @brief Wrap an angle within [-pi/2, pi/2) radians (180 deg).
 *
 * @param angle_rad Angle in [rad].
 * @return Angle in [rad].
 *
 * @ref https://stackoverflow.com/a/11498248
 */
double wrap_pi(double angle_rad);

/**
 * @brief Wrap an angle within [-pi/2, pi/2) radians (180 deg).
 *
 * @tparam T Data type.
 * @param angle_rad Angle in [rad].
 * @return Angle in [rad].
 *
 * @ref https://stackoverflow.com/a/11498248
 */
template<typename T>
T wrap_pi(T angle_rad)
{
  static_assert(std::numeric_limits<T>::is_integer, "Integer only.");

  angle_rad = std::fmod(angle_rad + Constants::PI, Constants::TWO_PI);

  if (angle_rad < 0.0)
  {
    angle_rad += Constants::TWO_PI;
  }

  return angle_rad - Constants::PI;
}

}  // namespace MathUtils

#endif  // MATHUTILS_WRAPPI_H_
