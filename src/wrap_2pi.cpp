/**
 * @file wrap_2pi.cpp
 * @author Michael Wrona
 * @date 2023-03-29
 */

#include "wrap_2pi.h"

namespace MathUtils {

float wrap_2pi(float angle_rad)
{
    angle_rad = std::fmod(angle_rad, static_cast<float>(Constants::TWO_PI));

    if (angle_rad < 0.0f) {
        angle_rad += static_cast<float>(Constants::TWO_PI);
    }

    return angle_rad;
}


double wrap_2pi(double angle_rad)
{
    angle_rad = std::fmod(angle_rad, Constants::TWO_PI);

    if (angle_rad < 0.0) {
        angle_rad += Constants::TWO_PI;
    }

    return angle_rad;
}

}  // namespace MathUtils
