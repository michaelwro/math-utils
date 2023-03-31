/**
 * @file lla_to_ecef.cpp
 * @author Michael Wrona
 * @date 2023-03-29
 */

#include "Geodesy/lla_to_ecef.h"

#include "constants.h"

#include <cmath>

namespace MathUtils {

Vector<3> lla_to_ecef(const GeoCoord& lla)
{
    // pre-compute terms
    const double sin_lat_rad = std::sin(lla.latitude());
    const double cos_lat_rad = std::cos(lla.latitude());

    // "radius of curvature in the meridian"
    const double c_term = Constants::WGS84_A_M /
        std::sqrt(1.0 - (Constants::WGS84_ECC2 * sin_lat_rad * sin_lat_rad));

    const double s_term = c_term * (1.0 - Constants::WGS84_ECC2);

    return Vector<3> {
        (c_term + lla.altitude()) * cos_lat_rad * std::cos(lla.longitude()),
        (c_term + lla.altitude()) * cos_lat_rad * std::sin(lla.longitude()),
        (s_term + lla.altitude()) * sin_lat_rad
    };
}

}  // namespace MathUtils
