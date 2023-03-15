/**
 * @file VectorMath.h
 * @author Michael Wrona
 * @date 2023-03-15
 * @brief Vector math functions.
 */

#ifndef MATHUTILS_LINALG_VECTOR_MATH_H_
#define MATHUTILS_LINALG_VECTOR_MATH_H_

#include "LinAlg/Vector.h"

namespace MathUtils {

/**
 * @brief 3D vector cross product of v1 x v2.
 *
 * @param v1 Vector 1 (LHS).
 * @param v2 Vector2 (RHS).
 * @return Vector cross product.
 */
Vector<3> cross(const Vector<3>& v1, const Vector<3>& v2);

/**
 * @brief Compute the vector dot product.
 *
 * @tparam N1 First vector length.
 * @tparam N2 Second vector length.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Dot product.
 */
template<std::size_t N1, std::size_t N2>
double dot(const Vector<N1>& v1, const Vector<N2>& v2)
{
  static_assert(N1 == N2, "Incompatible dimensions.");

  double dot_prod = 0.0;

  for (std::size_t idx = 0; idx < N1; idx++)
  {
    dot_prod += v1(idx) * v2(idx);
  }

  return dot_prod;
}

}  //  namespace MathUtils

#endif  // MATHUTILS_LINALG_VECTOR_MATH_H_