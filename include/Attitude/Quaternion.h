/**
 * @file Quaternion.h
 * @author Michael Wrona
 * @date 2023-03-10
 * @brief Quaternion class.
 */

#ifndef MATHUTILS_ATTITUDE_QUATERNION_H_
#define MATHUTILS_ATTITUDE_QUATERNION_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
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
   * @tparam T Initializer list data type.
   * @param quat_vals Quaternion values.
   */
  explicit Quaternion(const std::initializer_list<double> quat_vals)
  {
    // NOTE: Use an `assert` since the initializer list is non-static.
    assert(quat_vals.size() == 4);

    std::copy(quat_vals.begin(), quat_vals.end(), m_arr.begin());

    this->normalize();
  }

  /**
   * @brief Copy-construct quaternion.
   *
   * @param quat Other quaternion.
   */
  Quaternion(const Quaternion& quat)
    :m_arr{quat.m_arr}
  {}

  /**
   * @brief Copy-assign quaternion.
   *
   * @param quat Other quaternion.
   * @return Copied quaternion.
   */
  Quaternion& operator=(const Quaternion& quat)
  {
    m_arr = quat.m_arr;
    return *this;
  }

  /**
   * @brief Move-assign quaternion.
   *
   * @param quat Other quaternion.
   * @return Copied quaternion.
   */
  Quaternion& operator=(Quaternion&& quat)
  {
    m_arr.swap(quat.m_arr);
    return *this;
  }

  /**
   * @brief Assign quaternion values from an initializer list. Normalizes input.
   *
   * @param quat_vals Quaternion values.
   * @return New quaternion.
   */
  Quaternion& operator=(const std::initializer_list<double> quat_vals)
  {
    // NOTE: Use an `assert` since the initializer list is non-static.
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
  const double& operator()(const std::size_t idx) const
  {
    return m_arr.at(idx);
  }

  /**
   * @brief Return the conjugate (inverse) of the quaternion.
   *
   * @return Quaternion conjugate/inverse.
   */
  Quaternion conjugate() const
  {
    return Quaternion(m_arr.at(0), -m_arr.at(1), -m_arr.at(2), -m_arr.at(3));
  }

  /**
   * @brief Invert the quaternion.
   */
  Quaternion& invert()
  {
    m_arr.at(1) = -m_arr.at(1);
    m_arr.at(2) = -m_arr.at(2);
    m_arr.at(3) = -m_arr.at(3);

    return *this;
  }

  /**
   * @brief Negate (*= -1) the quaternion if the scalar component is negative to force a positive rotation.
   */
  void force_positive_rotation()
  {
    if (m_arr.at(0) < 0.0)
    {
      std::for_each(m_arr.begin(), m_arr.end(), [](double& val){val *= -1.0;});
    }
  }

  /**
   * @brief Normalize the quaternion to have a magnitude of 1.
   */
  void normalize()
  {
    // compute magnitude
    const double magn = std::sqrt(
      (m_arr.at(0) * m_arr.at(0)) +
      (m_arr.at(1) * m_arr.at(1)) +
      (m_arr.at(2) * m_arr.at(2)) +
      (m_arr.at(3) * m_arr.at(3))
    );

    // normalize each element
    std::for_each(m_arr.begin(), m_arr.end(), [magn](double& val){val /= magn;});
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
    os << std::setprecision(8) <<
      quat.m_arr.at(0) << ", " <<
      quat.m_arr.at(1) << ", " <<
      quat.m_arr.at(2) << ", " <<
      quat.m_arr.at(3);

    return os;
  }

private:
  std::array<double, 4> m_arr;  ///< Underlying array to store elements
};

}  // namespace MathUtils

#endif  // MATHUTILS_ATTITUDE_QUATERNION_H_
