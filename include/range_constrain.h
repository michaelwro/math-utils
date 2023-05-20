/**
 * @file range_constrain.h
 * @author Michael Wrona
 * @date 2023-05-20
 */

#pragma once

#include <cassert>
#include <type_traits>

namespace MathUtils {

/**
 * @brief Constrain number to be within a range.
 *
 * @tparam T Input type.
 * @param val Value to constrain.
 * @param lower Lower limit.
 * @param upper Upper limit.
 * @return `val` constrained to be within [lower, upper].
 */
template<typename T, std::enable_if_t<std::is_fundamental<T>::value, bool> = true>
[[nodiscard]] T range_constrain(const T val, const T lower, const T upper) noexcept
{
    if (val < lower)
    {
        return lower;
    }

    if (val > upper)
    {
        return upper;
    }

    return val;
}

}  // namespace MathUtils
