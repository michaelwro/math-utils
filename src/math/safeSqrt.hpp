/**
 * @file sqrt_safe.h
 * @author your name
 * @date 2023-05-20
 */

#pragma once

#include <cassert>
#include <cmath>

namespace math {

/**
 * @brief "Safe" square-root returns zero for negative inputs.
 *
 * @details Prevents NaN from being returned.
 *
 * @tparam T Input type.
 * @param val Operand.
 * @return Result constrained to [ 0, inf ).
 */
template <typename T>
[[nodiscard]] auto safeSqrt(const T val) noexcept {
    constexpr auto zero = static_cast<T>(0.0);

    assert(val >= zero);

    return val >= zero ? std::sqrt(val) : zero;
}

}  // namespace math
