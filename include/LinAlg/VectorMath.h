/**
 * @file VectorMath.h
 * @author Michael Wrona
 * @date 2023-03-08
 * @brief Vector math functions and operator overloads.
 */

#ifndef MATHUTILS_LINALG_VECTORMATH_H_
#define MATHUTILS_LINALG_VECTORMATH_H_

#include "Vector.h"

#include <cstddef>


namespace MathUtils { namespace LinAlg {


/**
 * @brief Add two vectors.
 *
 * @tparam N_LEFT First vector length.
 * @tparam N_RIGHT Second vector length.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Vector sum.
 */
template<std::size_t N_LEFT, std::size_t N_RIGHT>
Vector<N_LEFT> operator+(const Vector<N_LEFT>& v1, const Vector<N_RIGHT>& v2);


/**
 * @brief Vector-scalar multiplication.
 *
 * @tparam N Length of the vector.
 * @tparam T Scalar type.
 * @param vec Vector to be multiplied by the scalar.
 * @param scalar Scalar to multiply the vector by.
 * @return Vector-scalar multiplication result.
 */
template<std::size_t N, typename T>
Vector<N> operator*(const Vector<N>& vec, const T scalar);


/**
 * @brief Scalar-vector multiplication.
 *
 * @tparam N Length of the vector.
 * @tparam T Scalar type.
 * @param scalar Scalar to multiply the vector by.
 * @param vec Vector to be multiplied by the scalar.
 * @return Scalar-vector multiplication result.
 */
template<std::size_t N, typename T>
Vector<N> operator*(const T scalar, const Vector<N>& vec);


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
double dot(const Vector<N1>& v1, const Vector<N2>& v2);


/**
 * @brief 3D vector cross product of v1 x v2.
 *
 * @param v1 Vector 1 (LHS).
 * @param v2 Vector2 (RHS).
 * @return Vector cross product.
 */
Vector<3> cross(const Vector<3>& v1, const Vector<3>& v2);


}  // namespace LinAlg
}  // namespace MathUtils


#endif  // MATHUTILS_LINALG_VECTORMATH_H_
