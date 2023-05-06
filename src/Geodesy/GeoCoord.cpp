/**
 * @file GeoCoord.cpp
 * @author Michael Wrona
 * @date 2023-03-27
 */

#include "Geodesy/GeoCoord.h"

namespace MathUtils {

GeoCoord::GeoCoord(const double latitude_rad,
    const double longitude_rad,
    const double altitude_m
)
    :m_lat_rad(latitude_rad),
    m_lon_rad(longitude_rad),
    m_alt_m(altitude_m)
{}

std::ostream& operator<<(std::ostream& os, const GeoCoord& coord)
{
    os << coord.latitude() << ", "
        << coord.longitude() << ", "
        << coord.altitude();

    return os;
}

}  // namespace MathUtils
