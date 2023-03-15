/**
 * @file Vector.h
 * @author Michael Wrona
 * @date 2023-03-08
 * @brief Vector template class & functions.
 */

#ifndef MATHUTILS_LINALG_VECTOR_H_
#define MATHUTILS_LINALG_VECTOR_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <numeric>
#include <type_traits>

namespace MathUtils {

/**
 * @brief N-length vector class.
 *
 * @tparam N Length of the vector.
 */
template<std::size_t N>
class Vector
{
public:

  static_assert(N > 1, "One-length or zero-length vectors are not allowed.");

  /**
   * @brief Create a Vector.
   *
   * @details Default constructor sets all values to zero.
   */
  Vector()
  {
    m_arr.fill(0.0);
  }

  /**
   * @brief Destroy the vector.
   */
  ~Vector() = default;

  /**
   * @brief Create a vector from an initializer list.
   *
   * @tparam T Initializer list data type.
   * @param vector_vals Vector values.
   */
  template<typename T>
  explicit Vector(const std::initializer_list<T> vector_vals)
  {
    // NOTE: Use an `assert` since the initializer list is non-static.
    static_assert(std::is_fundamental<T>::value, "Vectors can only be initialized from fundamental types.");
    assert(N == vector_vals.size());

    /**
     * NOTE: Using std::copy with a list of non-double vals will implicitly convert to `double`. This should be fine
     * for `double` and integer-type lists, but a `float` list might have strange conversions. Compiler flags should
     * catch this scenario, though?
     */
    std::copy(vector_vals.begin(), vector_vals.end(), m_arr.begin());
  }

  /**
   * @brief Copy-construct vector.
   *
   * @param src_vec Other vector.
   */
  Vector(const Vector& src_vec)
    :m_arr{src_vec.m_arr}
  {}

  /**
   * @brief Copy-assign vector.
   * @param src_vec Other vector.
   * @return Copied vector.
   */
  Vector& operator=(const Vector& src_vec)
  {
    m_arr = src_vec.m_arr;
    return *this;
  }

  /**
   * @brief Move-assign vector.
   * @param src_vec Other vector.
   * @return Copied vector.
   */
  Vector& operator=(Vector&& src_vec)
  {
    m_arr.swap(src_vec.m_arr);
    return *this;
  }

  /**
   * @brief Assign vector values from an initializer list.
   *
   * @tparam T Initializer list type.
   * @param vector_vals New vector.
   */
  template<typename T>
  Vector& operator=(const std::initializer_list<T> vector_vals)
  {
    /**
     * NOTE: Since an initializer list is non-static, we cannot use `static_assert` to check the length. Therefore,
     * this assert is done at runtime.
     */
    static_assert(std::is_fundamental<T>::value, "Vectors can only be initialized from fundamental types.");
    assert(N == vector_vals.size());

    std::copy(vector_vals.begin(), vector_vals.end(), m_arr.begin());
    return *this;
  }

  /**
   * @brief Access vector element.
   *
   * @param idx Vector index.
   * @return Vector element at specified index.
   */
  double& operator()(const std::size_t idx)
  {
    assert(idx < N);
    return m_arr[idx];
  }

  /**
   * @brief Get vector element.
   *
   * @param idx Vector index.
   * @return Vector value at specified index.
   */
  const double& operator()(const std::size_t idx) const
  {
    assert(idx < N);
    return m_arr[idx];
  }

  /**
   * @brief Add scalar to all vector elements in-place (accumulate).
   *
   * @tparam T Scalar type.
   * @param scalar Scalar to add.
   * @return Vector with scalar added.
   */
  template<typename T>
  Vector& operator+=(const T scalar)
  {
    static_assert(std::is_fundamental<T>::value, "Only fundamental types allowed.");

    std::for_each(
      m_arr.begin(),
      m_arr.end(),
      [scalar](double& element){element += static_cast<double>(scalar);}
    );

    return *this;
  }

