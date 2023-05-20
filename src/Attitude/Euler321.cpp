/**
 * @file Euler321.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "Attitude/Euler321.h"

#include <utility>

namespace MathUtils {

std::ostream& operator<<(std::ostream& os, const Euler321& angles)
{
    os << angles.yaw() << ", "
        << angles.pitch() << ", "
        << angles.roll();

    return os;
}

}  // namespace MathUtils
