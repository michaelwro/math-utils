/**
 * @file quaternionToDCM.h
 * @author Michael Wrona
 * @date 2023-03-19
 */

#pragma once

#include "math/Matrix3.hpp"
#include "math/Quaternion.hpp"

namespace math {

/**
 * @brief Convert a quaternion to the corresponding transformation matrix (DCM). Equation
 * 45 from https://sites.utexas.edu/near/files/2022/07/Rotations.pdf
 *
 * @param quat The quaternion.
 * @return Corresponding transformation matrix.
 */
Matrix3 quaternionToDCM(const Quaternion& quat);

}  // namespace math
