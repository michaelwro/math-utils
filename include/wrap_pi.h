/**
 * @file wrap_pi.h
 * @author Michael Wrona
 * @date 2023-03-29
 */

#ifndef MATHUTILS_WRAPPI_H_
#define MATHUTILS_WRAPPI_H_

#include "constants.h"

#include <cassert>
#include <cmath>
#include <type_traits>

namespace MathUtils {

/**
 * @brief Wrap an angle within [-pi/2, pi/2) radians (180 deg).
 *
 * @tparam T Data type.
 * @param angle_rad Angle in [rad].
 * @return Angle in [rad].
 *
 * @ref https://stackoverflow.com/a/11498248
 */
template<typename T>
double wrap_pi(const T angle_rad)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    double dangle_rad = std::fmod(
        static_cast<double>(angle_rad) + Constants::PI, Constants::TWO_PI
    );

    if (dangle_rad < 0.0) {
        dangle_rad += Constants::TWO_PI;
    }

    return dangle_rad - Constants::PI;
}

}    // namespace MathUtils

#endif    // MATHUTILS_WRAPPI_H_
