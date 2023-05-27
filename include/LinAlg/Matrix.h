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
#include <concepts>
#include <initializer_list>
#include <iomanip>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>

namespace MathUtils {

/**
 * @brief Criteria for valid MathUtils::Matrix dimensions.
 *
 * @tparam ROWS Matrix rows.
 * @tparam COLS Matrix cols.
 */
template<std::size_t ROWS, std::size_t COLS>
concept valid_matrix_dims = (ROWS != 0) && (COLS != 0) && (ROWS != 1 && COLS != 1);

/**
 * @brief Criteria for a valid MathUtils::Matrix element.
 *
 * @tparam T Element type.
 */
template<typename T>
concept valid_matrix_element = std::integral<T> || std::floating_point<T>;

/**
 * @brief 2D matrix class.
 *
 * @details Stores elements in row-major order. All elements are zero at initialization.
 *
 * @tparam ROWS Number of rows.
 * @tparam COLS Number of columns.
 */
template<std::size_t ROWS, std::size_t COLS>
requires valid_matrix_dims<ROWS, COLS>
class Matrix {
public:
    Matrix() = default;

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
    requires valid_matrix_element<T>
    Matrix(const std::initializer_list<T> new_matrix)  //  cppcheck-suppress noExplicitConstructor
    {
        const std::size_t input_size = new_matrix.size();

        if (input_size != (ROWS * COLS))
        {
            throw std::length_error(
                Internal::invalid_init_list_length_error_msg(input_size, ROWS * COLS)
            );
        }

        std::copy(new_matrix.begin(), new_matrix.end(), m_arr.begin());
    }

    /**
     * @brief Create a matrix from an initializer list of lists.
     *
     * @details Row-major order.
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
    requires valid_matrix_element<T>
    Matrix(const std::initializer_list<std::initializer_list<T>> new_matrix)  //  cppcheck-suppress noExplicitConstructor
    {
        const std::size_t input_rows = new_matrix.size();

        if (input_rows != ROWS)
        {
            throw std::length_error(
                Internal::invalid_init_list_length_error_msg(input_rows, ROWS)
            );
        }

        auto array_element = m_arr.begin();  // start at the beginning of the array

        for (const auto& row : new_matrix)
        {
            const std::size_t input_cols = row.size();

            if (input_cols != COLS)
            {
                throw std::length_error(
                    Internal::invalid_init_list_length_error_msg(input_cols, COLS)
                );
            }

            for (const auto& val : row)
            {
                assert(array_element != m_arr.end());  // make sure we're not at the end
                *(array_element++) = static_cast<double>(val);  // assign value to array
            }
        }

        assert(array_element == m_arr.end());  // make sure we reached the end
    }

    Matrix(const Matrix& other) = default;

    Matrix(Matrix&& other) noexcept = default;

    Matrix& operator=(const Matrix& other) = default;

    Matrix& operator=(Matrix&& other) noexcept = default;

    /**
     * @brief Access matrix element.
     *
     * @param row Row index.
     * @param col Column index.
     * @return Matrix element at specified index.
     *
     */
    [[nodiscard]] double& operator()(const std::size_t row, std::size_t col)
    {
        return m_arr.at(get_array_index(row, col));
    }

    /**
     * @brief Get matrix element.
     *
     * @param row Row index.
     * @param col Column index.
     * @return Matrix element at specified index.
     */
    [[nodiscard]] const double& operator()(const std::size_t row, std::size_t col) const
    {
        return m_arr.at(get_array_index(row, col));
    }

    /**
     * @brief Access matrix element.
     *
     * @param row Row index.
     * @param col Column index.
     * @return Matrix element at specified index.
     *
     * @exception std::out_of_range Invalid matrix index.
     */
    [[nodiscard]] double& at(const std::size_t row, std::size_t col)
    {
        return m_arr.at(get_array_index(row, col));
    }

    /**
     * @brief Get matrix element.
     *
     * @param row Row index.
     * @param col Column index.
     * @return Matrix element at specified index.
     *
     * @exception std::out_of_range Invalid matrix index.
     */
    [[nodiscard]] const double& at(const std::size_t row, std::size_t col) const
    {
        return m_arr.at(get_array_index(row, col));
    }

    /**
     * @brief Get the number of rows in the matrix.
     *
     * @return Matrix rows.
     */
    [[nodiscard]] constexpr std::size_t rows() const noexcept
    {
        return ROWS;
    }

    /**
     * @brief Get the number of columns in the matrix.
     *
     * @return Matrix columns.
     */
    [[nodiscard]] constexpr std::size_t cols() const noexcept
    {
        return COLS;
    }

