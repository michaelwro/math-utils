/**
 * @file Matrix.h
 * @author Michael Wrona
 * @date 2023-03-18
 */

#pragma once

#include "Internal/error_msg_helpers.h"
#include "LinAlg/Vector.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace MathUtils {

/**
 * @brief 2D matrix class.
 *
 * @details Stores elements in row-major order.
 *
 * @tparam T_ROWS Number of rows.
 * @tparam T_COLS Number of columns.
 */
template<std::size_t T_ROWS, std::size_t T_COLS>
class Matrix {
public:
    using size_type = std::size_t;
    using matrix_type = double;

    static_assert(T_ROWS != 0, "Cannot have zero rows.");
    static_assert(T_COLS != 0, "Cannot have zero columns.");
    static_assert(T_ROWS != 1 && T_COLS != 1, "Cannot have one-element matrix.");

    /**
     * @brief Create a matrix.
     *
     * @details Default constructor sets all values to zero.
     */
    Matrix() = default;

    /**
     * @brief Destroy the matrix.
     */
    ~Matrix() = default;

    /**
     * @brief Create a matrix from an initializer list.
     *
     * @code {.cpp}
     * Matrix<3,2> my_mat({
     *    1, 2,
     *    3, 4,
     *    5, 6
     * });
     * @endcode
     *
     * @tparam T Initializer list data type.
     * @param new_matrix New values to assign to the array.
     *
     * @exception std::length_error Invalid init. list size.
     */
    template<typename T>
    Matrix(const std::initializer_list<T> new_matrix);

    /**
     * @brief Create a matrix from an initializer list of lists.
     *
     * @code {.cpp}
     * Matrix<3,2> my_mat({
     *    {1, 2},
     *    {3, 4},
     *    {5, 6}
     * });
     * @endcode
     *
     * @tparam T Initializer list data type.
     * @param new_matrix New values to assign to the array.
     *
     * @exception std::length_error Invalid init. list size.
     */
    template<typename T>
    Matrix(const std::initializer_list<std::initializer_list<T>> new_matrix);

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
    Matrix(Matrix&& other) noexcept
        :m_arr{std::move(other.m_arr)}
    {}

    /**
     * @brief Copy-assign matrix.
     *
     * @param other Other matrix.
     * @return Matrix.
     */
    Matrix& operator=(const Matrix& other);

    /**
     * @brief Move assign matrix.
     *
     * @param other Other matrix.
     * @return Matrix.
     */
    Matrix& operator=(Matrix&& other) noexcept;

    /**
     * @brief Access matrix element. No bounds checking.
     *
     * @param row Row index.
     * @param col Column index.
     * @return Matrix element at specified index.
     *
     */
    [[nodiscard]] double& operator()(const std::size_t row, std::size_t col);

    /**
     * @brief Get matrix element. No bounds checking.
     *
     * @param row Row index.
     * @param col Column index.
     * @return Matrix element at specified index.
     */
    [[nodiscard]] const double& operator()(const std::size_t row, std::size_t col) const;

    /**
     * @brief Access matrix element. With bounds checking.
     *
     * @param row Row index.
     * @param col Column index.
     * @return Matrix element at specified index.
     *
     * @exception std::out_of_range Invalid matrix index.
     */
    [[nodiscard]] double& at(const std::size_t row, std::size_t col);

    /**
     * @brief Get matrix element.  With bounds checking.
     *
     * @param row Row index.
     * @param col Column index.
     * @return Matrix element at specified index.
     *
     * @exception std::out_of_range Invalid matrix index.
     */
    [[nodiscard]] const double& at(const std::size_t row, std::size_t col) const;

    /**
     * @brief Get the number of rows in the matrix.
     *
     * @return Matrix rows.
     */
    [[nodiscard]] constexpr size_type rows() const noexcept
    {
        return T_ROWS;
    }

    /**
     * @brief Get the number of columns in the matrix.
     *
     * @return Matrix columns.
     */
    [[nodiscard]] constexpr size_type cols() const noexcept
    {
        return T_COLS;
    }

    // =============================================================================================
    // ADDITION OPERATORS
    // =============================================================================================

    /**
     * @brief Add scalar to matrix in-place.
     *
     * @tparam T Scalar type.
     * @param scalar Scalar to add.
     * @return Matrix with scalar added.
     */
    template<typename T>
    Matrix& operator+=(const T scalar);

    /**
     * @brief Add matrix in-place.
     *
     * @param mat Matrix to add.
     * @return Matrix.
     */
    Matrix& operator+=(const Matrix& mat);

    // =============================================================================================
    // SUBTRACTION OPERATORS
    // =============================================================================================

