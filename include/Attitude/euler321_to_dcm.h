/**
 * @file euler321_to_dcm.h
 * @author Michael Wrona
 * @date 2023-04-02
 */

#ifndef MATHUTILS_EULER321_TO_DCM_H_
#define MATHUTILS_EULER321_TO_DCM_H_

#include "LinAlg/Matrix.h"

namespace MathUtils {

/**
 * @brief Convert Euler 321 (yaw, pitch, roll) angles to a direction cosine matrix.
 *
 * @details Equation 3.33 from "Analytical Mechanics of Aerospace Systems" (Schaub).
 *
 * @param yaw_rad Yaw angle [rad].
 * @param pitch_rad Pitch angle [rad].
 * @param roll_rad Roll angle [rad].
 * @return DCM
 *
 * @ref https://www.vectornav.com/resources/inertial-navigation-primer/math-fundamentals/math-attitudetran
 */
Matrix<3,3> euler321_to_dcm(const double yaw_rad, const double pitch_rad, const double roll_rad);

}  // namespace MathUtils

#endif  // MATHUTILS_EULER321_TO_DCM_H_
