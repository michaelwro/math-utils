/**
 * @file euler321_to_dcm.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "Attitude/euler321_to_dcm.h"

#include <cmath>

namespace MathUtils {

Matrix<3,3> euler321_to_dcm(const double yaw_rad, const double pitch_rad, const double roll_rad)
{
    const double syaw = std::sin(yaw_rad);
    const double cyaw = std::cos(yaw_rad);

    const double spitch = std::sin(pitch_rad);
    const double cpitch = std::cos(pitch_rad);

    const double sroll = std::sin(roll_rad);
    const double croll = std::cos(roll_rad);

    return Matrix<3,3> {
        {cpitch * cyaw, cpitch * syaw, -spitch},
        {(sroll * spitch * cyaw) - (croll * syaw), (sroll * spitch * syaw) + (croll * cyaw), sroll * cpitch},
        {(croll * spitch * cyaw) + (sroll * syaw), (croll * spitch * syaw) - (sroll * cyaw), croll * cpitch}
    };
}

}  // namespace MathUtils