    /**
     * @brief Subtract scalar from matrix in-place.
     *
     * @tparam T Scalar type.
     * @param scalar Scalar to subtract.
     * @return Matrix with scalar subtracted.
     */
    template<typename T>
    Matrix& operator-=(const T scalar);

    /**
     * @brief Subtract matrix in-place.
     *
     * @param mat Matrix to subtract.
     * @return Matrix.
     */
    Matrix& operator-=(const Matrix& mat);

    // =============================================================================================
    // MULTIPLICATION OPERATORS
    // =============================================================================================

    /**
     * @brief Multiply matrix by scalar in-place.
     *
     * @tparam T Scalar type.
     * @param scalar Scalar to multiply.
     * @return Matrix with scalar multiplied.
     */
    template<typename T>
    Matrix& operator*=(const T scalar);

    // =============================================================================================
    // DIVISION OPERATORS
    // =============================================================================================

    /**
     * @brief Divide matrix by scalar in-place.
     *
     * @details No divide-by-zero checks.
     *
     * @tparam T Scalar type.
     * @param scalar Scalar to divide.
     * @return Matrix divided by scalar.
     */
    template<typename T>
    Matrix& operator/=(const T scalar);

    /**
     * @brief Get an identity matrix (square only).
     *
     * @return Identity matrix.
     *
     * @exception std::domain_error Non-square matrix.
     */
    static Matrix identity();

protected:
private:
    std::array<matrix_type, T_ROWS * T_COLS> m_arr {0};  ///< Underlying array to store values (row-major order).
};

// =================================================================================================
// CLASS MEMBER FUNCTIONS
// =================================================================================================

template<std::size_t R, std::size_t C>
template<typename T>
Matrix<R,C>::Matrix(const std::initializer_list<T> new_matrix)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    const size_type input_size = new_matrix.size();

    if (input_size != (R * C)) {
        throw std::length_error(
            Internal::invalid_init_list_length_error_msg(input_size, R*C)
        );
    }

    std::copy(new_matrix.begin(), new_matrix.end(), m_arr.begin());
}

template<std::size_t R, std::size_t C>
template<typename T>
Matrix<R,C>::Matrix(const std::initializer_list<std::initializer_list<T>> new_matrix)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only..");

    const size_type input_rows = new_matrix.size();

    if (input_rows != R) {
        throw std::length_error(
            Internal::invalid_init_list_length_error_msg(input_rows, R)
        );
    }

    auto array_element = m_arr.begin();  // start at the beginning of the array

    for (const auto& row : new_matrix) {
        const size_type input_cols = row.size();

        if (input_cols != C) {
            throw std::length_error(
                Internal::invalid_init_list_length_error_msg(input_cols, C)
            );
        }

        for (const auto& val : row) {
            assert(array_element != m_arr.end());  // make sure we're not at the end
            *(array_element++) = static_cast<matrix_type>(val);  // assign value to array
        }
    }

    assert(array_element == m_arr.end());  // make sure we reached the end
}

template<std::size_t R, std::size_t C>
Matrix<R,C>& Matrix<R,C>::operator=(const Matrix& other)
{
    if (&other == this) {
        return *this;
    }

    m_arr = other.m_arr;
    return *this;
}

template<std::size_t R, std::size_t C>
Matrix<R,C>& Matrix<R,C>::operator=(Matrix&& other) noexcept
{
    if (&other == this) {
        return *this;
    }

    m_arr.swap(other.m_arr);
    return *this;
}

template<std::size_t R, std::size_t C>
[[nodiscard]] double& Matrix<R,C>::operator()(const std::size_t row, std::size_t col)
{
    return m_arr.at((row * C) + col);
}

template<std::size_t R, std::size_t C>
[[nodiscard]] const double& Matrix<R,C>::operator()(const std::size_t row, std::size_t col) const
{
    return m_arr.at((row * C) + col);
}

template<std::size_t R, std::size_t C>
[[nodiscard]] double& Matrix<R,C>::at(const std::size_t row, std::size_t col)
{
    return m_arr.at((row * C) + col);
}

template<std::size_t R, std::size_t C>
[[nodiscard]] const double& Matrix<R,C>::at(const std::size_t row, std::size_t col) const
{
    return m_arr.at((row * C) + col);
}

template<std::size_t R, std::size_t C>
Matrix<R,C> Matrix<R,C>::identity()
{
    if (R != C) {
        throw std::domain_error("Identity matrices are for square matrices only.");
    }

    Matrix eye;

    for (std::size_t ii = 0; ii < R; ii++) {
        eye.m_arr.at((ii * C) + ii) = 1.0;
    }

    return eye;
}

// =================================================================================================
// ADDITION OPERATORS
// =================================================================================================

