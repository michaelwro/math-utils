/**
 * @file Matrix.h
 * @author Michael Wrona
 * @date 2023-03-18
 */

#ifndef MATHUTILS_LINALG_MATRIX_H_
#define MATHUTILS_LINALG_MATRIX_H_

#include "LinAlg/Vector.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <limits>
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
    :m_arr{}
  {}

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
    static_assert(std::is_fundamental<T>::value, "Only fundamental types allowed.");
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
    static_assert(std::is_fundamental<T>::value, "Only fundamental types allowed.");
    assert(new_matrix.size() == ROWS);  // check number of rows

    auto array_element = m_arr.begin();  // start at the beginning of the array

    for (const auto& row : new_matrix)
    {
      assert(row.size() == COLS);  // check number of cols

      for (const auto& val : row)
      {
        assert(array_element != m_arr.end());  // make sure we're not at the end
        *array_element = static_cast<double>(val);  // assign value to array
        array_element++;
      }
    }

    assert(array_element == m_arr.end());  // make sure we reached the end
  }

  /**
   * @brief Copy construct matrix.
   *
   * @param other Other matrix.
   */
  Matrix(const Matrix& other)
    :m_arr{other.m_arr}
  {}

  /**
   * @brief Move construct matrix.
   *
   * @param other Other matrix.
   */
  Matrix(Matrix&& other)
    :m_arr{std::move(other.m_arr)}
  {}

  /**
   * @brief Copy-assign matrix.
   *
   * @param other Other matrix.
   * @return Matrix.
   */
  Matrix& operator=(const Matrix& other)
  {
    if (&other == this)
    {
      return *this;
    }

    m_arr = other.m_arr;
    return *this;
  }

  /**
   * @brief Move assign matrix.
   *
   * @param other Other matrix.
   * @return Matrix.
   */
  Matrix& operator=(Matrix&& other)
  {
    if (&other == this)
    {
      return *this;
    }

    m_arr.swap(other.m_arr);
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
   * @brief Add scalar to matrix in-place.
   *
   * @tparam T Scalar type.
   * @param scalar Scalar to add.
   * @return Matrix with scalar added.
   */
  template<typename T>
  Matrix& operator+=(const T scalar)
  {
    static_assert(std::is_fundamental<T>::value, "Only fundamental types allowed");

    const double scalard = static_cast<double>(scalar);

    std::for_each(
      m_arr.begin(),
      m_arr.end(),
      [scalard](double& element){element += scalard;}
    );

    return *this;
  }

  /**
   * @brief Add matrix in-place.
   *
   * @param mat Matrix to add.
   * @return Matrix.
   */
  Matrix& operator+=(const Matrix& mat)
  {
    for (std::size_t idx = 0; idx < ROWS*COLS; idx++)
    {
      m_arr[idx] += mat.m_arr[idx];
    }

    return *this;
  }

  /**
   * @brief Subtract scalar from matrix in-place.
   *
   * @tparam T Scalar type.
   * @param scalar Scalar to subtract.
   * @return Matrix with scalar subtracted.
   */
  template<typename T>
  Matrix& operator-=(const T scalar)
  {
    static_assert(std::is_fundamental<T>::value, "Only fundamental types allowed");

    const double scalard = static_cast<double>(scalar);

    std::for_each(
      m_arr.begin(),
      m_arr.end(),
      [scalard](double& element){element -= scalard;}
    );

    return *this;
  }

  /**
   * @brief Subtract matrix in-place.
   *
   * @param mat Matrix to subtract.
   * @return Matrix.
   */
  Matrix& operator-=(const Matrix& mat)
  {
    for (std::size_t idx = 0; idx < ROWS*COLS; idx++)
    {
      m_arr[idx] -= mat.m_arr[idx];
    }

    return *this;
  }

  /**
   * @brief Multiply matrix by scalar in-place.
   *
   * @tparam T Scalar type.
   * @param scalar Scalar to multiply.
   * @return Matrix with scalar multiplied.
   */
  template<typename T>
  Matrix& operator*=(const T scalar)
  {
    static_assert(std::is_fundamental<T>::value, "Only fundamental types allowed");

    const double scalard = static_cast<double>(scalar);

    std::for_each(
      m_arr.begin(),
      m_arr.end(),
      [scalard](double& element){element *= scalard;}
    );

    return *this;
  }

  /**
   * @brief Multiply matrix in-place.
   *
   * @details This probs isn't efficient because a new std::array needs to be created and copied.
   *
   * @param mat Matrix to multiply by.
   * @return Matrix product.
   */
  Matrix& operator*=(const Matrix& mat)
  {
    std::array<double, ROWS*COLS> new_arr = {0};

    for (std::size_t ii = 0; ii < ROWS; ii++)
    {
      for (std::size_t jj = 0; jj < COLS; jj++)
      {
        double sum = 0.0;

        for (std::size_t kk = 0; kk < ROWS; kk++)
        {
          sum += m_arr[(ii * COLS) + kk] * mat.m_arr[(kk * COLS) + jj];
        }

        new_arr[(ii * COLS) + jj] = sum;
      }
    }

    m_arr = new_arr;
    return *this;
  }

  /**
   * @brief Divide matrix by scalar in-place.
   *
   * @tparam T Scalar type.
   * @param scalar Scalar to divide.
   * @return Matrix divided by scalar.
   */
  template<typename T>
  Matrix& operator/=(const T scalar)
  {
    static_assert(std::is_fundamental<T>::value, "Only fundamental types allowed");

    // make sure denominator is not too small
    const double scalard = static_cast<double>(scalar);
    assert(std::abs(scalard) > std::numeric_limits<double>::epsilon());

    std::for_each(
      m_arr.begin(),
      m_arr.end(),
      [scalard](double& element){element /= scalard;}
    );

    return *this;
  }

  /**
   * @brief Get an identity matrix.
   *
   * @return Identity matrix.
   */
  static Matrix identity()
  {
    Matrix eye;

    for (std::size_t ii = 0; ii < ROWS; ii++)
    {
      eye.m_arr[(ii * COLS) + ii] = 1.0;
    }

    return eye;
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
        std::string prefix = jj == 0 ? "\n" : "";  // put a newline or no char before the value
        std::string suffix = jj == mat.cols()-1 ? "" : ", ";  // put a comma or no char after the value

        os << prefix << std::setw(most_chars) << std::left << mat(ii, jj) << suffix;
      }
    }

    return os;
  }

