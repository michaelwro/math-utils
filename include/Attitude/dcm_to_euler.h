/**
 * @file dcm_to_euler.h
 * @author Michael Wrona
 * @date 2023-04-02
 */

#pragma once

#include "Attitude/Euler321.h"
#include "LinAlg/Matrix.h"

namespace MathUtils {

/**
 * @brief Convert a direction cosine matrix to 321 Euler angles.
 *
 * @details No pitch singularity checks.
 * Equations from "Analytical Mechanics of Aerospace Systems" (Schaub).
 *
 * @param dcm DCM to convert.
 * @return Corresponding 321 Euler angles.
 *
 * @ref https://www.vectornav.com/resources/inertial-navigation-primer/math-fundamentals/math-attitudetran
 */
Euler321 dcm_to_euler(const Matrix<3,3>& dcm);

}  // namespace MathUtils
