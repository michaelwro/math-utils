/**
 * @file quaternionToRotMatrix.cpp
 * @author michaelwro
 * @date 2025-03-30
 */

#include "math/quaternionToRotMatrix.hpp"

#include "math/crossProductMatrix.hpp"

namespace math {

Matrix3 quaternionToRotMatrix(const Quaternion& quat) {
    // get quat components
    const double qs = quat.s();
    const Matrix3 quat_mat = crossProductMatrix(quat.getVectorComponent());

    // calculate DCM
    return Matrix3::identity() + (2.0 * qs * quat_mat) + (2.0 * quat_mat * quat_mat);
}

}  // namespace math