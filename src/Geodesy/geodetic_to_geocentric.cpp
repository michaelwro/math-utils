/**
 * @file geodetic_to_geocentric.cpp
 * @author Michael Wrona
 * @date 2023-04-28
 */

#include "Geodesy/geodetic_to_geocentric.h"

#include "constants.h"

#include <cmath>

namespace MathUtils {

using PairType = std::pair<double, double>;

PairType geodetic_to_geocentric(const double lat_gd_rad, const double alt_m)
{
    const double sin_lat_gc = std::sin(lat_gd_rad);
    const double cos_lat_gc = std::cos(lat_gd_rad);

    const double N = Constants::WGS84_A_M /
        std::sqrt(1.0 - (Constants::WGS84_ECC2 * sin_lat_gc * sin_lat_gc));

    // distance from the polar axis
    const double rho = (N + alt_m) * cos_lat_gc;

    // distance from the equatorial axis
    const double z = (alt_m + (N * (1 - Constants::WGS84_ECC2))) * sin_lat_gc;

    // geocentric lat, geocentric radius
    return std::make_pair(std::atan2(z, rho), std::sqrt((z*z) + (rho*rho)));
}

PairType geodetic_to_geocentric(const GeoCoord& lla)
{
    return geodetic_to_geocentric(lla.latitude(), lla.altitude());
}

}  // namespace MathUtils
