/**
 * @file VectorOperators.h
 * @author Michael Wrona
 * @date 2023-03-15
 * @brief Vector operator overloads.
 */

#ifndef MATHUTILS_LINALG_VECTOR_OPERATORS_H_
#define MATHUTILS_LINALG_VECTOR_OPERATORS_H_

#include "LinAlg/Vector.h"

namespace MathUtils {

/**
 * @brief Add two vectors.
 *
 * @tparam N_LEFT First vector length.
 * @tparam N_RIGHT Second vector length.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Vector sum, v1 + v2.
 */
template<std::size_t N_LEFT, std::size_t N_RIGHT>
Vector<N_LEFT> operator+(const Vector<N_LEFT>& v1, const Vector<N_RIGHT>& v2)
{
  static_assert(N_LEFT == N_RIGHT, "Incompatible dimensions.");

  Vector<N_LEFT> result;

  for (std::size_t idx = 0; idx < N_LEFT; idx++)
  {
    result(idx) = v1(idx) + v2(idx);
  }

  return result;
}

/**
 * @brief Subtract two vectors.
 *
 * @tparam N_LEFT First vector length.
 * @tparam N_RIGHT Second vector length.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Vector difference, v1 - v2.
 */
template<std::size_t N_LEFT, std::size_t N_RIGHT>
Vector<N_LEFT> operator-(const Vector<N_LEFT>& v1, const Vector<N_RIGHT>& v2)
{
  static_assert(N_LEFT == N_RIGHT, "Incompatible dimensions.");

  Vector<N_LEFT> result;

  for (std::size_t idx = 0; idx < N_LEFT; idx++)
  {
    result(idx) = v1(idx) - v2(idx);
  }

  return result;
}

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
Vector<N> operator*(const Vector<N>& vec, const T scalar)
{
  static_assert(std::is_fundamental<T>::value, "Must be fundamental type.");

  Vector<N> res;

  for (std::size_t idx = 0; idx < vec.size(); idx++)
  {
    res(idx) = static_cast<double>(scalar) * vec(idx);
  }

  return res;
}

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
Vector<N> operator*(const T scalar, const Vector<N>& vec)
{
  static_assert(std::is_fundamental<T>::value, "Must be fundamental type.");
  return Vector<N>(vec * static_cast<double>(scalar));
}

}  // namespace MathUtils

#endif  // MATHUTILS_LINALG_VECTOR_OPERATORS_H_
