/**
 * @file Euler321.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "Attitude/Euler321.h"

#include <utility>

namespace MathUtils {

Euler321::Euler321(const double yaw_rad, const double pitch_rad, const double roll_rad)
    :m_yaw_rad(yaw_rad),
    m_pitch_rad(pitch_rad),
    m_roll_rad(roll_rad)
{}

std::ostream& operator<<(std::ostream& os, const Euler321& angles)
{
    os << angles.yaw() << ", "
        << angles.pitch() << ", "
        << angles.roll();

    return os;
}

}  // namespace MathUtils
