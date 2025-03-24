/**
 * @file Vector.h
 * @author Michael Wrona
 * @date 2023-03-08
 * @brief Vector template class & functions.
 */

#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <numeric>
#include <ostream>
#include <type_traits>

namespace math {

/**
 * @brief N-length vector.
 *
 * @details All elements are zero at initialization.
 *
 * @tparam LEN Length of the vector.
 */
template <std::size_t LEN>
class Vector {
public:
    Vector() = default;
    ~Vector() = default;

    /**
     * @brief Reassign new elements to a vector.
     *
     * @tparam Args Variadic template arguments.
     * @param elements New vector elements.
     */
    template <typename... Args>
    auto reassign(Args&&... elements)
        -> std::enable_if_t<(sizeof...(Args) == LEN) and
                                ((std::is_integral_v<std::common_type_t<Args...>>) or
                                 (std::is_floating_point_v<std::common_type_t<Args...>>)),
                            void> {
        m_arr = {std::forward<Args>(elements)...};
    }

    /**
     * @brief Assign elements to a vector.
     *
     * @tparam Args Variadic template argument.
     * @param elements New vector elements.
     * @return Populated vector.
     */
    template <typename... Args>
    [[nodiscard]] static auto assign(Args&&... elements)
        -> std::enable_if_t<(sizeof...(Args) == LEN) and
                                ((std::is_integral_v<std::common_type_t<Args...>>) or
                                 (std::is_floating_point_v<std::common_type_t<Args...>>)),
                            Vector> {
        Vector vec {};
        std::size_t idx = 0;

        for (const auto& element : {elements...}) {
            vec.m_arr[idx++] = static_cast<double>(element);
        }

        assert(idx == size());

        return vec;
    }

    /**
     * @brief Access vector element.
     *
     * @param idx Vector index.
     * @return Vector element at specified index.
     */
    [[nodiscard]] double& operator()(const std::size_t idx) {
        assert(idx < size());
        return m_arr[idx];
    }

    /**
     * @brief Get vector element.
     *
     * @param idx Vector index.
     * @return Vector value at specified index.
     */
    [[nodiscard]] const double& operator()(const std::size_t idx) const {
        assert(idx < size());
        return m_arr[idx];
    }

    /**
     * @brief Get the vector length (number of elements).
     *
     * @return Vector length.
     */
    [[nodiscard]] static constexpr std::size_t size() noexcept {
        return LEN;
    }

    /**
     * @brief Fill the entire vector with a value.
     *
     * @param val Value to fill the vector with.
     */
    void fill(const double val) noexcept {
        m_arr.fill(val);
    }

    /**
     * @brief Return the magnitude/norm of the vector.
     *
     * @return Vector magnitude.
     */
    [[nodiscard]] double magnitude() const {
        const double magn = std::accumulate(
            m_arr.begin(), m_arr.end(), 0.0,
            [](auto accum, const auto& val) { return accum += val * val; });

        assert(magn >= 0.0);
        return std::sqrt(magn);
    }

    /**
     * @brief Normalize the vector.
     *
     * @details No divide-by-zero checks.
     */
    void normalize() {
        const double magn = this->magnitude();

        std::for_each(m_arr.begin(), m_arr.end(), [magn](auto& val) { val /= magn; });
    }

    /**
     * @brief Return the sum of all elements in the vector.
     *
     * @return Sum of all vector elements.
     */
    [[nodiscard]] double sum() const {
        return std::accumulate(m_arr.begin(), m_arr.end(), 0.0, std::plus<double>());
    }