  /**
   * @brief Add vector in-place (accumulate).
   *
   * @tparam LEN Other vector length.
   * @param vec Vector to add.
   * @return Vector with other vector added.
   */
  template<std::size_t LEN>
  Vector& operator+=(const Vector<LEN>& vec)
  {
    static_assert(LEN == N, "Vector is incompatible length.");

    for (std::size_t idx = 0; idx < N; idx++)
    {
      m_arr[idx] += vec.m_arr[idx];
    }
    return *this;
  }

  /**
   * @brief Subtract scalar from all vector elements in-place.
   *
   * @tparam T Scalar type.
   * @param scalar Scalar to subtract.
   * @return Vector with scalar subtracted.
   */
  template<typename T>
  Vector& operator-=(const T scalar)
  {
    static_assert(std::is_fundamental<T>::value, "Only fundamental types allowed.");

    std::for_each(
      m_arr.begin(),
      m_arr.end(),
      [scalar](double& element){element -= static_cast<double>(scalar);}
    );

    return *this;
  }

  /**
   * @brief Subtract vector in-place (accumulate).
   *
   * @tparam LEN Other vector length.
   * @param vec Vector to subtract.
   * @return Vector with other vector subtracted.
   */
  template<std::size_t LEN>
  Vector& operator-=(const Vector<LEN>& vec)
  {
    static_assert(LEN == N, "Vector is incompatible length.");

    for (std::size_t idx = 0; idx < N; idx++)
    {
      m_arr[idx] -= vec.m_arr[idx];
    }
    return *this;
  }

  /**
   * @brief Multiply all elements by a scalar in-place.
   *
   * @tparam T Scalar type.
   * @param scalar Scalar to multiply by.
   * @return Vector with scalar multiplied.
   */
  template<typename T>
  Vector& operator*=(const T scalar)
  {
    static_assert(std::is_fundamental<T>::value, "Only fundamental types allowed.");

    std::for_each(
      m_arr.begin(),
      m_arr.end(),
      [scalar](double& element){element *= static_cast<double>(scalar);}
    );

    return *this;
  }

  /**
   * @brief Divide all elements by a scalar in-place.
   *
   * @tparam T Scalar type.
   * @param scalar Scalar to divide by.
   * @return Vector with scalar divided.
   */
  template<typename T>
  Vector& operator/=(const T scalar)
  {
    static_assert(std::is_fundamental<T>::value, "Only fundamental types allowed.");

    const double scalard = static_cast<double>(scalar);
    assert(scalard > 1e-14);  // make sure denominator is not too small

    std::for_each(
      m_arr.begin(),
      m_arr.end(),
      [scalard](double& element){element /= scalard;}
    );

    return *this;
  }

  /**
   * @brief Get the vector length (number of elements).
   *
   * @return Vector length.
   */
  std::size_t size() const
  {
    return N;
  }

  /**
   * @brief Fill the entire vector with a value.
   *
   * @param val Value to fill the vector with.
   */
  void fill(const double val)
  {
    m_arr.fill(val);
  }

  /**
   * @brief Return the magnitude/norm of the vector.
   *
   * @return Vector magnitude.
   */
  double magnitude() const
  {
    const double magn = std::accumulate(
      m_arr.begin(), m_arr.end(), 0.0,
      [](double accum, const double& val){return accum += val * val;}
    );

    return std::sqrt(magn);
  }

  /**
   * @brief Normalize the vector.
   */
  void normalize()
  {
    const double magn = magnitude();

    std::for_each(m_arr.begin(), m_arr.end(), [magn](double& val){val /= magn;});
  }

  /**
   * @brief Return the sum of all elements in the vector.
   *
   * @return Sum of all vector elements.
   */
  double sum() const
  {
    return std::accumulate(m_arr.begin(), m_arr.end(), 0.0, std::plus<double>());
  }

