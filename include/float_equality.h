/**
 * @file float_equality.h
 * @author Michael Wrona
 * @date 2023-03-17
 */

#pragma once

#include <algorithm>
#include <concepts>
#include <limits>

namespace MathUtils {

/**
 * @brief Check if two floating-point value are "close enough" to be equal.
 *
 * @details Uses absolute and relative tolerance.
 *
 * @tparam T variable type.
 * @param a First value.
 * @param b Second value.
 * @return True if "close enough," false otherwise.
 *
 * @ref https://stackoverflow.com/a/15012792
 * @ref https://realtimecollisiondetection.net/blog/?p=89
 * @ref https://floating-point-gui.de/errors/comparison/
 */
template<typename T>
requires std::floating_point<T>
[[nodiscard]] inline bool float_equality(const T a, const T b)
{
    return std::abs(a - b) <= std::numeric_limits<T>::epsilon() * std::max(
        {static_cast<T>(1.0), a, b},
        [](const T val1, const T val2){return val1 < val2;}
    );
}

}    // namespace MathUtils
