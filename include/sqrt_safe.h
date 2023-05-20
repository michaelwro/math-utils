/**
 * @file sqrt_safe.h
 * @author your name
 * @date 2023-05-20
 */

#pragma once

#include <cmath>
#include <type_traits>

namespace MathUtils {

/**
 * @brief "Safe" square-root returns zero for negative inputs.
 *
 * @details Prevents NaN from being returned.
 *
 * @tparam T Input type.
 * @param val Operand.
 * @return Result constrained to [ 0, sqrt(val) ).
 */
template<typename T>
[[nodiscard]] auto sqrt_safe(const T val) noexcept
{
    return val >= static_cast<T>(0.0) ? std::sqrt(val) : static_cast<T>(0.0);
}

}  // namespace MathUtils