    /**
     * @brief Multiply all elements by -1.0. Flip the sign of all elements.
     *
     * @return Vector with signs flipped.
     */
    void negate() {
        std::for_each(m_arr.begin(), m_arr.end(), [](auto& val) { val *= -1.0; });
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
    template <typename T>
    Vector& operator+=(const T scalar) {
        static_assert(isValidType<T>(), "Invalid type.");

        const auto scalard = static_cast<double>(scalar);

        std::for_each(m_arr.begin(), m_arr.end(),
                      [scalard](auto& element) { element += scalard; });

        return *this;
    }

    /**
     * @brief Add vector in-place (accumulate).
     *
     * @param vec Vector to add.
     * @return Vector with other vector added.
     */
    Vector& operator+=(const Vector& vec) noexcept {
        for (std::size_t idx = 0; idx < size(); idx++) {
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
    template <typename T>
    Vector operator+(const T scalar) const {
        static_assert(isValidType<T>(), "Invalid type.");
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
    Vector operator+(const Vector& vec) const {
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
    template <typename T>
    Vector& operator-=(const T scalar) {
        static_assert(isValidType<T>(), "Invalid type.");
        const auto scalard = static_cast<double>(scalar);

        std::for_each(m_arr.begin(), m_arr.end(),
                      [scalard](auto& element) { element -= scalard; });

        return *this;
    }

    /**
     * @brief Subtract vector in-place.
     *
     * @param vec Vector to subtract.
     * @return Vector with other vector subtracted from it.
     */
    Vector& operator-=(const Vector& vec) noexcept {
        for (std::size_t idx = 0; idx < size(); idx++) {
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
    template <typename T>
    Vector operator-(const T scalar) const {
        static_assert(isValidType<T>(), "Invalid type.");
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
    Vector operator-(const Vector& vec) const {
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
    template <typename T>
    Vector& operator*=(const T scalar) {
        static_assert(isValidType<T>(), "Invalid type.");

        const auto scalard = static_cast<double>(scalar);

        std::for_each(m_arr.begin(), m_arr.end(),
                      [scalard](auto& element) { element *= scalard; });

        return *this;
    }

    /**
     * @brief Multiply two vectors in-place.
     *
     * @param vec Other vector to multiply by.
     * @return vec1 *= vec2.
     */
    Vector& operator*=(const Vector& vec) noexcept {
        for (std::size_t idx = 0; idx < size(); idx++) {
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
    Vector operator*(const Vector& vec) const {
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
    template <typename T>
    Vector& operator/=(const T scalar) {
        static_assert(isValidType<T>(), "Invalid type.");

        const auto scalard = static_cast<double>(scalar);

        std::for_each(m_arr.begin(), m_arr.end(),
                      [scalard](auto& element) { element /= scalard; });

        return *this;
    }

    /**
     * @brief Check if a type is a valid vector element.
     *
     * @tparam The type.
     * @return True if valid, valse otherwise.
     */
    template <typename T>
    static constexpr auto isValidType()
        -> std::enable_if_t<std::is_integral_v<T> or std::is_floating_point_v<T>, bool> {
        return true;
    }

private:
    std::array<double, LEN> m_arr {0};  ///< Underlying array to store vector values.
};

// =======================================================================================
// MULTIPLICATION OPERATORS
// =======================================================================================

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
template <std::size_t N, typename T>
Vector<N> operator*(const T scalar, const Vector<N>& vec) {
    static_assert(Vector<N>::template isValidType<T>(), "Invalid Type");

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
template <std::size_t N, typename T>
Vector<N> operator*(const Vector<N>& vec, const T scalar) {
    static_assert(Vector<N>::template isValidType<T>(), "Invalid Type");

    return scalar * vec;
}

// =======================================================================================
// OTHER OPERATORS
// =======================================================================================

/**
 * @brief Print a vector to a stream. Comma-separates values. Does not add a
 * newline at the end.
 *
 * @param os Output stream.
 * @param vec Vector to print.
 * @return Output stream with vector.
 *
 * @code {.cpp}
 * std::cout << my_vector << "\n";
 * @endcode
 */
template <std::size_t N>
std::ostream& operator<<(std::ostream& os, const Vector<N>& vec) {
    for (std::size_t idx = 0; idx < vec.size() - 1; idx++) {
        os << vec(idx) << ", ";
    }

    os << vec(vec.size() - 1);
    return os;
}

// =======================================================================================
// VECTOR-ONLY FUNCTIONS
// =======================================================================================

/**
 * @brief 3D vector cross product of v1 x v2.
 *
 * @param v1 Vector 1 (LHS).
 * @param v2 Vector2 (RHS).
 * @return Vector cross product.
 */
inline Vector<3> cross(const Vector<3>& v1, const Vector<3>& v2) {
    return Vector<3>::assign((v1(1) * v2(2)) - (v1(2) * v2(1)),
                             (v1(2) * v2(0)) - (v1(0) * v2(2)),
                             (v1(0) * v2(1)) - (v1(1) * v2(0)));
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
inline double dot(const Vector<2>& v1, const Vector<2>& v2) {
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
inline double dot(const Vector<3>& v1, const Vector<3>& v2) {
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
template <std::size_t N>
double dot(const Vector<N>& v1, const Vector<N>& v2) {
    double dot_prod = 0.0;

    for (std::size_t idx = 0; idx < N; idx++) {
        dot_prod += v1(idx) * v2(idx);
    }

    return dot_prod;
}

}  // namespace math
