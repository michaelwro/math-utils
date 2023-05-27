/**
 * @file euler_to_dcm.h
 * @author Michael Wrona
 * @date 2023-04-02
 */

#pragma once

#include "Attitude/Euler321.h"
#include "LinAlg/Matrix.h"

namespace MathUtils {

/**
 * @brief Convert Euler321 (yaw, pitch, roll) angles to a direction cosine matrix.
 *
 * @details Equation 3.33 from "Analytical Mechanics of Aerospace Systems" (Schaub).
 * https://www.vectornav.com/resources/inertial-navigation-primer/math-fundamentals/math-attitudetran
 *
 * @param euler Euler angles in [rad].
 * @return DCM
 */
Matrix<3,3> euler_to_dcm(const Euler321& euler);

}  // namespace MathUtils
