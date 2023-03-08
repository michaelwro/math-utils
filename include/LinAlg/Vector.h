/**
 * @file Vector.h
 * @author Michael Wrona
 * @date 2023-03-08
 * @brief Vector template class.
 */

#ifndef MATHUTILS_LINALG_VECTOR_H_
#define MATHUTILS_LINALG_VECTOR_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <numeric>
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


  ~Vector() = default;


  /**
   * @brief Create a vector from an initializer list.
   *
   * @tparam T Initializer list data type.
   * @param vector_vals Vector values.
   */
  template<typename T>
  Vector(std::initializer_list<T> vector_vals)
  {
    /**
     * NOTE: Since an initializer list is non-static, we cannot use `static_assert` to check the length. Therefore,
     * this assert is done at runtime.
     */
    static_assert(std::is_fundamental<T>::value, "Vectors can only be initialized from fundamental types");
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
   * @param vector_vals New vector values.
   */
  template<typename T>
  Vector& operator=(std::initializer_list<T> vector_vals)
  {
    /**
     * NOTE: Since an initializer list is non-static, we cannot use `static_assert` to check the length. Therefore,
     * this assert is done at runtime.
     */
    static_assert(std::is_fundamental<T>::value, "Vectors can only be initialized from fundamental types");
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

    std::for_each(
      m_arr.begin(), m_arr.end(), [magn](double& val){val /= magn;}
    );
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


}  // namespace LinAlg
}  // namespace MathUtils


#endif  // MATHUTILS_LINALG_VECTOR_H_