template<std::size_t R, std::size_t C>
template<typename T>
Matrix<R,C>& Matrix<R,C>::operator+=(const T scalar)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    const auto scalard = static_cast<double>(scalar);

    std::for_each(
        m_arr.begin(),
        m_arr.end(),
        [scalard](double& element){element += scalard;}
    );

    return *this;
}

template<std::size_t R, std::size_t C>
Matrix<R,C>& Matrix<R,C>::operator+=(const Matrix& mat)
{
    for (std::size_t idx = 0; idx < m_arr.size(); idx++) {
        m_arr.at(idx) += mat.m_arr.at(idx);
    }

    return *this;
}

/**
 * @brief 2x2 matrix-matrix addition A + B.
 *
 * @details Expanded multiplication operations with SymPy.
 *
 * @code {.py}
 * a = sympy.MatrixSymbol('a', 2, 2)
 * b = sympy.MatrixSymbol('b', 2, 2)
 * numpy.add(a, b)
 * @endcode
 *
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix sum.
 */
inline Matrix<2,2> operator+(const Matrix<2,2>& a, const Matrix<2,2>& b)
{
    return Matrix<2,2>({
        {a(0,0) + b(0,0), a(0,1) + b(0,1)},
        {a(1,0) + b(1,0), a(1,1) + b(1,1)}
    });
}

/**
 * @brief 3x3 matrix-matrix addition A + B.
 *
 * @details Expanded multiplication operations with SymPy.
 *
 * @code {.py}
 * a = sympy.MatrixSymbol('a', 3, 3)
 * b = sympy.MatrixSymbol('b', 3, 3)
 * numpy.add(a, b)
 * @endcode
 *
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix sum.
 */
inline Matrix<3,3> operator+(const Matrix<3,3>& a, const Matrix<3,3>& b)
{
    return Matrix<3,3>({
        {a(0,0) + b(0,0), a(0,1) + b(0,1), a(0,2) + b(0,2)},
        {a(1,0) + b(1,0), a(1,1) + b(1,1), a(1,2) + b(1,2)},
        {a(2,0) + b(2,0), a(2,1) + b(2,1), a(2,2) + b(2,2)}
    });
}

/**
 * @brief Matrix-matrix addition A + B.
 *
 * @tparam N Matrix rows.
 * @tparam M Matrix columns.
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix-matrix sum.
 */
template<std::size_t N, std::size_t M>
Matrix<N,M> operator+(const Matrix<N,M>& a, const Matrix<N,M>& b)
{
    Matrix<N,M> c(a);

    for (std::size_t ii = 0; ii < N; ii++) {
        for (std::size_t jj = 0; jj < M; jj++) {
            c(ii, jj) += b(ii, jj);
        }
    }

    return c;
}

// =================================================================================================
// SUBTRACTION OPERATORS
// =================================================================================================

template<std::size_t R, std::size_t C>
template<typename T>
Matrix<R,C>& Matrix<R,C>::operator-=(const T scalar)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    const auto scalard = static_cast<matrix_type>(scalar);

    std::for_each(
        m_arr.begin(),
        m_arr.end(),
        [scalard](matrix_type& element){element -= scalard;}
    );

    return *this;
}

template<std::size_t R, std::size_t C>
Matrix<R,C>& Matrix<R,C>::operator-=(const Matrix& mat)
{
    for (std::size_t idx = 0; idx < (R*C); idx++) {
        m_arr.at(idx) -= mat.m_arr.at(idx);
    }

    return *this;
}

/**
 * @brief 2x2 matrix-matrix subtraction A - B.
 *
 * @details Expanded multiplication operations with SymPy.
 *
 * @code {.py}
 * a = sympy.MatrixSymbol('a', 2, 2)
 * b = sympy.MatrixSymbol('b', 2, 2)
 * numpy.subtract(a, b)
 * @endcode
 *
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix difference.
 */
inline Matrix<2,2> operator-(const Matrix<2,2>& a, const Matrix<2,2>& b)
{
    return Matrix<2,2>({
        {a(0,0) - b(0,0), a(0,1) - b(0,1)},
        {a(1,0) - b(1,0), a(1,1) - b(1,1)}
    });
}

/**
 * @brief 3x3 matrix-matrix subtraction A - B.
 *
 * @details Expanded multiplication operations with SymPy.
 *
 * @code {.py}
 * a = sympy.MatrixSymbol('a', 3, 3)
 * b = sympy.MatrixSymbol('b', 3, 3)
 * numpy.subtract(a, b)
 * @endcode
 *
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix difference.
 */
