
#ifndef MATHUTILS_LINALG_VECTOR_H_
#define MATHUTILS_LINALG_VECTOR_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <type_traits>

namespace MathUtils { namespace LinAlg {

/**
 * @brief N-length vector class.
 *
 * @tparam N Length of the vector.
 */
template<std::size_t N>
class Vector
{
public:
  /**
   * @brief Create a Vector.
   *
   * @details Default constructor sets all values to zero.
   */
  Vector()
  {
    // std::cout << "DEFAULT CONSTRUCT\n";
    m_arr.fill(0.0);
  }


  ~Vector() = default;


  /**
   * @brief Create a vector from an initializer list.
   *
   * @tparam T Initializer list data type.
   * @param vector_vals Vector values.
   */
  template<typename T>
  Vector(const std::initializer_list<T>& vector_vals)
  {
    // std::cout << "INIT LIST CONSTRUCT\n";

    /**
     * NOTE: Since an initializer list is non-static, we cannot use `static_assert` to check the length. Therefore,
     * this assert is done at runtime.
     */
    static_assert(std::is_fundamental<T>::value);
    assert(N == vector_vals.size());

    /**
     * NOTE: Using std::copy with a list of non-double vals will implicitly convert to `double`. This should be fine
     * for `double` and integer-type lists, but a `float` list might have strange conversions. Compiler flags should
     * catch this scenario, though?
     */
    std::copy(vector_vals.begin(), vector_vals.end(), m_arr.begin());
  };


  /**
   * @brief Copy-construct vector.
   *
   * @param src_vec Other vector.
   */
  Vector(const Vector& src_vec)
    :m_arr{src_vec.m_arr}
  {
    // std::cout << "COPY CONSTRUCT\n";
  }


  /**
   * @brief Copy-assign vector.
   * @param src_vec Other vector.
   * @return Copied vector.
   */
  Vector& operator=(const Vector& src_vec)
  {
    // std::cout << "COPY ASSIGN\n";
    m_arr = src_vec.m_arr;
    return *this;
  }


  /**
   * @brief Move-assign vector.
   * @param src_vec Other vector.
   * @return Copied vector.
   */
  Vector& operator=(const Vector&& src_vec)
  {
    // std::cout << "MOVE ASSIGN\n";
    m_arr.swap(src_vec.m_arr);
    return *this;
  }


  /**
   * @brief Assign vector values from an initializer list.
   *
   * @tparam T Initializer list type.
   * @param vector_vals New vector values.
   */
  template<typename T>
  Vector& operator=(const std::initializer_list<T>& vector_vals)
  {
    // std::cout << "INIT LIST ASSIGN\n";

    /**
     * NOTE: Since an initializer list is non-static, we cannot use `static_assert` to check the length. Therefore,
     * this assert is done at runtime.
     */
    static_assert(std::is_fundamental<T>::value);
    assert(N == vector_vals.size());

    /**
     * NOTE: Using std::copy with a list of non-double vals will implicitly convert to `double`. This should be fine
     * for `double` and integer-type lists, but a `float` list might have strange conversions. Compiler flags should
     * catch this scenario, though?
     */
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
    return m_arr.at(idx);
  }


  /**
   * @brief Get Vector element.
   *
   * @param idx Vector index.
   * @return Vector value at specified index.
   */
  const double& operator()(const std::size_t idx) const
  {
    return m_arr.at(idx);
  }

  /**
   * @brief Get the vector length (number of elements).
   *
   * @return Vector length.
   */
  std::size_t length() const
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
   * @brief Print a vector to a stream. Comma-separates values. Does not add a newline at the end.
   *
   * @param os Output stream.
   * @param vec Vector to print.
   * @return Output stream with Vector.
   *
   * @code {.cpp}
   * std::cout << my_vector << "\n";
   * @endcode
   */
  friend std::ostream& operator<<(std::ostream& os, const Vector& vec)
  {
    for (std::size_t idx = 0; idx < vec.m_arr.size() - 1; idx++)
      os << std::setprecision(8) << vec.m_arr.at(idx) << ", ";

    os << std::setprecision(8) << vec.m_arr.at(vec.m_arr.size() - 1);
    return os;
  }

private:
  static constexpr std::size_t m_print_prec = 8;  ///< Number of decimals to use when printing to stream.
  std::array<double, N> m_arr;  ///< Underlying array to store vector values.
};


// ====================================================================================================================
// Vector math functions and operator overloads
// ====================================================================================================================


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
 * @brief Vector-scalar multiplication.
 *
 * @details The scalar type is a template to support multiplying the Vector by non-double types. A `static_assert` is
 * included to verify the type is a fundamental type (int, float, etc.).
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
  static_assert(std::is_fundamental<T>::value);

  Vector<N> res;

  for (std::size_t idx = 0; idx < vec.length(); idx++) {
    res(idx) = static_cast<double>(scalar) * vec(idx);
  }

  return res;
}


/**
 * @brief Scalar-vector multiplication.
 *
 * @details The scalar type is a template to support multiplying the Vector by non-double types. A `static_assert` is
 * included to verify the type is a fundamental type (int, float, etc.).
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
  static_assert(std::is_fundamental<T>::value);
  return Vector<N> {vec * static_cast<double>(scalar)};
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
  static_assert(N1 == N2);

  double dot_prod = 0.0;

  // TODO: Use std::accumulate?
  for (std::size_t idx = 0; idx < N1; idx++)
  {
    dot_prod += v1(idx) * v2(idx);
  }

  return dot_prod;
}


/**
 * @brief 3D vector cross product of v1 x v2.
 *
 * @param v1 Vector 1 (LHS).
 * @param v2 Vector2 (RHS).
 * @return Vector cross product.
 */
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


#endif  // MATHUTILS_LINALG_VECTOR_H_
