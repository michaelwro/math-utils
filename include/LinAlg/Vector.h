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
#include <concepts>
#include <initializer_list>
#include <iomanip>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>

namespace MathUtils {

/**
 * @brief Criteria for a valid MathUtils::Vector dimension.
 *
 * @tparam N Vector length.
 */
template<std::size_t N>
concept valid_vector_dim = N > 1;

/**
 * @brief Criteria for a valid MathUtils::Vector element.
 *
 * @tparam T Element type.
 */
template<typename T>
concept valid_vector_element = std::integral<T> || std::floating_point<T>;

/**
 * @brief N-length vector class.
 *
 * @tparam LEN Length of the vector.
 */
template<std::size_t LEN>
requires valid_vector_dim<LEN>
class Vector {
public:
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
    requires valid_vector_element<T>
    Vector(const std::initializer_list<T> vector_vals)  //  cppcheck-suppress noExplicitConstructor
    {
        const std::size_t input_length = vector_vals.size();

        if (input_length != LEN)
        {
            throw std::length_error(
                Internal::invalid_init_list_length_error_msg(input_length, LEN)
            );
        }

        std::copy(vector_vals.begin(), vector_vals.end(), m_arr.begin());
    }

    /**
     * @brief Copy-construct vector.
     *
     * @param other Other vector.
     */
    Vector(const Vector& other) = default;

    /**
     * @brief Move construct vector.
     *
     * @param other Other vector.
     */
    Vector(Vector&& other) noexcept = default;

    /**
     * @brief Copy-assign vector.
     * @param other Other vector.
     * @return Copied vector.
     */
    Vector& operator=(const Vector& other) = default;

    /**
     * @brief Move-assign vector.
     * @param other Other vector.
     * @return Copied vector.
     */
    Vector& operator=(Vector&& other) noexcept = default;

    /**
     * @brief Assign vector values from an initializer list.
     *
     * @tparam T Initializer list type.
     * @param vector_vals New vector.
     *
     * @exception std::length_error Initializer list length doesn't match vector size.
     */
    template<typename T>
    requires valid_vector_element<T>
    Vector& operator=(const std::initializer_list<T> vector_vals)
    {
        const std::size_t input_length = vector_vals.size();

        if (input_length != LEN)
        {
            throw std::length_error(
                Internal::invalid_init_list_length_error_msg(input_length, LEN)
            );
        }

        std::copy(vector_vals.begin(), vector_vals.end(), m_arr.begin());
        return *this;
    }

    /**
     * @brief Access vector element.
     *
     * @param idx Vector index.
     * @return Vector element at specified index.
     */
    [[nodiscard]] double& operator()(const std::size_t idx)
    {
        return m_arr.at(idx);
    }

    /**
     * @brief Get vector element.
     *
     * @param idx Vector index.
     * @return Vector value at specified index.
     */
    [[nodiscard]] const double& operator()(const std::size_t idx) const
    {
        return m_arr.at(idx);
    }

    /**
     * @brief Access vector element. With bounds checks.
     *
     * @param idx Vector index.
     * @return Vector element at specified index.
     *
     * @exception std::out_of_range Invalid vector index.
     */
    [[nodiscard]] double& at(const std::size_t idx)
    {
        return m_arr.at(idx);
    }

    /**
     * @brief Get vector element. With bounds checks.
     *
     * @param idx Vector index.
     * @return Vector element at specified index.
     *
     * @exception std::out_of_range Invalid vector index.
     */
    [[nodiscard]] const double& at(const std::size_t idx) const
    {
        return m_arr.at(idx);
    }

    /**
     * @brief Get the vector length (number of elements).
     *
     * @return Vector length.
     */
    [[nodiscard]] constexpr std::size_t size() const noexcept
    {
        return LEN;
    }

    /**
     * @brief Fill the entire vector with a value.
     *
     * @param val Value to fill the vector with.
     */
    void fill(const double val) noexcept
    {
        m_arr.fill(val);
    }

    /**
     * @brief Return the magnitude/norm of the vector.
     *
     * @return Vector magnitude.
     */
    [[nodiscard]] double magnitude() const
    {
        const double magn = std::accumulate(
            m_arr.begin(), m_arr.end(), 0.0,
            [](auto accum, const auto& val){return accum += val * val;}
        );

        assert(magn >= 0.0);
        return std::sqrt(magn);
    }

    /**
     * @brief Normalize the vector.
     *
     * @details No divide-by-zero checks.
     */
    void normalize()
    {
        const double magn = this->magnitude();

        std::for_each(m_arr.begin(), m_arr.end(), [magn](auto& val){val /= magn;});
    }

    /**
     * @brief Return the sum of all elements in the vector.
     *
     * @return Sum of all vector elements.
     */
    [[nodiscard]] double get_sum() const
    {
        return std::accumulate(m_arr.begin(), m_arr.end(), 0.0, std::plus<double>());
    }

