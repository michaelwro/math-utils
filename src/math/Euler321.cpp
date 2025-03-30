/**
 * @file Euler321.cpp
 * @author michaelwro
 * @date 2025-03-30
 */

#include "math/Euler321.hpp"

namespace math {

Euler321::Euler321(const double yaw_rad, const double pitch_rad, const double roll_rad)
    : m_yaw_rad(yaw_rad), m_pitch_rad(pitch_rad), m_roll_rad(roll_rad) {
}

double& Euler321::yaw() noexcept {
    return m_yaw_rad;
}

const double& Euler321::yaw() const noexcept {
    return m_yaw_rad;
}

double& Euler321::pitch() noexcept {
    return m_pitch_rad;
}

const double& Euler321::pitch() const noexcept {
    return m_pitch_rad;
}

double& Euler321::roll() noexcept {
    return m_roll_rad;
}

const double& Euler321::roll() const noexcept {
    return m_roll_rad;
}

std::ostream& operator<<(std::ostream& os, const Euler321& angles) {
    os << angles.yaw() << "," << angles.pitch() << "," << angles.roll();
    return os;
}

}  // namespace math