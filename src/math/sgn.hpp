/**
 * @file sgn.hpp
 * @author michaelwro
 * @date 2025-03-23
 */

#pragma once

#include <cmath>
#include <type_traits>

namespace math {

/**
 * @brief Signum `sgn` function. Returns +1, 0, or -1.
 *
 * @tparam T Variable type.
 * @param value Signed input value.
 * @return +1, 0, or -1.
 */
template <typename T>
T sgn(const T value) {
    static_assert(std::is_integral_v<T> or std::is_floating_point_v<T>, "Invalid type.");
    return std::copysign(static_cast<T>(1.0), value);
}

}  // namespace math