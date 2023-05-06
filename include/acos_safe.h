/**
 * @file acos_safe.h
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
 * @brief Compute arcosine with bounds checks. Limits output to [pi, 0].
 *
 * @details If the input is greater than 1, 0 is returned. If the input is less than -1, pi
 * is returned.
 *
 * @tparam T Input type.
 * @param val Value to take the arccosine of, in [rad].
 * @return Arccosine of `val`.
 */
template<typename T>
[[nodiscard]] double acos_safe(const T val) noexcept
{
    static_assert(std::is_floating_point<T>::value, "Fundamental types only.");
    assert(std::abs(val) <= 1.0);

    if (val >= 1.0)
    {
        return 0.0;
    }
    else if (val <= -1.0)
    {
        return Constants::PI;
    }

    return std::acos(val);
}

}  // namespace MathUtils
