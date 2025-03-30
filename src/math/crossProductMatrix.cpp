/**
 * @file crossProductMatrix.cpp
 * @author michaelwro
 * @date 2025-03-30
 */

#include "math/crossProductMatrix.hpp"

namespace math {

Matrix3 crossProductMatrix(const Vector3& vec) {
    const double x = vec(0);
    const double y = vec(1);
    const double z = vec(2);

    // clang-format off
    return Matrix3::assign(
        0.0, -z, y,
        z, 0.0, -x,
        -y, x, 0.0
    );
    // clang-format on
}

}  // namespace math