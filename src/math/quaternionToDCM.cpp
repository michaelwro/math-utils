/**
 * @file quaternionToDCM.cpp
 * @author michaelwro
 * @date 2025-03-30
 */

#include "math/quaternionToDCM.hpp"

#include "math/crossProductMatrix.hpp"

namespace math {

Matrix3 quaternionToDCM(const Quaternion& q) {
    // get quat components
    const double qs = q.s();
    const Matrix3 quat_mat = crossProductMatrix(q.getVectorComponent());

    // calculate DCM
    return Matrix3::identity() - (2.0 * qs * quat_mat) + (2.0 * quat_mat * quat_mat);
}

}  // namespace math