/**
 * @file quaternion_derivative.cpp
 * @author Michael Wrona
 * @date 2023-03-15
 */

#include "Attitude/quaternion_derivative.h"

namespace MathUtils {

Vector<4> quaternion_derivative(const Quaternion& q, Vector<3> w_rps)
{
    return Vector<4>({
        -0.5 * ((w_rps(0) * q(1)) + (w_rps(1) * q(2)) + (w_rps(2) * q(3))),
        0.5 * ((w_rps(0) * q(0)) + (w_rps(2) * q(2)) - (w_rps(1) * q(3))),
        0.5 * ((w_rps(1) * q(0)) - (w_rps(2) * q(1)) + (w_rps(0) * q(3))),
        0.5 * ((w_rps(2) * q(0)) + (w_rps(1) * q(1)) - (w_rps(0) * q(2)))
    });
}

}  // namespace MathUtils
