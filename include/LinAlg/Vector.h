/**
 * @file Vector.h
 * @author Michael Wrona
 * @date 2023-03-08
 * @brief Vector template class & functions.
 */

#pragma once

#include "Internal/error_msg_helpers.h"

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
 * @brief N-length vector class.
 *
 * @tparam T_LEN Length of the vector.
 */
template<std::size_t T_LEN>
class Vector {
public:

    using size_type = std::size_t;
    using vector_type = double;

    static_assert(T_LEN > 1, "One-length or zero-length vectors are not allowed.");

    /**
     * @brief Create a Vector.
     */
    Vector() = default;

    /**
     * @brief Destroy Vector.
     */
    ~Vector() = default;

    /**
     * @brief Create a vector from an initializer list.
     *
     * @tparam T Initializer list data type.
     * @param vector_vals Vector values.
     *
     * @exception std::length_error Initializer list length doesn't match vector size.
     */
    template<typename T>
    explicit Vector(const std::initializer_list<T> vector_vals);

    /**
     * @brief Copy-construct vector.
     *
     * @param other Other vector.
     */
    Vector(const Vector& other)
        :m_arr{other.m_arr}
    {}

    /**
     * @brief Move construct vector.
     *
     * @param other Other vector.
     */
    Vector(Vector&& other) noexcept
        :m_arr{std::move(other.m_arr)}
    {}

    /**
     * @brief Copy-assign vector.
     * @param other Other vector.
     * @return Copied vector.
     */
    Vector& operator=(const Vector& other);

    /**
     * @brief Move-assign vector.
     * @param other Other vector.
     * @return Copied vector.
     */
    Vector& operator=(Vector&& other) noexcept;

    /**
     * @brief Assign vector values from an initializer list.
     *
     * @tparam T Initializer list type.
     * @param vector_vals New vector.
     *
     * @exception std::length_error Initializer list length doesn't match vector size.
     */
    template<typename T>
    Vector& operator=(const std::initializer_list<T> vector_vals);

    /**
     * @brief Access vector element.
     *
     * @param idx Vector index.
     * @return Vector element at specified index.
     */
    [[nodiscard]] vector_type& operator()(const size_type idx);

    /**
     * @brief Get vector element. No bounds checks.
     *
     * @param idx Vector index.
     * @return Vector value at specified index.
     */
    [[nodiscard]] const vector_type& operator()(const size_type idx) const;

    /**
     * @brief Access vector element. With bounds checks.
     *
     * @param idx Vector index.
     * @return Vector element at specified index.
     *
     * @exception std::out_of_range Invalid vector index.
     */
    [[nodiscard]] vector_type& at(const size_type idx);

    /**
     * @brief Get vector element. With bounds checks.
     *
     * @param idx Vector index.
     * @return Vector element at specified index.
     *
     * @exception std::out_of_range Invalid vector index.
     */
    [[nodiscard]] const vector_type& at(const size_type idx) const;

    /**
     * @brief Get the vector length (number of elements).
     *
     * @return Vector length.
     */
    [[nodiscard]] constexpr size_type size() const noexcept;

    /**
     * @brief Fill the entire vector with a value.
     *
     * @param val Value to fill the vector with.
     */
    void fill(const vector_type val) noexcept;

    /**
     * @brief Return the magnitude/norm of the vector.
     *
     * @return Vector magnitude.
     */
    [[nodiscard]] vector_type magnitude() const;

    /**
     * @brief Normalize the vector.
     *
     * @details No divide-by-zero checks.
     */
    void normalize();

    /**
     * @brief Return the sum of all elements in the vector.
     *
     * @return Sum of all vector elements.
     */
    [[nodiscard]] vector_type get_sum() const;

    /**
     * @brief Multiply all elements by -1.0. Flip the sign of all elements.
     *
     * @return Vector with signs flipped.
     */
    void negate();

    // =============================================================================================
    // ADDITION OPERATORS
    // =============================================================================================

    /**
     * @brief Add scalar to all vector elements in-place (accumulate).
     *
     * @tparam T Scalar type.
     * @param scalar Scalar to add.
     * @return Vector with scalar added.
     */
    template<typename T>
    Vector& operator+=(const T scalar);

    /**
     * @brief Add vector in-place (accumulate).
     *
     * @param vec Vector to add.
     * @return Vector with other vector added.
     */
    Vector& operator+=(const Vector& vec) noexcept;

    // =============================================================================================
    // SUBTRACTION OPERATORS
    // =============================================================================================

    /**
     * @brief Subtract scalar from all vector elements in-place.
     *
     * @tparam T Scalar type.
     * @param scalar Scalar to subtract.
     * @return Vector with scalar subtracted.
     */
    template<typename T>
    Vector& operator-=(const T scalar);

