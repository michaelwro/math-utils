/**
 * @file Quaternion.cpp
 * @author Michael Wrona
 * @date 2023-03-25
 */

#include "Attitude/Quaternion.h"

#include "float_equality.h"
#include "Internal/error_msg_helpers.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <stdexcept>
#include <type_traits>

namespace MathUtils {

Quaternion::Quaternion(const double qs, const double qx, const double qy, const double qz)
    :m_arr{qs, qx, qy, qz}
{
    this->normalize();
}

Quaternion::Quaternion(const std::initializer_list<double> quat_vals)
{
    // quaternions shall always have 4 elements.
    const std::size_t num_vals = quat_vals.size();

    if (num_vals != 4) {
        throw std::length_error(Internal::invalid_init_list_length_error_msg(num_vals, 4));
    }

    std::copy(quat_vals.begin(), quat_vals.end(), m_arr.begin());

    this->normalize();
}

Quaternion::Quaternion(Quaternion&& other) noexcept
    :m_arr{other.m_arr}
{}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
    if (&other == this) {
        return *this;
    }

    m_arr = other.m_arr;
    return *this;
}

Quaternion& Quaternion::operator=(Quaternion&& other) noexcept
{
    if (&other == this) {
        return *this;
    }

    m_arr.swap(other.m_arr);
    return *this;
}

Quaternion& Quaternion::operator=(const std::initializer_list<double> quat_vals)
{
    // quaternions shall always have 4 elements.
    const std::size_t num_vals = quat_vals.size();

    if (num_vals != 4) {
        throw std::length_error(Internal::invalid_init_list_length_error_msg(num_vals, 4));
    }

    std::copy(quat_vals.begin(), quat_vals.end(), m_arr.begin());
    this->normalize();

    return *this;
}

[[nodiscard]] const double& Quaternion::operator()(const std::size_t idx) const
{
    return m_arr.at(idx);
}

[[nodiscard]] const double& Quaternion::at(const std::size_t idx) const
{
    return m_arr.at(idx);
}

[[nodiscard]] Quaternion Quaternion::inverse() const
{
    return Quaternion(m_arr[0], -m_arr[1], -m_arr[2], -m_arr[3]);
}

void Quaternion::force_positive_rotation() noexcept
{
    if (m_arr[0] < 0.0) {
        m_arr[0] *= -1.0;
        m_arr[1] *= -1.0;
        m_arr[2] *= -1.0;
        m_arr[3] *= -1.0;
    }
}

void Quaternion::normalize()
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
     * Assert instead of throwing, since it would never make logical sense that a quaternion would
     * have zero magnitude.
     */
    assert(!float_equality(magn, 0.0));

    m_arr[0] /= magn;
    m_arr[1] /= magn;
    m_arr[2] /= magn;
    m_arr[3] /= magn;
}

[[nodiscard]] Vector<3> Quaternion::eigen_axis() const
{
    // rotation angle divided by 2
    const double angle_div_two = std::acos(m_arr[0]);
    const double sin_angle_div_two = std::sin(angle_div_two);

    // NOTE: Could be div-by-zero for small or zero rotation angles.
    // Could maybe return zero vector?
    return Vector<3> {
        m_arr[1] / sin_angle_div_two,
        m_arr[2] / sin_angle_div_two,
        m_arr[3] / sin_angle_div_two
    };
}

[[nodiscard]] double Quaternion::angle() const
{
    return 2.0 * std::acos(m_arr[0]);
}

std::ostream& operator<<(std::ostream& os, const Quaternion& quat)
{
    os << quat.m_arr[0] << ", "
        << quat.m_arr[1] << ", "
        << quat.m_arr[2] << ", "
        << quat.m_arr[3];

    return os;
}

}  // namespace MathUtils
