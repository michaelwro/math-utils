/**
 * @file quaternion_derivative.h
 * @author Michael Wrona
 * @date 2023-03-15
 */

#pragma once

#include "Attitude/Quaternion.h"
#include "LinAlg/Vector.h"

namespace MathUtils {

/**
 * @brief Return q-dot quaternion kinematic differential equation.
 *
 * @details Equation 3.103 from "Analytical Mechanics of Aerospace Systems."
 *
 * @param q Quaternion.
 * @param w_rps Angular rates in [rad/sec]
 * @return Q-dot (time derivative).
 *
 * @ref https://repositories.lib.utexas.edu/bitstream/handle/2152/74954/Hans-JoachimWuensche.pdf?sequence=2&isAllowed=y
 */
Vector<4> quaternion_derivative(const Quaternion& q, Vector<3> w_rps);

}  // namespace MathUtils
