/**
 * @file Quaternion.h
 * @author Michael Wrona
 * @date 2023-03-10
 * @brief Quaternion class.
 */

#ifndef MATHUTILS_ATTITUDE_QUATERNION_H_
#define MATHUTILS_ATTITUDE_QUATERNION_H_

#include "LinAlg/Vector.h"

#include <array>
#include <functional>
#include <initializer_list>
#include <iostream>

namespace MathUtils {

/**
 * @brief Quaternion class.
 *
 * @details Scalar-first representation: [s, x, y, z].
 */
class Quaternion
{
public:
  /**
   * @brief Create a quaternion.
   *
   * @details Sets to unity [1, 0, 0, 0]
   */
  Quaternion()
    :m_arr{1.0, 0.0, 0.0, 0.0}
  {}

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
  Quaternion(const double qs, const double qx, const double qy, const double qz);

  /**
   * @brief Create a quaternion from an initializer list. Normalizes input.
   *
   * @param quat_vals Quaternion values.
   *
   * @exception std::length_error Input was not 4 elements.
   */
  explicit Quaternion(const std::initializer_list<double> quat_vals);

  /**
   * @brief Copy-construct quaternion.
   *
   * @param other Other quaternion.
   */
  Quaternion(const Quaternion& other)
    :m_arr{other.m_arr}
  {}

  /**
   * @brief Move construct quaternion.
   *
   * @param other Other quaternion.
   */
  Quaternion(Quaternion&& other) noexcept
    :m_arr{std::move(other.m_arr)}
  {}

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
  Quaternion& operator=(Quaternion&& other);

  /**
   * @brief Assign quaternion values from an initializer list. Normalizes input.
   *
   * @param quat_vals Quaternion values.
   * @return New quaternion.
   *
   * @exception std::length_error Input was not four elements.
   */
  Quaternion& operator=(const std::initializer_list<double> quat_vals);

  /**
   * @brief Get quaternion element.
   *
   * @param idx Quaternion index.
   * @return Quaternion element at specified index.
   */
  const double& operator()(const std::size_t idx) const noexcept;

  /**
   * @brief Return the conjugate (inverse) of the quaternion.
   *
   * @return Quaternion conjugate/inverse.
   */
  Quaternion conjugate() const;

  /**
   * @brief Invert the quaternion.
   */
  void invert() noexcept;

  /**
   * @brief Negate (*= -1) the quaternion if the scalar component is negative to force a positive rotation.
   *
   * @return Quaternion.
   */
  void force_positive_rotation() noexcept;

  /**
   * @brief Normalize the quaternion to have a magnitude of 1.
   */
  void normalize() noexcept;

  /**
   * @brief Return the quaternion's eigen axis.
   *
   * @return Quaternion eigen axis.
   */
  Vector<3> eigen_axis() const;

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
  std::array<double, 4> m_arr;  ///< Underlying array to store elements
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

}  // namespace MathUtils

#endif  // MATHUTILS_ATTITUDE_QUATERNION_H_
