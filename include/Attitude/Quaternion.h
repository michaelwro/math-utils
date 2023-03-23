/**
 * @file Quaternion.h
 * @author Michael Wrona
 * @date 2023-03-10
 * @brief Quaternion class.
 */

#ifndef MATHUTILS_ATTITUDE_QUATERNION_H_
#define MATHUTILS_ATTITUDE_QUATERNION_H_

#include "float_equality.h"
#include "Internal/error_msg_helpers.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <type_traits>

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
  Quaternion(const double qs, const double qx, const double qy, const double qz)
    :m_arr{qs, qx, qy, qz}
  {
    this->normalize();
  }

  /**
   * @brief Create a quaternion from an initializer list. Normalizes input.
   *
   * @param quat_vals Quaternion values.
   */
  explicit Quaternion(const std::initializer_list<double> quat_vals)
  {
    // assert since quaternions shall always have 4 elements.
    assert(quat_vals.size() == 4);

    std::copy(quat_vals.begin(), quat_vals.end(), m_arr.begin());

    this->normalize();
  }

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
  Quaternion& operator=(const Quaternion& other)
  {
    if (&other == this)
    {
      return *this;
    }

    m_arr = other.m_arr;
    return *this;
  }

  /**
   * @brief Move-assign quaternion.
   *
   * @param other Other quaternion.
   * @return Copied quaternion.
   */
  Quaternion& operator=(Quaternion&& other)
  {
    if (&other == this)
    {
      return *this;
    }

    m_arr.swap(other.m_arr);
    return *this;
  }

  /**
   * @brief Assign quaternion values from an initializer list. Normalizes input.
   *
   * @param quat_vals Quaternion values.
   * @return New quaternion.
   *
   * @exception std::length_error Input was not four elements.
   */
  Quaternion& operator=(const std::initializer_list<double> quat_vals)
  {
    // assert since quaternions shall always have 4 elements.
    assert(quat_vals.size() == 4);

    std::copy(quat_vals.begin(), quat_vals.end(), m_arr.begin());
    this->normalize();

    return *this;
  }

  /**
   * @brief Get quaternion element.
   *
   * @param idx Quaternion index.
   * @return Quaternion element at specified index.
   */
  const double& operator()(const std::size_t idx) const noexcept
  {
    assert(idx < 4);
    return m_arr[idx];
  }

  /**
   * @brief Return the conjugate (inverse) of the quaternion.
   *
   * @return Quaternion conjugate/inverse.
   */
  Quaternion conjugate() const
  {
    return Quaternion(m_arr[0], -m_arr[1], -m_arr[2], -m_arr[3]);
  }

  /**
   * @brief Invert the quaternion.
   */
  void invert() noexcept
  {
    m_arr[1] *= -1.0;
    m_arr[2] *= -1.0;
    m_arr[3] *= -1.0;
  }

  /**
   * @brief Negate (*= -1) the quaternion if the scalar component is negative to force a positive rotation.
   *
   * @return Quaternion.
   */
  void force_positive_rotation() noexcept
  {
    if (m_arr[0] < 0.0)
    {
      m_arr[0] *= -1.0;
      m_arr[1] *= -1.0;
      m_arr[2] *= -1.0;
      m_arr[3] *= -1.0;
    }
  }

  /**
   * @brief Normalize the quaternion to have a magnitude of 1.
   */
  void normalize() noexcept
  {
    // compute magnitude
    const double magn = std::sqrt(
      (m_arr[0] * m_arr[0]) +
      (m_arr[1] * m_arr[1]) +
      (m_arr[2] * m_arr[2]) +
      (m_arr[3] * m_arr[3])
    );

    /**
     * Make sure its not too small before dividing.
     * Assert instead of throwing, since it would never make logical sense that a quaternion would have zero
     * magnitude. Also, throwing assumes that there'd be a corrective action for this scenario, which there
     * really isn't.
     */
    assert(!float_equality(magn, 0.0));

    // normalize each element
    m_arr[0] /= magn;
    m_arr[1] /= magn;
    m_arr[2] /= magn;
    m_arr[3] /= magn;
  }

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
  friend std::ostream& operator<<(std::ostream& os, const Quaternion& quat)
  {
    os << quat.m_arr[0] << ", " <<
      quat.m_arr[1] << ", " <<
      quat.m_arr[2] << ", " <<
      quat.m_arr[3];

    return os;
  }

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
