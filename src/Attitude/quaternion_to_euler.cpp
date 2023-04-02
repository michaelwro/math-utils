/**
 * @file quaternion_to_euler.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "Attitude/quaternion_to_euler.h"

#include "asin_safe.h"
#include "constants.h"

#include <cmath>

namespace MathUtils {

Euler321 quaternion_to_euler(const Quaternion& q)
{
    const double q0 = q(0);

    const double q1 = q(1);
    const double q11 = q1 * q1;

    const double q2 = q(2);
    const double q22 = q2 * q2;

    const double q3 = q(3);
    const double q33 = q3 * q3;

    /**
     * No pitch singularity (close to +/- 90 deg) checks performed here.
     * Note that -asin(2.0 * ((q1*q3) - (q0*q2))) = asin(2.0 * ((q0*q2) - (q1*q3)))
     * Below assumes unit quaternion ||q|| = 1
     */
    return Euler321 {
        std::atan2((q1*q2) + (q0*q3), 0.5 - q22 - q33),
        asin_safe(2.0 * ((q0*q2) - (q1*q3))),
        std::atan2((q2*q3) + (q0*q1), 0.5 - q22 - q11)
    };
}

}  // namespace MathUtils