    /**
     * @brief Multiply all elements by -1.0. Flip the sign of all elements.
     *
     * @return Vector with signs flipped.
     */
    void negate()
    {
        std::for_each(m_arr.begin(), m_arr.end(), [](auto& val){val *= -1.0;});
    }

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
    requires valid_vector_element<T>
    Vector& operator+=(const T scalar)
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
     * @brief Add vector in-place (accumulate).
     *
     * @param vec Vector to add.
     * @return Vector with other vector added.
     */
    Vector& operator+=(const Vector& vec) noexcept
    {
        for (std::size_t idx = 0; idx < LEN; idx++)
        {
            m_arr[idx] += vec.m_arr[idx];
        }

        return *this;
    }

    /**
     * @brief Add a vector and scalar.
     *
     * @details Calls operator+=(T).
     *
     * @tparam T Scalar type.
     * @param scalar Scalar to add.
     * @return Vector plus scalar.
     */
    template<typename T>
    requires valid_vector_element<T>
    Vector operator+(const T scalar) const
    {
        Vector result(*this);
        return result += scalar;
    }

    /**
     * @brief Add two vectors.
     *
     * @details Calls operator+=(Vector).
     *
     * @param vec Other vector.
     * @return Vector sum, v1 + v2.
     */
    Vector operator+(const Vector& vec) const
    {
        Vector result(*this);
        return result += vec;
    }

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
    requires valid_vector_element<T>
    Vector& operator-=(const T scalar)
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
     * @brief Subtract vector in-place.
     *
     * @param vec Vector to subtract.
     * @return Vector with other vector subtracted from it.
     */
    Vector& operator-=(const Vector& vec) noexcept
    {
        for (std::size_t idx = 0; idx < LEN; idx++)
        {
            m_arr[idx] -= vec.m_arr[idx];
        }

        return *this;
    }

    /**
     * @brief Subtract a scalar from a vector.
     *
     * @details Calls operator-=(T).
     *
     * @tparam T Scalar type.
     * @param scalar Scalar to subtract.
     * @return Vector minus scalar.
     */
    template<typename T>
    requires valid_vector_element<T>
    Vector operator-(const T scalar) const
    {
        Vector result(*this);
        return result -= scalar;
    }

    /**
     * @brief Subtract two vectors.
     *
     * @details Calls operator-=(Vector).
     *
     * @param vec Vector to subtract.
     * @return Vector difference, v1 - v2.
     */
    Vector operator-(const Vector& vec) const
    {
        Vector result(*this);
        return result -= vec;
    }

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
    requires valid_vector_element<T>
    Vector& operator*=(const T scalar)
    {
        const auto scalard = static_cast<double>(scalar);

        std::for_each(
            m_arr.begin(),
            m_arr.end(),
            [scalard](auto& element){element *= scalard;}
        );

        return *this;
    }

    /**
     * @brief Multiply two vectors in-place.
     *
     * @param vec Other vector to multiply by.
     * @return vec1 *= vec2.
     */
    Vector& operator*=(const Vector& vec) noexcept
    {
        for (std::size_t idx = 0; idx < LEN; idx++)
        {
            m_arr[idx] *= vec.m_arr[idx];
        }

        return *this;
    }

    /**
     * @brief Multiply two vectors.
     *
     * @details Calls operator*=(Vector).
     *
     * @param vec Other vector.
     * @return vec1 * vec2.
     */
    Vector operator*(const Vector& vec) const
    {
        Vector result(*this);
        return result *= vec;
    }

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
    requires valid_vector_element<T>
    Vector& operator/=(const T scalar)
    {
        const auto scalard = static_cast<double>(scalar);

        std::for_each(
            m_arr.begin(),
            m_arr.end(),
            [scalard](auto& element){element /= scalard;}
        );

        return *this;
    }

protected:
private:
    std::array<double, LEN> m_arr {0};  ///< Underlying array to store vector values.
};


// =================================================================================================
// MULTIPLICATION OPERATORS
// =================================================================================================

/**
 * @brief Multiply a vector by a scalar (scalar * vector).
 *
 * @details Calls operator*=(T).
 *
 * @tparam N Vector length.
 * @tparam T Scalar type.
 * @param scalar Scalar to multiply by.
 * @param vec Vector operand.
 * @return Vector times scalar.
 */
template<std::size_t N, typename T>
requires valid_vector_element<T>
Vector<N> operator*(const T scalar, const Vector<N>& vec)
{
    Vector<N> result(vec);
    result *= scalar;
    return result;
}

/**
 * @brief Multiply a vector by a scalar (vector * scalar).
 *
 * @details Calls operator(Vector, T).
 *
 * @tparam N Vector length.
 * @tparam T Scalar type.
 * @param scalar Scalar to multiply by.
 * @param vec Vector operand.
 * @return Vector times scalar.
 */
template<std::size_t N, typename T>
requires valid_vector_element<T>
Vector<N> operator*(const Vector<N>& vec, const T scalar)
{
    return scalar * vec;
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
    for (std::size_t idx = 0; idx < vec.size() - 1; idx++)
    {
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

    for (std::size_t idx = 0; idx < N; idx++)
    {
        dot_prod += v1(idx) * v2(idx);
    }

    return dot_prod;
}

}  // namespace MathUtils
