/**
 * @file dcm_to_quaternion.h
 * @author Michael Wrona
 * @date 2023-03-26
 */

#pragma once

#include "LinAlg/Matrix.h"
#include "Attitude/Quaternion.h"

namespace MathUtils {

/**
 * @brief Convert a DCM to a quaternion.
 *
 * @details "Analytical Mechanics of Aerospace Systems" (Schaub et. al.) Stanley method.
 *
 * @param dcm DCM to convert to quaternion.
 * @return Quaternion corresponding to the DCM.
 *
 * @exception std::runtime_error If the DCM could not be converted (something weird happened
 * internally).
 */
Quaternion dcm_to_quaternion(const Matrix<3,3>& dcm);

}  // namespace MathUtils
