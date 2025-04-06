/**
 * @file wrap360.hpp
 * @author michaelwro
 * @date 2025-04-06
 */

#pragma once

#include <cmath>
#include <type_traits>

namespace math {

/**
 * @brief Wrap an angle within [0, 360) DEGREES.
 *
 * @tparam T The typer.
 * @param angle_deg [deg] Angle.
 * @returns [deg] WRapped angle.
 */
template <typename T>
[[nodiscard]] T wrap2pi(const T angle_deg) {
    static_assert(std::is_floating_point_v<T>, "Must be float-type.");

    constexpr auto three_sixty = static_cast<T>(360);
    T fmod_angle = std::fmod(angle_deg, three_sixty);

    if (fmod_angle < 0.0) {
        fmod_angle += three_sixty;
    }

    return fmod_angle;
}

}  // namespace math