protected:
private:
  std::array<double, ROWS * COLS> m_arr;  ///< Underlying array to store values (row-major order).
};


// ====================================================================================================================
// MATRIX ONLY FUNCTIONS
// ====================================================================================================================
/**
 * @brief Compute the trace of a matrix (sum of diagonal elements).
 *
 * @tparam Matrix dimension (square).
 * @param Matrix Matrix.
 * @return Matrix trace.
 */
template<std::size_t N>
double trace(const Matrix<N,N>& mat)
{
  double tr = 0.0;

  for (std::size_t idx = 0; idx < N; idx++)
  {
    tr += mat(idx, idx);
  }

  return tr;
}


// ====================================================================================================================
// MATRIX <-> SCALAR OPERATOR OVERLOADS
// ====================================================================================================================
/**
 * @brief Scalar-matrix multiplication.
 *
 * @tparam N Rows.
 * @tparam M Columns.
 * @tparam T Scalar type
 * @param scalar Scalar to multiply.
 * @param mat Matrix to multiply.
 * @return Product.
 */
template<std::size_t N, std::size_t M, typename T>
Matrix<N,M> operator*(const T scalar, const Matrix<N,M>& mat)
{
  static_assert(std::is_fundamental<T>::value, "Must be fundamental type.");

  Matrix<N,M> out_mat(mat);
  const double scalard = static_cast<double>(scalar);

  for (std::size_t ii = 0; ii < N; ii++)
  {
    for (std::size_t jj = 0; jj < M; jj++)
    {
      out_mat(ii, jj) *= scalard;
    }
  }

  return out_mat;
}

/**
 * @brief Matrix-scalar multiplication.
 *
 * @tparam N Rows.
 * @tparam M Columns.
 * @tparam T Scalar type
 * @param mat Matrix to multiply.
 * @param scalar Scalar to multiply.
 * @return Product.
 */
template<std::size_t N, std::size_t M, typename T>
Matrix<N,M> operator*(const Matrix<N,M>& mat, const T scalar)
{
  static_assert(std::is_fundamental<T>::value, "Must be fundamental type.");
  return scalar * mat;
}


// ====================================================================================================================
// MATRIX <-> MATRIX OPERATOR OVERLOADS
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
// MATRIX <-> VECTOR OPERATOR OVERLOADS
// ====================================================================================================================
/**
 * @brief 2x2 matrix and 2x1 vector multiplication.
 *
 * @details Expanded multiplication operations with SymPy.
 *
 * @code {.py}
 * a = sympy.MatrixSymbol('mat', 2, 2)
 * b = sympy.MatrixSymbol('vec', 2, 1)
 * numpy.matmul(a, b)
 * @endcode
 *
 * @param mat Matrix.
 * @param vec Vector.
 * @return Matrix-vector product.
 */
inline Vector<2> operator*(const Matrix<2,2>& mat, const Vector<2>& vec)
{
  return Vector<2> {
    mat(0,0)*vec(0) + mat(0,1)*vec(1),
    mat(1,0)*vec(0) + mat(1,1)*vec(1)
  };
}

/**
 * @brief 3x3 matrix and 3x1 vector multiplication.
 *
 * @details Expanded multiplication operations with SymPy.
 *
 * @code {.py}
 * a = sympy.MatrixSymbol('mat', 3, 3)
 * b = sympy.MatrixSymbol('vec', 3, 1)
 * numpy.matmul(a, b)
 * @endcode
 *
 * @param mat Matrix.
 * @param vec Vector.
 * @return Matrix-vector product.
 */
inline Vector<3> operator*(const Matrix<3,3>& mat, const Vector<3>& vec)
{
  return Vector<3> {
    mat(0,0)*vec(0) + mat(0,1)*vec(1) + mat(0,2)*vec(2),
    mat(1,0)*vec(0) + mat(1,1)*vec(1) + mat(1,2)*vec(2),
    mat(2,0)*vec(0) + mat(2,1)*vec(1) + mat(2,2)*vec(2)
  };
}

/**
 * @brief Matrix-vector multiplication.
 *
 * @tparam N Rows.
 * @tparam M Columns.
 * @param mat Matrix.
 * @param vec Vector.
 * @return Matrix-vector product.
 *
 * @ref http://www.cs.umsl.edu/~sanjiv/classes/cs5740/lectures/mvm.pdf
 */
template<std::size_t N, std::size_t M>
Vector<N> operator*(const Matrix<N,M>& mat, const Vector<M>& vec)
{
  Vector<N> res;

  for (std::size_t ii = 0; ii < N; ii++)
  {
    double sum = 0.0;

    for (std::size_t jj = 0; jj < M; jj++)
    {
      sum += mat(ii, jj) * vec(jj);
    }

    res(ii) = sum;
  }

  return res;
}

}  // namespace MathUtils

#endif  // MATHUTILS_LINALG_MATRIX_H_
