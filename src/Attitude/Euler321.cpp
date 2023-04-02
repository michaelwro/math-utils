/**
 * @file Euler321.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "Attitude/Euler321.h"

#include <utility>

namespace MathUtils {

Euler321::Euler321()
    :m_yaw_rad{},
    m_pitch_rad{},
    m_roll_rad{}
{}


Euler321::Euler321(const double yaw_rad, const double pitch_rad, const double roll_rad)
    :m_yaw_rad{yaw_rad},
    m_pitch_rad{pitch_rad},
    m_roll_rad{roll_rad}
{}


Euler321::Euler321(const Euler321& other)
    :m_yaw_rad{other.m_yaw_rad},
    m_pitch_rad{other.m_pitch_rad},
    m_roll_rad{other.m_roll_rad}
{}


Euler321::Euler321(Euler321&& other) noexcept
    :m_yaw_rad{std::exchange(other.m_yaw_rad, 0.0)},
    m_pitch_rad{std::exchange(other.m_pitch_rad, 0.0)},
    m_roll_rad{std::exchange(other.m_roll_rad, 0.0)}
{}


Euler321& Euler321::operator=(const Euler321& other)
{
    if (&other == this) {
        return *this;
    }

    m_yaw_rad = other.m_yaw_rad;
    m_pitch_rad = other.m_pitch_rad;
    m_roll_rad = other.m_roll_rad;
    return *this;
}


Euler321& Euler321::operator=(Euler321&& other) noexcept
{
    if (&other == this) {
        return *this;
    }

    m_yaw_rad = std::exchange(other.m_yaw_rad, 0.0);
    m_pitch_rad = std::exchange(other.m_pitch_rad, 0.0);
    m_roll_rad = std::exchange(other.m_roll_rad, 0.0);
    return *this;
}


double& Euler321::yaw() noexcept
{
    return m_yaw_rad;
}


const double& Euler321::yaw() const noexcept
{
    return m_yaw_rad;
}


double& Euler321::pitch() noexcept
{
    return m_pitch_rad;
}


const double& Euler321::pitch() const noexcept
{
    return m_pitch_rad;
}


double& Euler321::roll() noexcept
{
    return m_roll_rad;
}


const double& Euler321::roll() const noexcept
{
    return m_roll_rad;
}


std::ostream& operator<<(std::ostream& os, const Euler321& angles)
{
    os << angles.m_yaw_rad << ", "
        << angles.m_pitch_rad << ", "
        << angles.m_roll_rad;

    return os;
}

}  // namespace MathUtils
