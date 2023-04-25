/**
 * @file Quaternion.h
 * @author Michael Wrona
 * @date 2023-03-10
 * @brief Quaternion class.
 */

#pragma once

#include "LinAlg/Vector.h"

#include <array>
#include <initializer_list>
#include <iostream>

namespace MathUtils {

/**
 * @brief Quaternion class.
 *
 * @details Scalar-first representation: [s, x, y, z].
 */
class Quaternion {
public:

    using quat_type = double;
    using size_type = std::size_t;

    /**
     * @brief Create a quaternion.
     *
     * @details Sets to unity [1, 0, 0, 0]
     */
    Quaternion() = default;

    /**
     * @brief Destroy the quaternion.
     */
    ~Quaternion() = default;

    /**
     * @brief Create a quaternion. Normalizes input.
     *
     * @param qs Scalar component.
     * @param qx X-component.
     * @param qy Y-component.
     * @param qz Z-component.
     */
    Quaternion(const quat_type qs, const quat_type qx, const quat_type qy, const quat_type qz);

    /**
     * @brief Create a quaternion from an initializer list. Normalizes input.
     *
     * @param quat_vals Quaternion values.
     *
     * @exception std::length_error Input was not 4 elements.
     */
    Quaternion(const std::initializer_list<quat_type> quat_vals);

    /**
     * @brief Copy-construct quaternion.
     *
     * @param other Other quaternion.
     */
    Quaternion(const Quaternion& other) = default;

    /**
     * @brief Move construct quaternion.
     *
     * @param other Other quaternion.
     */
    Quaternion(Quaternion&& other) noexcept;

    /**
     * @brief Copy-assign quaternion.
     *
     * @param other Other quaternion.
     * @return Copied quaternion.
     */
    Quaternion& operator=(const Quaternion& other);

    /**
     * @brief Move-assign quaternion.
     *
     * @param other Other quaternion.
     * @return Copied quaternion.
     */
    Quaternion& operator=(Quaternion&& other) noexcept;

    /**
     * @brief Assign quaternion values from an initializer list. Normalizes input.
     *
     * @param quat_vals Quaternion values.
     * @return New quaternion.
     *
     * @exception std::length_error Input was not four elements.
     */
    Quaternion& operator=(const std::initializer_list<quat_type> quat_vals);

    /**
     * @brief Get quaternion element.
     *
     * @param idx Quaternion index.
     * @return Quaternion element at specified index.
     */
    [[nodiscard]] const quat_type& operator()(const std::size_t idx) const;

    /**
     * @brief Get quaternion element. With bounds checking.
     *
     * @param idx Quaternion index.
     * @return Value at index.
     *
     * @exception std::out_of_range Invalid quaternion index.
     */
    [[nodiscard]] const quat_type& at(const std::size_t idx) const;

    /**
     * @brief Return the inverse of the quaternion.
     *
     * @details q^-1 = [qs, -qx, -qy, -qz] / ||q||
     *
     * @return Quaternion inverse.
     */
    [[nodiscard]] Quaternion inverse() const;

    /**
     * @brief If the scalar part is negative, negate (*= -1) the quaternion elements to enforce a
     * positive rotation angle [0, 180].
     *
     * @return Quaternion.
     */
    void force_positive_rotation() noexcept;

    /**
     * @brief Normalize the quaternion to have a magnitude of 1.
     */
    void normalize();

    /**
     * @brief Return the quaternion's eigen axis.
     *
     * @details No divide-by-zero checks are performed.
     *
     * @return Quaternion eigen axis.
     */
    [[nodiscard]] Vector<3> eigen_axis() const;

    /**
     * @brief Return the quaternion's rotation angle.
     *
     * @return Quaternion rotation angle in [rad].
     */
    [[nodiscard]] quat_type angle() const;

    /**
     * @brief Print a quaternion to a stream. Comma-separates values. Does not add a newline at the end.
     *
     * @param os Output stream.
     * @param vec Quaternion to print.
     * @return Output stream with quaternion.
     *
     * @code {.cpp}
     * std::cout << my_vequat << "\n";
     * @endcode
     */
    friend std::ostream& operator<<(std::ostream& os, const Quaternion& quat);

protected:
private:
    std::array<quat_type, 4> m_arr {1, 0, 0, 0};  ///< Underlying array to store elements
};

// ============================================================================
// QUATERNION-ONLY OPERATOR OVERLOADS
// ============================================================================

/**
 * @brief Compute the quaternion product. Normalizes result.
 *
 * @details `q_a_c = q_a_b * q_b_c`
 *
 * "Analytical Mechanics of Aerospace Systems" equation 3.97.
 *
 * @param q_b First quaternion.
 * @param q_c Second quaternion.
 * @return Quaternion product q_b * q_c.
 */
inline Quaternion operator*(const Quaternion& q_b, const Quaternion& q_c)
{
    // NOTE: Constructor normalizes result.
    return Quaternion(
        (q_c(0) * q_b(0)) - (q_c(1) * q_b(1)) - (q_c(2) * q_b(2)) - (q_c(3) * q_b(3)),
        (q_c(1) * q_b(0)) + (q_c(0) * q_b(1)) + (q_c(3) * q_b(2)) - (q_c(2) * q_b(3)),
        (q_c(2) * q_b(0)) - (q_c(3) * q_b(1)) + (q_c(0) * q_b(2)) + (q_c(1) * q_b(3)),
        (q_c(3) * q_b(0)) + (q_c(2) * q_b(1)) - (q_c(1) * q_b(2)) + (q_c(0) * q_b(3))
    );
}

}    // namespace MathUtils