    /**
     * @brief Get the total number of elements in the matrix.
     *
     * @details `Matrix<3,3>::num_elements()` would be 9.
     *
     * @return Number of elements in the matrix.
     */
    [[nodiscard]] constexpr std::size_t num_elements() const noexcept
    {
        return ROWS * COLS;
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
    requires valid_matrix_element<T>
    Matrix& operator+=(const T scalar)
    {
        const auto scalard = static_cast<double>(scalar);

        std::for_each(
            m_arr.begin(),
            m_arr.end(),
            [scalard](auto& element){element += scalard;}
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
        for (std::size_t idx = 0; idx < m_arr.size(); idx++)
        {
            m_arr.at(idx) += mat.m_arr.at(idx);
        }

        return *this;
    }

    /**
     * @brief Matrix-matrix addition A + B.
     *
     * @details Uses operator+=(Matrix).
     *
     * @param MAT Other matrix.
     * @return Matrix-matrix sum.
     */
    Matrix operator+(const Matrix& mat) const
    {
        Matrix result(*this);
        return result += mat;
    }

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
    requires valid_matrix_element<T>
    Matrix& operator-=(const T scalar)
    {
        const auto scalard = static_cast<double>(scalar);

        std::for_each(
            m_arr.begin(),
            m_arr.end(),
            [scalard](auto& element){element -= scalard;}
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
        for (std::size_t idx = 0; idx < (ROWS * COLS); idx++)
        {
            m_arr.at(idx) -= mat.m_arr.at(idx);
        }

        return *this;
    }

    /**
     * @brief Subtract two matrices.
     *
     * @details Uses operator-=(Matrix).
     *
     * @param mat Other matrix.
     * @return Matrix difference, m1 - m2.
     */
    Matrix operator-(const Matrix& mat) const
    {
        Matrix result(*this);
        return result -= mat;
    }

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
    requires valid_matrix_element<T>
    Matrix& operator*=(const T scalar)
    {
        const auto scalard = static_cast<double>(scalar);

        std::for_each(
            m_arr.begin(),
            m_arr.end(),
            [scalard](auto& element){element *= scalard;}
        );

        return *this;
    }

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
    requires valid_matrix_element<T>
    Matrix& operator/=(const T scalar)
    {
        const auto scalard = static_cast<double>(scalar);

        std::for_each(
            m_arr.begin(),
            m_arr.end(),
            [scalard](auto& element){element /= scalard;}
        );

        return *this;
    }

    /**
     * @brief Get an identity matrix (square only).
     *
     * @tparam N Row dimension.
     * @tparam M Column dimension.
     * @return Identity matrix.
     */
    template<std::size_t N = ROWS, std::size_t M = COLS>
    static std::enable_if_t<N == M, Matrix> identity()
    {
        Matrix eye;  // zero-init

        for (std::size_t ii = 0; ii < ROWS; ii++)
        {
            /**
             * NOTE: UPDATE THIS WHEN SWAPPING ROW/COL MAJOR ORDER.
             * This cannot use get_array_index() since it is a static function.
             */
            eye.m_arr.at((ii * COLS) + ii) = 1.0;
        }

        return eye;
    }

private:
    /**
     * @brief Get 1-dimensional `m_arr` index corresponding to (row, col) indices.
     *
     * @details Row-major order.
     *
     * @param row Row index.
     * @param col Column index.
     * @return corresponding `m_arr` index.
     */
    std::size_t get_array_index(const std::size_t row, const std::size_t col) const noexcept
    {
        return (row * COLS) + col;
    }

private:
    std::array<double, ROWS * COLS> m_arr {0};  ///< Underlying array to store values.
};


// =================================================================================================
// MULTIPLICATION OPERATORS
// =================================================================================================

/**
 * @brief Scalar-matrix multiplication.
 *
 * @details Uses operator*=(T).
 *
 * @tparam N Rows.
 * @tparam M Columns.
 * @tparam T Scalar type
 * @param scalar Scalar to multiply.
 * @param mat Matrix to multiply.
 * @return Product.
 */
template<std::size_t N, std::size_t M, typename T>
requires valid_matrix_element<T>
Matrix<N,M> operator*(const T scalar, const Matrix<N,M>& mat)
{
    Matrix<N,M> result(mat);
    const auto scalard = static_cast<double>(scalar);
    return result *= scalard;
}

/**
 * @brief Matrix-scalar multiplication.
 *
 * @details Uses operator*(T).
 *
 * @tparam N Rows.
 * @tparam M Columns.
 * @tparam T Scalar type
 * @param mat Matrix to multiply.
 * @param scalar Scalar to multiply.
 * @return Product.
 */
template<std::size_t N, std::size_t M, typename T>
requires valid_matrix_element<T>
Matrix<N,M> operator*(const Matrix<N,M>& mat, const T scalar)
{
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
 * https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
 *
 * @tparam N Matrix A rows.
 * @tparam M Matrix A columns and matrix B rows.
 * @tparam P Matrix B columns.
 * @param a Matrix A.
 * @param b Matrix B.
 * @return Matrix-matrix product, (N, P).
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
 * @details http://www.cs.umsl.edu/~sanjiv/classes/cs5740/lectures/mvm.pdf
 *
 * @tparam N Rows.
 * @tparam M Columns.
 * @param mat Matrix.
 * @param vec Vector.
 * @return Matrix-vector product.
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
    for (std::size_t ii = 0; ii < mat.rows(); ii++)
    {
        for (std::size_t jj = 0; jj < mat.cols(); jj++)
        {
            const std::size_t chars = num_str_chars(mat(ii, jj));
            most_chars = (chars > most_chars) ? chars : most_chars;
        }
    }
    /**
     * Print the matrix.
     * https://cplusplus.com/forum/beginner/275937/#msg1194918
     */
    for (std::size_t ii = 0; ii < mat.rows(); ii++)
    {
        for (std::size_t jj = 0; jj < mat.cols(); jj++)
        {
            std::string prefix = (jj == 0) ? "\n" : "";  // put a newline or no char before the value
            std::string suffix = (jj == mat.cols()-1) ? "" : ", ";  // put a comma or no char after the value

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

    for (std::size_t idx = 0; idx < N; idx++)
    {
        tr += mat(idx, idx);
    }

    return tr;
}

}    // namespace MathUtils
