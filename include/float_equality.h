/**
 * @file float_equality.h
 * @author michaelwro
 * @date 2023-03-17
 */

#ifndef MATHUTILS_FLOAT_EQUALITY_H_
#define MATHUTILS_FLOAT_EQUALITY_H_

#include <algorithm>
#include <cassert>
#include <limits>
#include <type_traits>

namespace MathUtils {

/**
 * @brief Check if two floating-point value are "close enough" to be equal.
 *
 * @details Uses absolute and relative tolerance.
 *
 * @param a First value.
 * @param b Second value.
 * @return True if "close enough," false otherwise.
 *
 * @ref https://stackoverflow.com/a/15012792
 * @ref https://realtimecollisiondetection.net/blog/?p=89
 * @ref https://floating-point-gui.de/errors/comparison/
 */

template<typename T>
inline bool float_equality(const T a, const T b)
{
  static_assert(std::is_floating_point<T>::value, "Must be floating-point type.");

  return std::abs(a - b) <= std::numeric_limits<T>::epsilon() * std::max(
    {static_cast<T>(1.0), a, b},
    [](const T val1, const T val2){return val1 < val2;}
  );
}

}  // namespace MathUtils

#endif  // MATHUTILS_FLOAT_EQUALITY_H_