    /**
     * @brief Subtract vector in-place.
     *
     * @param vec Vector to subtract.
     * @return Vector with other vector subtracted from it.
     */
    Vector& operator-=(const Vector& vec) noexcept;

    // =============================================================================================
    // MULTIPLICATION OPERATORS
    // =============================================================================================

    /**
     * @brief Multiply all elements by a scalar in-place.
     *
     * @tparam T Scalar type.
     * @param scalar Scalar to multiply by.
     * @return Vector with scalar multiplied.
     */
    template<typename T>
    Vector& operator*=(const T scalar);

    // =============================================================================================
    // DIVISION OPERATORS
    // =============================================================================================

    /**
     * @brief Divide all elements by a scalar in-place.
     *
     * @details No divide-by-zero checks.
     *
     * @tparam T Scalar type.
     * @param scalar Scalar to divide by.
     * @return Vector with scalar divided.
     */
    template<typename T>
    Vector& operator/=(const T scalar);

protected:
private:
    std::array<vector_type, T_LEN> m_arr {0.0};  ///< Underlying array to store vector values.
};

// =================================================================================================
// CLASS MEMBER FUNCTIONS
// =================================================================================================

template<std::size_t N>
template<typename T>
Vector<N>::Vector(const std::initializer_list<T> vector_vals)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    const std::size_t input_length = vector_vals.size();

    if (input_length != N) {
        throw std::length_error(
            Internal::invalid_init_list_length_error_msg(input_length, N)
        );
    }

    std::copy(vector_vals.begin(), vector_vals.end(), m_arr.begin());
}

template<std::size_t N>
Vector<N>& Vector<N>::operator=(const Vector& other)
{
    if (&other == this) {
        return *this;
    }

    m_arr = other.m_arr;
    return *this;
}

template<std::size_t N>
Vector<N>& Vector<N>::operator=(Vector&& other) noexcept
{
    if (&other == this) {
        return *this;
    }

    m_arr.swap(other.m_arr);
    return *this;
}

template<std::size_t N>
template<typename T>
Vector<N>& Vector<N>::operator=(const std::initializer_list<T> vector_vals)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    const std::size_t input_length = vector_vals.size();

    if (input_length != N) {
        throw std::length_error(
            Internal::invalid_init_list_length_error_msg(input_length, N)
        );
    }

    std::copy(vector_vals.begin(), vector_vals.end(), m_arr.begin());
    return *this;
}

template<std::size_t N>
[[nodiscard]] double& Vector<N>::operator()(const size_type idx)
{
    return m_arr.at(idx);
}

template<std::size_t N>
[[nodiscard]] const double& Vector<N>::operator()(const std::size_t idx) const
{
    return m_arr.at(idx);
}

template<std::size_t N>
[[nodiscard]] double& Vector<N>::at(const std::size_t idx)
{
    return m_arr.at(idx);
}

template<std::size_t N>
[[nodiscard]] const double& Vector<N>::at(const std::size_t idx) const
{
    return m_arr.at(idx);
}

template<std::size_t N>
[[nodiscard]] constexpr std::size_t Vector<N>::size() const noexcept
{
    return N;
}

template<std::size_t N>
void Vector<N>::fill(const double val) noexcept
{
    m_arr.fill(val);
}

template<std::size_t N>
[[nodiscard]] double Vector<N>::magnitude() const
{
    const double magn = std::accumulate(
        m_arr.begin(), m_arr.end(), 0.0,
        [](double accum, const double& val){return accum += val * val;}
    );

    /**
     * NOTE: Since all elements were squared in the above operation, this argument should never
     * be negative.
     * TODO: Use safe_sqrt
     */
    assert(magn >= 0.0);
    return std::sqrt(magn);
}

template<std::size_t N>
void Vector<N>::normalize()
{
    const double magn = this->magnitude();

    std::for_each(m_arr.begin(), m_arr.end(), [magn](double& val){val /= magn;});
}

template<std::size_t N>
[[nodiscard]] double Vector<N>::get_sum() const
{
    return std::accumulate(m_arr.begin(), m_arr.end(), 0.0, std::plus<>());
}

template<std::size_t N>
void Vector<N>::negate()
{
    std::for_each(m_arr.begin(), m_arr.end(), [](double& val){val *= -1.0;});
}

// =================================================================================================
// ADDITION OPERATORS
// =================================================================================================

template<std::size_t N>
template<typename T>
Vector<N>& Vector<N>::operator+=(const T scalar)
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

