/**
 * @file asin_safe.h
 * @author Michael Wrona
 * @date 2023-03-25
 */

#pragma once

#include <cassert>
#include <cmath>

#include "constants.hpp"

namespace math {

/**
 * @brief Compute arcsine with bounds checks. Limits output to [-pi/2, pi/2].
 *
 * @tparam T Input type.
 * @param val Value to take the arcsine of, in [rad].
 * @return Arcsine of `val`.
 */
template <typename T>
[[nodiscard]] T safeArcsin(const T val) noexcept {
    assert(std::abs(val) <= 1.0);

    constexpr auto pidiv2 = static_cast<T>(constants::pi_div2);

    if (val >= 1.0) {
        return pidiv2;
    }
    else if (val <= -1.0) {
        return -pidiv2;
    }

    return std::asin(val);
}

}  // namespace math
