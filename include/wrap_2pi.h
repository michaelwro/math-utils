/**
 * @file wrap_2pi.h
 * @author Michael Wrona
 * @date 2023-03-29
 */

#pragma once

#include "constants.h"

#include <cassert>
#include <cmath>
#include <type_traits>

namespace MathUtils {

/**
 * @brief Wrap an angle within [0, 2pi) radians (360 deg).
 *
 * @tparam T Data type.
 * @param angle_rad Angle in [rad].
 * @return Angle in [rad].
 *
 * @ref https://stackoverflow.com/a/11498248
 */
template<typename T>
double wrap_2pi(const T angle_rad)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    double dangle_rad = std::fmod(static_cast<double>(angle_rad), Constants::TWO_PI);

    if (dangle_rad < 0.0) {
        dangle_rad += Constants::TWO_PI;
    }

    return dangle_rad;
}

}    // namespace MathUtils