  /**
   * @brief Multiply all elements by -1.0. Change the sign of all elements.
   *
   * @return Vector with signs changed.
   */
  Vector& negate()
  {
    std::for_each(m_arr.begin(), m_arr.end(), [](double& val){val *= -1.0;});
    return *this;
  }

  /**
   * @brief Print a vector to a stream. Comma-separates values. Does not add a newline at the end.
   *
   * @param os Output stream.
   * @param vec Vector to print.
   * @return Output stream with vector.
   *
   * @code {.cpp}
   * std::cout << my_vector << "\n";
   * @endcode
   */
  friend std::ostream& operator<<(std::ostream& os, const Vector& vec)
  {
    for (std::size_t idx = 0; idx < vec.m_arr.size() - 1; idx++)
    {
      os << std::setprecision(8) << vec.m_arr[idx] << ", ";
    }

    os << std::setprecision(8) << vec.m_arr[vec.m_arr.size() - 1];
    return os;
  }

private:
  std::array<double, N> m_arr;  ///< Underlying array to store vector values.
};

// ============================================================================
// VECTOR-ONLY FUNCTIONS
// ============================================================================

/**
 * @brief 3D vector cross product of v1 x v2.
 *
 * @param v1 Vector 1 (LHS).
 * @param v2 Vector2 (RHS).
 * @return Vector cross product.
 */
inline Vector<3> cross(const Vector<3>& v1, const Vector<3>& v2)
{
  return Vector<3>{
    (v1(1) * v2(2)) - (v1(2) * v2(1)),
    (v1(2) * v2(0)) - (v1(0) * v2(2)),
    (v1(0) * v2(1)) - (v1(1) * v2(0))
  };
}

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


// ============================================================================
// VECTOR-ONLY OPERATOR OVERLOADS
// ============================================================================

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
 * @brief Add a scalar to a vector.
 *
 * @tparam N Vector length.
 * @tparam T Scalar type
 * @param v Vector.
 * @param scalar Scalar.
 * @return Scalar added to vector.
 */
template<std::size_t N, typename T>
Vector<N> operator+(const Vector<N>& v, const T scalar)
{
  static_assert(std::is_fundamental<T>::value, "Scalar must be fundamental type.");

  Vector<N> res;

  for (std::size_t idx = 0; idx < N; idx++)
  {
    res(idx) = v(idx) + static_cast<double>(scalar);
  }

  return res;
}

/**
 * @brief Add a scalar to a vector.
 *
 * @tparam T Scalar type
 * @tparam N Vector length.
 * @param scalar Scalar.
 * @param v Vector.
 * @return Scalar added to vector.
 */
template<typename T, std::size_t N>
Vector<N> operator+(const T scalar, const Vector<N>& v)
{
  static_assert(std::is_fundamental<T>::value, "Scalar must be fundamental type.");

  return v + scalar;
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
 * @brief Subract a scalar from a vector.
 *
 * @tparam N Vector length.
 * @tparam T Scalar type.
 * @param v Vector.
 * @param scalar Scalar
 * @return Vector with scalar subtracted from it.
 */
template<std::size_t N, typename T>
Vector<N> operator-(const Vector<N>& v, const T scalar)
{
  static_assert(std::is_fundamental<T>::value, "Scalar must be fundamental type.");

  Vector<N> res;

  for (std::size_t idx = 0; idx < N; idx++)
  {
    res(idx) = v(idx) - static_cast<double>(scalar);
  }

  return res;
}

/**
 * @brief Subract a scalar from a vector.
 *
 * @tparam T Scalar type.
 * @tparam N Vector length.
 * @param scalar Scalar
 * @param v Vector.
 * @return Vector with scalar subtracted from it.
 */
template<typename T, std::size_t N>
Vector<N> operator-(const T scalar, const Vector<N>& v)
{
  static_assert(std::is_fundamental<T>::value, "Scalar must be fundamental type.");

  return v - scalar;
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

#endif  // MATHUTILS_LINALG_VECTOR_H_
