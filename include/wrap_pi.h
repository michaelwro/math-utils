/**
 * @file wrap_pi.h
 * @author Michael Wrona
 * @date 2023-03-29
 */

#pragma once

#include "constants.h"

#include <cmath>
#include <concepts>

namespace MathUtils {

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
requires std::floating_point<T>
[[nodiscard]] T wrap_pi(const T angle_rad)
{
    constexpr auto pi = static_cast<T>(Constants::PI);
    constexpr auto two_pi = static_cast<T>(Constants::TWO_PI);

    T dangle_rad = std::fmod(angle_rad + pi, two_pi);

    if (dangle_rad < 0.0)
    {
        dangle_rad += two_pi;
    }

    return dangle_rad - pi;
}

}    // namespace MathUtils
