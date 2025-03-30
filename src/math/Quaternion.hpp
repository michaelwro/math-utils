/**
 * @file Quaternion.h
 * @author Michael Wrona
 * @date 2023-03-10
 * @brief Quaternion class.
 */

#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <tuple>

#include "math/Vector.hpp"

namespace math {

/**
 * @brief Quaternion class.
 *
 * @details Scalar-first representation: [s, x, y, z]. Sets to unity [1, 0, 0,
 * 0]
 */
class Quaternion {
public:
    Quaternion() = default;
    ~Quaternion() = default;

    /**
     * @brief Create a quaternion. Normalizes input.
     *
     * @param qs Scalar component.
     * @param qx X-component.
     * @param qy Y-component.
     * @param qz Z-component.
     */
    Quaternion(const double qs, const double qx, const double qy, const double qz);

    /**
     * @brief Number of quaternion elements.
     *
     * @return 4.
     */
    static constexpr std::size_t size() noexcept {
        return 4;
    }

    /**
     * @brief Scalar component.
     */
    const double& s() const noexcept;

    /**
     * @brief Scalar component.
     */
    const double& w() const noexcept;

    /**
     * @brief X-component.
     */
    const double& x() const noexcept;

    /**
     * @brief Y-component.
     */
    const double& y() const noexcept;

    /**
     * @brief Z-component.
     */
    const double& z() const noexcept;

    /**
     * @brief Get the vector components of the quaternion. NOT THE EIGEN AXIS!
     *
     * @return Vector component.
     */
    Vector<3> getVectorComponent() const;

    /**
     * @brief Get quaternion element.
     *
     * @param idx Quaternion index.
     * @return Quaternion element at specified index.
     */
    [[nodiscard]] const double& operator()(const std::size_t idx) const noexcept;

    /**
     * @brief Return the conjugate/inverse of the quaternion.
     *
     * @details q^-1 = [qs, -qx, -qy, -qz] / ||q||
     *
     * @return Quaternion inverse.
     */
    [[nodiscard]] Quaternion getConjugate() const;

    /**
     * @brief If the scalar part is negative, negate (*= -1) the quaternion
     * elements to enforce a positive rotation angle [0, 180].
     *
     * @return Quaternion.
     */
    void forcePositiveRotation();

    /**
     * @brief Normalize the quaternion to have a magnitude of 1. Uses the method from NASA
     * JEOD at
     * https://github.com/nasa/jeod/blob/d6afa961154db8d95570a5e379ccc36445fba52a/models/utils/quaternion/src/quat_norm.cc
     */
    void normalize();

    // [[nodiscard]] Vector<3> transform(const Vector<3>& vec) const;

    // [[nodiscard]] Vector<3> rotate(const Vector<3>& vec) const;

    /**
     * @brief Calculate the eigen angle and eigen axis for the quaternion.
     *
     * @return [rad] Eigen angle, [uvec] eigen axis.
     */
    [[nodiscard]] std::tuple<double, Vector<3>> getEigenAxisAngle() const;

    /**
     * @brief Return the quaternion's eigen axis.
     *
     * @details No divide-by-zero checks are performed.
     *
     * @return Quaternion eigen axis.
     */
    [[nodiscard]] Vector<3> getEigenAxis() const;

    /**
     * @brief Return the quaternion's rotation angle.
     *
     * @return [rad] Quaternion rotation angle.
     */
    [[nodiscard]] double getEigenAngle() const;

protected:
private:
    /**
     * @brief Multiply all array elements by `-1`.
     *
     * @tparam T Array type.
     * @tparam N Array size.
     * @param[in,out] arr Input array.
     */
    template <typename T, std::size_t N>
    static void negateArray(std::array<T, N>& arr) {
        static_assert(arr.size() > 1, "Invalid array size.");
        std::for_each(arr.begin(), arr.end(), [](T& val) { val *= -1.0; });
    }

    /**
     * @brief Threshold for the approximate normnalization method. See the NASA JEOD
     * docs for more info. Calculated with `import math; math.sqrt(8 * math.pow(2,
     * -54))`.
     */
    static constexpr double m_normalization_threshold {2.1073424255447017e-08};

    /**
     * @brief Underlying array to store elements, SCALAR-FIRST.
     */
    std::array<double, 4> m_arr {1, 0, 0, 0};
};

// =======================================================================================
// QUATERNION-ONLY OPERATOR OVERLOADS
// =======================================================================================

/**
 * @brief Compute the quaternion product. Hamilton transformation convention. Normalizes
 * result. Equation 34 from https://sites.utexas.edu/near/files/2022/07/Rotations.pdf
 *
 * @param q2 First (LHS) quaternion.
 * @param q1 Second (RHS) quaternion.
 * @return Quaternion product q2 * q1.
 */
Quaternion operator*(const Quaternion& q2, const Quaternion& q1);

/**
 * @brief Print a quaternion to a stream. Comma-separates values. Does not add a
 * newline at the end.
 *
 * @param os Output stream.
 * @param vec Quaternion to print.
 * @return Output stream with quaternion.
 *
 * @code {.cpp}
 * std::cout << my_quat << "\n";
 * @endcode
 */
std::ostream& operator<<(std::ostream& os, const Quaternion& quat);

}  // namespace math
