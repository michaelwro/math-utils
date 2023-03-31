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
#include <numeric>

namespace MathUtils {

/**
 * @brief Wrap an angle within [0, 2pi) radians (360 deg).
 *
 * @param angle_rad Angle in [rad].
 * @return Angle in [rad].
 *
 * @ref https://stackoverflow.com/a/11498248
 */
float wrap_2pi(float angle_rad);

/**
 * @brief Wrap an angle within [0, 2pi) radians (360 deg).
 *
 * @param angle_rad Angle in [rad].
 * @return Angle in [rad].
 *
 * @ref https://stackoverflow.com/a/11498248
 */
double wrap_2pi(double angle_rad);

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
double wrap_2pi(const T angle_rad)
{
    static_assert(std::numeric_limits<T>::is_integer, "Integer only.");

    double d_angle_rad = std::fmod(static_cast<double>(angle_rad), Constants::TWO_PI);

    if (d_angle_rad < 0.0) {
        d_angle_rad += Constants::TWO_PI;
    }

    return d_angle_rad;
}

}    // namespace MathUtils

#endif    // MATHUTILS_WRAP2PI_H_
