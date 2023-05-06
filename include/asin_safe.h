/**
 * @file asin_safe.h
 * @author Michael Wrona
 * @date 2023-03-25
 */

#pragma once

#include "constants.h"

#include <cmath>
#include <cassert>
#include <type_traits>

namespace MathUtils {

/**
 * @brief Compute arcsine with bounds checks. Limits output to [-pi/2, pi/2].
 *
 * @details If the input is greater than 1, pi/2 is returned. If the input is less than -1, -pi/2
 * is returned.
 *
 * @tparam T Input type.
 * @param val Value to take the arcsine of, in [rad].
 * @return Arcsine of `val`.
 */
template<typename T>
[[nodiscard]] T asin_safe(const T val) noexcept
{
    static_assert(std::is_floating_point<T>::value, "Fundamental types only.");
    assert(std::abs(val) <= 1.0);

    if (val >= 1.0)
    {
        return Constants::PI_DIV2;
    }
    else if (val <= -1.0)
    {
        return -Constants::PI_DIV2;
    }

    return std::asin(val);
}

}  // MathUtils
