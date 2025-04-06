/**
 * @file wrap_2pi.h
 * @author Michael Wrona
 * @date 2023-03-29
 */

#pragma once

#include <cmath>
#include <type_traits>

#include "constants.hpp"

namespace math {

/**
 * @brief Wrap an angle within [0, 2pi) radians (360 deg).
 *
 * @tparam T Data type.
 * @param angle_rad Angle in [rad].
 * @return Angle in [rad].
 *
 * @ref https://stackoverflow.com/a/11498248
 */
template <typename T>
[[nodiscard]] T wrap2pi(const T angle_rad) {
    static_assert(std::is_floating_point_v<T>, "Must be float-type.");

    constexpr auto two_pi = static_cast<T>(constants::two_pi);
    T fmod_angle = std::fmod(angle_rad, two_pi);

    if (fmod_angle < 0.0) {
        fmod_angle += two_pi;
    }

    return fmod_angle;
}

}  // namespace math
