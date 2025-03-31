/**
 * @file quaternionToRotMatrix.hpp
 * @author michaelwro
 * @date 2025-03-30
 */

#pragma once

#include "math/Matrix3.hpp"
#include "math/Quaternion.hpp"

namespace math {

/**
 * @brief Convert a quaternion that represents an ACITVE rotation to the corresponding
 * rotation matrix. Equation 44 from
 * https://sites.utexas.edu/near/files/2022/07/Rotations.pdf
 *
 * @param quat The quaternion.
 * @return Corresponding rotation matrix.
 */
Matrix3 quaternionToRotMatrix(const Quaternion& quat);

}  // namespace math