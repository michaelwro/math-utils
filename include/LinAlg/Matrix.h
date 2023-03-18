/**
 * @file Matrix.h
 * @author Michael Wrona
 * @date 2023-03-18
 */

#ifndef MATHUTILS_LINALG_MATRIX_H_
#define MATHUTILS_LINALG_MATRIX_H_

// #include <limits>
// #include <numeric>
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <ostream>
#include <sstream>
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
template<std::size_t ROWS, std::size_t COLS>
class Matrix
{
public:
  static_assert(ROWS != 0, "Cannot have zero rows.");
  static_assert(COLS != 0, "Cannot have zero columns.");
  static_assert(ROWS != 1 && COLS != 1, "Cannot have one-element matrix.");

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
   * @brief Create a matrix from an initializer list.
   *
   * @code {.cpp}
   * Matrix<2,3> my_mat({
   *  1, 2,
   *  3, 4,
   *  5, 6
   * });
   * @endcode
   *
   * @tparam T Initializer list data type.
   * @param new_matrix New values to assign to the array.
   */
  template<typename T>
  explicit Matrix(const std::initializer_list<T> new_matrix)
  {
    static_assert(std::is_fundamental<T>::value, "Can only be initialized from fundamental types.");
    assert(new_matrix.size() == ROWS * COLS);

    std::copy(new_matrix.begin(), new_matrix.end(), m_arr.begin());
  }

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
    assert(new_matrix.size() == ROWS);  // check number of rows

    auto array_element = m_arr.begin();  // start at the beginning of the array


    for (const auto& row : new_matrix)
    {
      assert(row.size() == COLS);  // check number of cols

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

  /**
   * @brief Get the number of rows in the matrix.
   *
   * @return Matrix rows.
   */
  std::size_t rows() const
  {
    return ROWS;
  }

  /**
   * @brief Get the number of columns in the matrix.
   *
   * @return Matrix columns.
   */
  std::size_t columns() const
  {
    return COLS;
  }

  /**
   * @brief Print a matrix to a stream. Comma-separates values. Does not add a newline at the end.
   *
   * @param os Output stream.
   * @param mat Matrix to print.
   * @return Output stream with matrix.
   */
  friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)
  {
    // figure out how many chars are required to print a number
    auto num_str_chars = [](const double val){
      std::ostringstream ss;
      ss << val;
      return ss.str().size();
    };

    // loop through array and find the longest number
    std::size_t most_chars = 1;
    for (const auto& val : mat.m_arr)
    {
      std::size_t chars = num_str_chars(val);
      most_chars = chars > most_chars ? chars : most_chars;
    }

    /**
     * Print the matrix.
     * https://cplusplus.com/forum/beginner/275937/#msg1194918
     */
    for (std::size_t i = 0; i < mat.rows(); i++)
    {
      for (std::size_t j = 0; j < mat.columns(); j++)
      {
        os << (j == 0 ? "\n" : "") << std::setw(most_chars) << std::left <<
          mat(i, j) << (j == mat.columns()-1 ? "" : ", ");
      }
    }

    return os;
  }

protected:
private:
  std::array<double, ROWS * COLS> m_arr;  ///< Underlying array to store values (row-major order).
};

}  // namespace MathUtils

#endif  // MATHUTILS_LINALG_MATRIX_H_