template<std::size_t N>
Vector<N>& Vector<N>::operator+=(const Vector& vec) noexcept
{
    for (std::size_t idx = 0; idx < N; idx++) {
        m_arr[idx] += vec.m_arr[idx];
    }

    return *this;
}

/**
 * @brief Add two vectors.
 *
 * @tparam N Vector length.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Vector sum, v1 + v2.
 */
template<std::size_t N>
Vector<N> operator+(const Vector<N>& v1, const Vector<N>& v2)
{
    Vector<N> result(v1);

    for (std::size_t idx = 0; idx < N; idx++) {
        result(idx) += v2(idx);
    }

    return result;
}

// =================================================================================================
// SUBTRACTION OPERATORS
// =================================================================================================

template<std::size_t N>
template<typename T>
Vector<N>& Vector<N>::operator-=(const T scalar)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    const auto scalard = static_cast<double>(scalar);

    std::for_each(
        m_arr.begin(),
        m_arr.end(),
        [scalard](double& element){element -= scalard;}
    );

    return *this;
}

template<std::size_t N>
Vector<N>& Vector<N>::operator-=(const Vector& vec) noexcept
{
    for (std::size_t idx = 0; idx < N; idx++)
    {
        m_arr[idx] -= vec.m_arr[idx];
    }

    return *this;
}

/**
 * @brief Subtract two vectors.
 *
 * @tparam N Vector length.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Vector difference, v1 - v2.
 */
template<std::size_t N>
Vector<N> operator-(const Vector<N>& v1, const Vector<N>& v2)
{
    Vector<N> result(v1);

    for (std::size_t idx = 0; idx < N; idx++) {
        result(idx) -= v2(idx);
    }

    return result;
}

// =================================================================================================
// MULTIPLICATION OPERATORS
// =================================================================================================

template<std::size_t N>
template<typename T>
Vector<N>& Vector<N>::operator*=(const T scalar)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    const auto scalard = static_cast<double>(scalar);

    std::for_each(
        m_arr.begin(),
        m_arr.end(),
        [scalard](double& element){element *= scalard;}
    );

    return *this;
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
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    Vector<N> res(vec);
    const auto scalard = static_cast<double>(scalar);

    for (std::size_t idx = 0; idx < vec.size(); idx++) {
        res(idx) *= scalard;
    }

    return res;
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
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");
    return scalar * vec;
}

/**
 * @brief Multiply two vectors.
 *
 * @tparam N Vector length.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Vector product, v1 * v2.
 */
template<std::size_t N>
Vector<N> operator*(const Vector<N>& v1, const Vector<N>& v2)
{
    Vector<N> result(v1);

    for (std::size_t idx = 0; idx < N; idx++) {
        result(idx) *= v2(idx);
    }

    return result;
}

// =================================================================================================
// DIVISION OPERATORS
// =================================================================================================

template<std::size_t N>
template<typename T>
Vector<N>& Vector<N>::operator/=(const T scalar)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");

    const auto scalard = static_cast<double>(scalar);

    std::for_each(
        m_arr.begin(),
        m_arr.end(),
        [scalard](double& element){element /= scalard;}
    );

    return *this;
}

// =================================================================================================
// OTHER OPERATORS
// =================================================================================================

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
template<std::size_t N>
std::ostream& operator<<(std::ostream& os, const Vector<N>& vec)
{
    for (std::size_t idx = 0; idx < vec.size() - 1; idx++) {
        os << vec(idx) << ", ";
    }

    os << vec(vec.size() - 1);
    return os;
}

// =================================================================================================
// VECTOR-ONLY FUNCTIONS
// =================================================================================================

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
 * @details Explicit calculation for length-2 vectors.
 *
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Dot product.
 */
inline double dot(const Vector<2>& v1, const Vector<2>& v2)
{
    return (v1(0) * v2(0)) + (v1(1) * v2(1));
}

/**
 * @brief Compute the vector dot product.
 *
 * @details Explicit calculation for length-3 vectors.
 *
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Dot product.
 */
inline double dot(const Vector<3>& v1, const Vector<3>& v2)
{
    return (v1(0) * v2(0)) + (v1(1) * v2(1)) + (v1(2) * v2(2));
}

/**
 * @brief Compute the vector dot product.
 *
 * @tparam N Vector length.
 * @param v1 First vector.
 * @param v2 Second vector.
 * @return Dot product.
 */
template<std::size_t N>
double dot(const Vector<N>& v1, const Vector<N>& v2)
{
    double dot_prod = 0.0;

    for (std::size_t idx = 0; idx < N; idx++) {
        dot_prod += v1(idx) * v2(idx);
    }

    return dot_prod;
}

}  // namespace MathUtils
