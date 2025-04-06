/**
 * @file Quaternion.cpp
 * @author michaelwro
 * @date 2025-03-30
 */

#include "math/Quaternion.hpp"

#include <cassert>
#include <cmath>

namespace math {

Quaternion::Quaternion(const double qs, const double qx, const double qy, const double qz)
    : m_arr {qs, qx, qy, qz} {
    this->normalize();
}

const double& Quaternion::s() const noexcept {
    return m_arr[0];
}

const double& Quaternion::w() const noexcept {
    return s();
}

const double& Quaternion::x() const noexcept {
    return m_arr[1];
}

const double& Quaternion::y() const noexcept {
    return m_arr[2];
}

const double& Quaternion::z() const noexcept {
    return m_arr[3];
}

Vector<3> Quaternion::getVectorComponent() const {
    return Vector<3>::assign(x(), y(), z());
}

const double& Quaternion::operator()(const std::size_t idx) const noexcept {
    assert(idx < size());
    return m_arr[idx];
}

Quaternion Quaternion::getConjugate() const {
    return {s(), -x(), -y(), -z()};
}

void Quaternion::forcePositiveRotation() {
    if (s() < 0.0) {
        negateArray(m_arr);
    }
}

void Quaternion::normalize() {
    // magnitude-squared of the elements
    const double magn_sq = (s() * s()) + (x() * x()) + (y() * y()) + (z() * z());

    // 1 - q^2 factor
    const double one_minus_magn_sq = 1.0 - magn_sq;

    static_assert(m_normalization_threshold > 0.0,
                  "Invalid quaternion normalization threshold");

    double norm_scale_factor {};

    if ((one_minus_magn_sq > -m_normalization_threshold) and
        (one_minus_magn_sq < m_normalization_threshold)) {
        // within "small" threshold, use approximate method
        norm_scale_factor = 2.0 / (1.0 + magn_sq);
    }
    else {
        // otherwise, calculate norm as usual
        norm_scale_factor = 1.0 / std::sqrt(magn_sq);
    }

    // scale quaternion elements
    std::for_each(m_arr.begin(), m_arr.end(),
                  [norm_scale_factor](auto& val) { val *= norm_scale_factor; });
}

std::tuple<double, Vector<3>> Quaternion::eigenAxisAngle() const {
    // force positive rotation
    Quaternion quat(*this);
    quat.forcePositiveRotation();

    // compute magnitude of the quaternion vector part
    Vector<3> quat_vector = quat.getVectorComponent();

    // magnitude of the quaternion vector elements is sin(a / 2)
    double sin_angle_div2 = quat_vector.magnitude();

    // ill-defined eigen vector if the eigen angle is zero
    if (not std::isnormal(sin_angle_div2)) {
        // arbitrarily use X-vector
        return {0.0, Vector<3>::assign(1.0, 0.0, 0.0)};
    }

    // compute eigen axis
    Vector<3> eigen_axis = quat_vector / sin_angle_div2;

    double eigen_angle_rad {};

    if (sin_angle_div2 < quat.s()) {
        eigen_angle_rad = 2.0 * std::asin(sin_angle_div2);
    }
    else {
        eigen_angle_rad = 2.0 * std::acos(quat.s());
    }

    return {eigen_angle_rad, eigen_axis};
}

Vector<3> Quaternion::eigenAxis() const {
    [[maybe_unused]] auto [_, axis] = eigenAxisAngle();
    return axis;
}

double Quaternion::eigenAngle() const {
    [[maybe_unused]] auto [angle, _] = eigenAxisAngle();
    return angle;
}

Quaternion operator*(const Quaternion& q2, const Quaternion& q1) {
    // get the scalar and vector components
    const double q2s = q2.s();
    const double q1s = q1.s();

    const auto q2v = q2.getVectorComponent();
    const auto q1v = q1.getVectorComponent();

    // calculate scalar component
    const double scalar_part = (q1s * q2s) - dot(q2v, q1v);

    // calculate vector component
    const Vector<3> vector_component = (q1s * q2v) + (q2s * q1v) + cross(q2v, q1v);

    // normalize and return result
    return {scalar_part, vector_component(0), vector_component(1), vector_component(2)};
}

std::ostream& operator<<(std::ostream& os, const Quaternion& quat) {
    os << quat.w() << "," << quat.x() << "," << quat.y() << "," << quat.z();
    return os;
}

}  // namespace math
