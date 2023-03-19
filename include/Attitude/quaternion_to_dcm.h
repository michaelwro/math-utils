/**
 * @file quaternion_to_dcm.h
 * @author Michael Wrona
 * @date 2023-03-19
 */

#ifndef MATHUTILS_ATTITUDE_QUATERNION_TO_DCM_H_
#define MATHUTILS_ATTITUDE_QUATERNION_TO_DCM_H_

#include "Attitude/Quaternion.h"
#include "LinAlg/Matrix.h"

namespace MathUtils {

/**
 * @brief Convert quaternion to direction cosine matrix.
 *
 * @details Equation from "Analytical Mechanics of Aerospace Systems" (H. Schaub et. al.).
 *
 * @param q Quaternion.
 * @return Corresponding DCM.
 */
Matrix<3,3> quaternion_to_dcm(const Quaternion& q);

}  // namespace MathUtils

#endif  // MATHUTILS_ATTITUDE_QUATERNION_TO_DCM_H_
