/**
 * @file crossProductMatrix.hpp
 * @author michaelwro
 * @date 2025-03-30
 */

#pragma once

#include "math/Matrix3.hpp"
#include "math/Vector3.hpp"

namespace math {

/**
 * @brief Get the skew-symmetric matrix to calculate cross products via matrix-vector
 * multiplication. From
 * https://en.wikipedia.org/wiki/Cross_product#Conversion_to_matrix_multiplication
 *
 * @param vec The vector.
 * @return Cross product matrix.
 */
Matrix3 crossProductMatrix(const Vector3& vec);

}  // namespace math