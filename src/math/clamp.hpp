/**
 * @file clamp.hpp
 * @author michaelwro
 * @date 2025-04-06
 */

#pragma once

namespace math {

/**
 * @brief Restrict a value to be within `[min, max]`.
 *
 * @tparam T Data type.
 * @param val Input value.
 * @param min Minimum bound for `val`.
 * @param max Maximum value for `val`.
 * @return `val` restricted within bounds.
 */
template <typename T>
T clamp(T val, const T min, const T max) {
    assert(min < max);

    if (val < min) {
        return min;
    }
    else if (val > max) {
        return max;
    }

    return val;
}

}  // namespace math
