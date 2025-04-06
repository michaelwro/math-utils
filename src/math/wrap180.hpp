/**
 * @file wrap180.hpp
 * @author michaelwro
 * @date 2025-04-06
 */

#pragma once

#include <cmath>
#include <type_traits>

namespace math {

/**
 * @brief Wrap an angle to within `[-180, 180]` DEGREES
 *
 * @tparam T Input type.
 * @param angle_deg [deg] Angle.
 * @return [deg] Wrapped angle.
 */
template <typename T>
[[nodiscard]] T wrap180(const T angle_deg) {
    static_assert(std::is_floating_point_v<T>, "Must be float-type.");

    constexpr auto one_eighty = static_cast<T>(180);
    constexpr auto three_sixty = static_cast<T>(360);

    T fmod_angle = std::fmod(angle_deg + one_eighty, three_sixty);

    if (fmod_angle < 0.0) {
        fmod_angle += three_sixty;
    }

    return fmod_angle - one_eighty;
}

}  // namespace math
