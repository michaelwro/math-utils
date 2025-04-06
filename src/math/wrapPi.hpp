/**
 * @file wrap_pi.h
 * @author Michael Wrona
 * @date 2023-03-29
 */

#pragma once

#include <cmath>
#include <type_traits>

#include "constants.hpp"

namespace math {

/**
 * @brief Wrap an angle within [-pi, pi) radians (180 deg).
 *
 * @tparam T Data type.
 * @param angle_rad Angle in [rad].
 * @return Angle in [rad].
 *
 * @ref https://stackoverflow.com/a/11498248
 */
template <typename T>
[[nodiscard]] T wrapPi(const T angle_rad) {
    static_assert(std::is_floating_point_v<T>, "Must be float-type.");

    constexpr auto pi = static_cast<T>(constants::pi);
    constexpr auto two_pi = static_cast<T>(constants::two_pi);

    T fmod_angle = std::fmod(angle_rad + pi, two_pi);

    if (fmod_angle < 0.0) {
        fmod_angle += two_pi;
    }

    return fmod_angle - pi;
}

}  // namespace math
