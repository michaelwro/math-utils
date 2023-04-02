/**
 * @file euler_to_dcm.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "Attitude/euler_to_dcm.h"

#include <cmath>

namespace MathUtils {

Matrix<3,3> euler_to_dcm(const Euler321& euler)
{
    const double syaw = std::sin(euler.yaw());
    const double cyaw = std::cos(euler.yaw());

    const double spitch = std::sin(euler.pitch());
    const double cpitch = std::cos(euler.pitch());

    const double sroll = std::sin(euler.roll());
    const double croll = std::cos(euler.roll());

    return Matrix<3,3> {
        {cpitch * cyaw, cpitch * syaw, -spitch},
        {(sroll * spitch * cyaw) - (croll * syaw), (sroll * spitch * syaw) + (croll * cyaw), sroll * cpitch},
        {(croll * spitch * cyaw) + (sroll * syaw), (croll * spitch * syaw) - (sroll * cyaw), croll * cpitch}
    };
}

}  // namespace MathUtils