inline Matrix<3,3> operator-(const Matrix<3,3>& a, const Matrix<3,3>& b)
{
    return Matrix<3,3>({
        {a(0,0) - b(0,0), a(0,1) - b(0,1), a(0,2) - b(0,2)},
        {a(1,0) - b(1,0), a(1,1) - b(1,1), a(1,2) - b(1,2)},
        {a(2,0) - b(2,0), a(2,1) - b(2,1), a(2,2) - b(2,2)}
    });
}

/**
 * @brief Matrix-matrix subtraction A - B.
 *
 * @tparam N Matrix rows.
 * @tparam M Matrix columns.
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix-matrix difference.
 */
template<std::size_t N, std::size_t M>
Matrix<N,M> operator-(const Matrix<N,M>& a, const Matrix<N,M>& b)
{
    Matrix<N,M> c(a);

    for (std::size_t ii = 0; ii < N; ii++) {
        for (std::size_t jj = 0; jj < M; jj++) {
            c(ii, jj) -= b(ii, jj);
        }
    }

    return c;
}

// =================================================================================================
// MULTIPLICATION OPERATORS
// =================================================================================================

template<std::size_t R, std::size_t C>
template<typename T>
Matrix<R,C>& Matrix<R,C>::operator*=(const T scalar)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    const auto scalard = static_cast<matrix_type>(scalar);

    std::for_each(
        m_arr.begin(),
        m_arr.end(),
        [scalard](matrix_type& element){element *= scalard;}
    );

    return *this;
}

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
    const auto scalard = static_cast<double>(scalar);

    for (std::size_t ii = 0; ii < N; ii++) {
        for (std::size_t jj = 0; jj < M; jj++) {
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

    for (std::size_t ii = 0; ii < N; ii++) {
        for (std::size_t jj = 0; jj < P; jj++) {
            double sum = 0.0;

            for (std::size_t kk = 0; kk < M; kk++) {
                sum += a(ii, kk) * b(kk, jj);
            }

            c(ii, jj) = sum;
        }
    }

    return c;
}

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

    for (std::size_t ii = 0; ii < N; ii++) {
        double sum = 0.0;

        for (std::size_t jj = 0; jj < M; jj++) {
            sum += mat(ii, jj) * vec(jj);
        }

        res(ii) = sum;
    }

    return res;
}

// =================================================================================================
// DIVISION OPERATORS
// =================================================================================================

template<std::size_t R, std::size_t C>
template<typename T>
Matrix<R,C>& Matrix<R,C>::operator/=(const T scalar)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    // make sure denominator is not too small
    const auto scalard = static_cast<matrix_type>(scalar);

    std::for_each(
        m_arr.begin(),
        m_arr.end(),
        [scalard](matrix_type& element){element /= scalard;}
    );

    return *this;
}

// =================================================================================================
// OTHER OPERATORS
// =================================================================================================

/**
 * @brief Print a matrix to a stream. Comma-separates values. Does not add a newline at the end.
 *
 * @param os Output stream.
 * @param mat Matrix to print.
 * @return Output stream with matrix.
 */
template<std::size_t R, std::size_t C>
std::ostream& operator<<(std::ostream& os, const Matrix<R,C>& mat)
{
    // figure out how many chars are required to print a number
    auto num_str_chars = [](const double val){
        std::ostringstream ss;
        ss << val;
        return ss.str().size();
    };

    // loop through array and find the longest number
    std::size_t most_chars = 1;
    for (std::size_t ii = 0; ii < mat.rows(); ii++) {
        for (std::size_t jj = 0; jj < mat.cols(); jj++) {
            const std::size_t chars = num_str_chars(mat(ii, jj));
            most_chars = chars > most_chars ? chars : most_chars;
        }
    }
    /**
     * Print the matrix.
     * https://cplusplus.com/forum/beginner/275937/#msg1194918
     */
    for (std::size_t ii = 0; ii < mat.rows(); ii++) {
        for (std::size_t jj = 0; jj < mat.cols(); jj++) {
            std::string prefix = jj == 0 ? "\n" : "";  // put a newline or no char before the value
            std::string suffix = jj == mat.cols()-1 ? "" : ", ";  // put a comma or no char after the value

            os << prefix << std::setw(static_cast<int>(most_chars)) << std::left << mat(ii, jj) << suffix;
        }
    }

    return os;
}

// =================================================================================================
// OTHER FUNCTIONS
// =================================================================================================

/**
 * @brief Compute the trace of a matrix (sum of diagonal elements).
 *
 * @tparam Matrix dimension (square).
 * @param Matrix Matrix.
 * @return Matrix trace.
 */
template<std::size_t N>
[[nodiscard]] double trace(const Matrix<N,N>& mat)
{
    double tr = 0.0;

    for (std::size_t idx = 0; idx < N; idx++) {
        tr += mat(idx, idx);
    }

    return tr;
}

}    // namespace MathUtils
