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
    :m_lat_rad{latitude_rad},
    m_lon_rad{longitude_rad},
    m_alt_m{altitude_m}
{}

[[nodiscard]] double& GeoCoord::latitude() noexcept
{
    return m_lat_rad;
}

[[nodiscard]] const double& GeoCoord::latitude() const noexcept
{
    return m_lat_rad;
}

[[nodiscard]] double& GeoCoord::longitude() noexcept
{
    return m_lon_rad;
}

[[nodiscard]] const double& GeoCoord::longitude() const noexcept
{
    return m_lon_rad;
}

[[nodiscard]] double& GeoCoord::altitude() noexcept
{
    return m_alt_m;
}

[[nodiscard]] const double& GeoCoord::altitude() const noexcept
{
    return m_alt_m;
}

std::ostream& operator<<(std::ostream& os, const GeoCoord& coord)
{
    os << coord.m_lat_rad << ", "
        << coord.m_lon_rad << ", "
        << coord.m_alt_m;

    return os;
}

}  // namespace MathUtils
