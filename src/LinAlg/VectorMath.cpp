/**
 * @file VectorMath.cpp
 * @author Michael Wrona
 * @date 2023-03-08
 * @brief Vector math functions and operator overloads.
 */

#include "LinAlg/Vector.h"
#include "LinAlg/VectorMath.h"

#include <cstddef>

namespace MathUtils { namespace LinAlg {


template<std::size_t N_LEFT, std::size_t N_RIGHT>
Vector<N_LEFT> operator+(const Vector<N_LEFT>& v1, const Vector<N_RIGHT>& v2)
{
  static_assert(N_LEFT == N_RIGHT);

  Vector<N_LEFT> result;

  for (std::size_t idx = 0; idx < N_LEFT; idx++)
  {
    result(idx) = v1(idx) + v2(idx);
  }

  return result;
}


/**
 * @details The scalar type is a template to support multiplying the Vector by non-double types. A `static_assert` is
 * included to verify the type is a fundamental type (int, float, etc.).
 */
template<std::size_t N, typename T>
Vector<N> operator*(const Vector<N>& vec, const T scalar)
{
  static_assert(std::is_fundamental<T>::value);

  Vector<N> res;

  for (std::size_t idx = 0; idx < vec.length(); idx++) {
    res(idx) = static_cast<double>(scalar) * vec(idx);
  }

  return res;
}


/**
 * @details The scalar type is a template to support multiplying the Vector by non-double types. A `static_assert` is
 * included to verify the type is a fundamental type (int, float, etc.).
 */
template<std::size_t N, typename T>
Vector<N> operator*(const T scalar, const Vector<N>& vec)
{
  static_assert(std::is_fundamental<T>::value);
  return Vector<N> {vec * static_cast<double>(scalar)};
}


template<std::size_t N1, std::size_t N2>
double dot(const Vector<N1>& v1, const Vector<N2>& v2)
{
  static_assert(N1 == N2);

  double dot_prod = 0.0;

  // TODO: Use std::accumulate?
  for (std::size_t idx = 0; idx < N1; idx++)
  {
    dot_prod += v1(idx) * v2(idx);
  }

  return dot_prod;
}


Vector<3> cross(const Vector<3>& v1, const Vector<3>& v2)
{
  return Vector<3> {
    (v1(1) * v2(2)) - (v1(2) - v2(1)),
    (v1(2) * v2(0)) - (v1(0) - v2(2)),
    (v1(0) * v2(1)) - (v1(1) - v2(0))
  };
}

}  // namespace LinAlg
}  // namespace MathUtils
