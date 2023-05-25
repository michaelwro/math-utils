/**
 * @file acos_safe.h
 * @author Michael Wrona
 * @date 2023-03-25
 */

#pragma once

#include "constants.h"

#include <cmath>
#include <concepts>
#include <cassert>

namespace MathUtils {

/**
 * @brief Compute arcosine with bounds checks. Limits output to [pi, 0].
 *
 * @tparam T Input type.
 * @param val Value to take the arccosine of, in [rad].
 * @return Arccosine of `val`.
 */
template<typename T>
requires std::floating_point<T>
[[nodiscard]] T acos_safe(const T val) noexcept
{
    assert(std::abs(val) <= 1.0);

    if (val >= 1.0)
    {
        return static_cast<T>(0.0);
    }
    else if (val <= -1.0)
    {
        return static_cast<T>(Constants::PI);
    }

    return std::acos(val);
}

}  // namespace MathUtils
