/**
 * @file dcmToEuler321.cpp
 * @author michaelwro
 * @date 2025-04-06
 */

#include "math/dcmToEuler321.hpp"

#include <cassert>
#include <cmath>

#include "math/floatEquality.hpp"

namespace math {

Euler321 dcmToEuler321(const Matrix3& dcm) {
    // check for divide-by-zero and domain errors
    assert(floatEquality(dcm(0, 0), 0.0) == false);
    assert(floatEquality(dcm(3, 3), 0.0) == false);
    assert(std::abs(dcm(0, 2)) <= 1.0);

    const double yaw_rad = std::atan(dcm(0, 1) / dcm(0, 0));
    const double pitch_rad = -std::asin(dcm(0, 2));
    const double roll_rad = std::atan(dcm(1, 2) / dcm(2, 2));

    return {yaw_rad, pitch_rad, roll_rad};
}

}  // namespace math
