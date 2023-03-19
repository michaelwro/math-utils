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
   * Matrix<3,2> my_mat({
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
   * Matrix<3,2> my_mat({
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
  std::size_t cols() const
  {
    return COLS;
  }

  /**
   * @brief Get the trace of the matrix (sum of diagonal elements).
   *
   * @return Matrix trace.
   */
  double trace() const
  {
    assert(ROWS == COLS);  // only allowed for square matrices

    double tr = 0.0;

    for (std::size_t idx = 0; idx < ROWS; idx++)
    {
      tr += m_arr[(idx * COLS) + idx];
    }

    return tr;
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
    for (std::size_t ii = 0; ii < mat.rows(); ii++)
    {
      for (std::size_t jj = 0; jj < mat.cols(); jj++)
      {
        os << (jj == 0 ? "\n" : "") << std::setw(most_chars) << std::left <<
          mat(ii, jj) << (jj == mat.cols()-1 ? "" : ", ");
      }
    }

    return os;
  }

protected:
private:
  std::array<double, ROWS * COLS> m_arr;  ///< Underlying array to store values (row-major order).
};

// ====================================================================================================================
// MATRIX-MATRIX OPERATOR OVERLOADS
// ====================================================================================================================

/**
 * @brief 2x2 matrix-matrix multiplication A * B.
 *
 * @details Expanded multiplication operations with SymPy.
 *
 * @code {.py}
 * a = sympy.MatrixSymbol('a', 2, 2)
 * b = sympy.MatrixSymbol('b', 2, 2)
 * numpy.matmul(a, b)
 * @endcode
 *
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix product.
 */
inline Matrix<2,2> operator*(const Matrix<2,2>& a, const Matrix<2,2>& b)
{
  return Matrix<2,2>({
    {a(0,0)*b(0,0) + a(0,1)*b(1,0), a(0,0)*b(0,1) + a(0,1)*b(1,1)},
    {a(1,0)*b(0,0) + a(1,1)*b(1,0), a(1,0)*b(0,1) + a(1,1)*b(1,1)}
  });
}

/**
 * @brief 3x3 matrix-matrix multiplication A * B.
 *
 * @details Expanded multiplication operations with SymPy.
 *
 * @code {.py}
 * a = sympy.MatrixSymbol('a', 3, 3)
 * b = sympy.MatrixSymbol('b', 3, 3)
 * numpy.matmul(a, b)
 * @endcode
 *
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix product.
 */
inline Matrix<3,3> operator*(const Matrix<3,3>& a, const Matrix<3,3>& b)
{
  return Matrix<3,3>({
    {a(0,0)*b(0,0) + a(0,1)*b(1,0) + a(0,2)*b(2,0),
    a(0,0)*b(0,1) + a(0,1)*b(1,1) + a(0,2)*b(2,1),
    a(0,0)*b(0,2) + a(0,1)*b(1,2) + a(0,2)*b(2,2)},
    {a(1,0)*b(0,0) + a(1,1)*b(1,0) + a(1,2)*b(2,0),
    a(1,0)*b(0,1) + a(1,1)*b(1,1) + a(1,2)*b(2,1),
    a(1,0)*b(0,2) + a(1,1)*b(1,2) + a(1,2)*b(2,2)},
    {a(2,0)*b(0,0) + a(2,1)*b(1,0) + a(2,2)*b(2,0),
    a(2,0)*b(0,1) + a(2,1)*b(1,1) + a(2,2)*b(2,1),
    a(2,0)*b(0,2) + a(2,1)*b(1,2) + a(2,2)*b(2,2)}
  });
}

/**
 * @brief Matrix-matrix multiplication A * B.
 *
 * @details Naive implementation.
 *
 * @tparam N Matrix A rows.
 * @tparam M Matrix A columns and matrix B rows.
 * @tparam P Matrix B columns.
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix-matrix product, (N, P).
 *
 * @ref https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
 */
template<std::size_t N, std::size_t M, std::size_t P>
Matrix<N,P> operator*(const Matrix<N,M>& a, const Matrix<M,P>& b)
{
  Matrix<N,P> c;

  for (std::size_t ii = 0; ii < N; ii++)
  {
    for (std::size_t jj = 0; jj < P; jj++)
    {
      double sum = 0.0;
      for (std::size_t kk = 0; kk < M; kk++)
      {
        sum += a(ii, kk) * b(kk, jj);
      }

      c(ii, jj) = sum;
    }
  }

  return c;
}




// ====================================================================================================================
// MATRIX-VECTOR OPERATOR OVERLOADS
// ====================================================================================================================



}  // namespace MathUtils

#endif  // MATHUTILS_LINALG_MATRIX_H_
