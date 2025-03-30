/**
 * @file acos_safe.h
 * @author Michael Wrona
 * @date 2023-03-25
 */

#pragma once

#include <cassert>
#include <cmath>

#include "constants.hpp"

namespace math {

/**
 * @brief Compute arcosine with bounds checks. Limits output to [pi, 0].
 *
 * @tparam T Input type.
 * @param val Value to take the arccosine of, in [rad].
 * @return Arccosine of `val`.
 */
template <typename T>
[[nodiscard]] T acos_safe(const T val) {
    assert(std::abs(val) <= 1.0);

    if (val >= 1.0) {
        return static_cast<T>(0.0);
    }
    else if (val <= -1.0) {
        return static_cast<T>(constants::pi);
    }

    return std::acos(val);
}

}  // namespace math
