/**
 * @file Matrix.h
 * @author Michael Wrona
 * @date 2023-03-18
 */

#ifndef MATHUTILS_LINALG_MATRIX_H_
#define MATHUTILS_LINALG_MATRIX_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
// #include <cmath>
#include <functional>
#include <initializer_list>
// #include <iomanip>
// #include <limits>
// #include <numeric>
#include <type_traits>

namespace MathUtils {

/**
 * @brief NxM matrix class.
 *
 * @details Stores elements in row-major order.
 *
 * @tparam ROWS Number of rows.
 * @tparam COLS Number of columns.
 */
template<std::size_t ROWS, std::size_t M>
class Matrix
{
public:
  static_assert(ROWS != 0 && COLS != 0, "Cannot have zero rows/columns.");

  /**
   * @brief Create a matrix.
   *
   * @details Default constructor sets all values to zero.
   */
  Matrix()
  {
    m_arr.fill(0.0);
  }

  /**
   * @brief Destroy the matrix.
   */
  ~Matrix() = default;

  /**
   * @brief Create a matrix from an initializer list of lists.
   *
   * @code {.cpp}
   * Matrix<2,3> my_mat({
   *  {1, 2},
   *  {3, 4},
   *  {5, 6}
   * });
   * @endcode
   *
   * @tparam T Initializer list data type.
   * @param new_matrix New values to assign to the array.
   */
  template<typename T>
  explicit Matrix(const std::initializer_list<std::initializer_list<T>> new_matrix)
  {
    static_assert(std::is_fundamental<T>::value, "Can only be initialized from fundamental types.");

    auto array_element = m_arr.begin();  // start at the beginning of the array

    for (const auto& row : new_matrix)
    {
      assert(row.size() == ROWS);  // check row dimension

      for (const auto& val : row)
      {
        assert(array_element != m_arr.end());  // make sure we're not at the end
        *(array_element++) = static_cast<double>(val);  // assign value to array
      }
    }

    assert(array_element == m_arr.end());  // make sure we reached the end
  }

  /**
   * @brief Copy construct matrix.
   *
   * @param mat Other matrix.
   */
  Matrix(const Matrix& mat)
    :m_arr{mat.m_arr}
  {}

  /**
   * @brief Copy-assign matrix.
   *
   * @param mat Other matrix.
   * @return Matrix.
   */
  Matrix& operator=(const Matrix& mat)
  {
    m_arr = mat.m_arr;
    return *this;
  }

  /**
   * @brief Move assign matrix.
   *
   * @param mat Other matrix.
   * @return Matrix.
   */
  Matrix& operator=(Matrix&& mat)
  {
    m_arr.swap(mat.m_arr);
    return *this;
  }

  /**
   * @brief Assign matrix values from an initializer list of lists.
   *
   * @code {.cpp}
   * Matrix<2,3> my_mat;
   * my_mat = {
   *  {1, 2},
   *  {3, 4},
   *  {5, 6}
   * };
   * @endcode
   *
   * @tparam T Initializer list data type.
   * @param new_matrix New values to assign to the array.
   */
  template<typename T>
  Matrix& operator=(const std::initializer_list<std::initializer_list<T>> new_matrix)
  {
    static_assert(std::is_fundamental<T>::value, "Can only be initialized from fundamental types.");

    auto array_element = m_arr.begin();  // start at the beginning of the array

    for (const auto& row : new_matrix)
    {
      assert(row.size() == ROWS);  // check row dimension

      for (const auto& val : row)
      {
        assert(array_element != m_arr.end());  // make sure we're not at the end
        *(array_element++) = static_cast<double>(val);  // assign value to array
      }
    }

    assert(array_element == m_arr.end());  // make sure we reached the end
    return *this;
  }

  /**
   * @brief Access matrix element.
   *
   * @param row Row index.
   * @param col Column index.
   * @return Matrix element at specified index.
   */
  double& operator()(const std::size_t row, std::size_t col)
  {
    assert(row < ROWS);
    assert(col < COLS);
    return m_arr[(row * COLS) + col];
  }

  /**
   * @brief Get matrix element.
   *
   * @param row Row index.
   * @param col Column index.
   * @return Matrix element at specified index.
   */
  const double& operator()(const std::size_t row, std::size_t col) const
  {
    assert(row < ROWS);
    assert(col < COLS);
    return m_arr[(row * COLS) + col];
  }

protected:
private:
  std::array<double, ROWS * COLS> m_arr;  ///< Underlying array to store values (row-major order).
};

}  // namespace MathUtils

#endif  // MATHUTILS_LINALG_MATRIX_H_
