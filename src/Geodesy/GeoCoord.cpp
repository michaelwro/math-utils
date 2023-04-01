/**
 * @file GeoCoord.cpp
 * @author Michael Wrona
 * @date 2023-03-27
 */

#include "Geodesy/GeoCoord.h"

#include <utility>

namespace MathUtils {

GeoCoord::GeoCoord()
    :m_lat_rad{},
    m_lon_rad{},
    m_alt_m{}
{}


GeoCoord::GeoCoord(const double latitude_rad, const double longitude_rad, const double altitude_m)
    :m_lat_rad{latitude_rad},
    m_lon_rad{longitude_rad},
    m_alt_m{altitude_m}
{}


GeoCoord::GeoCoord(const GeoCoord& other)
    :m_lat_rad{other.m_lat_rad},
    m_lon_rad{other.m_lon_rad},
    m_alt_m{other.m_alt_m}
{}


GeoCoord::GeoCoord(GeoCoord&& other) noexcept
    :m_lat_rad{std::exchange(other.m_lat_rad, 0.0)},
    m_lon_rad{std::exchange(other.m_lon_rad, 0.0)},
    m_alt_m{std::exchange(other.m_alt_m, 0.0)}
{}


GeoCoord& GeoCoord::operator=(const GeoCoord& other)
{
    if (&other == this) {
        return *this;
    }

    m_lat_rad = other.m_lat_rad;
    m_lon_rad = other.m_lon_rad;
    m_alt_m = other.m_alt_m;
    return *this;
}


GeoCoord& GeoCoord::operator=(GeoCoord&& other) noexcept
{
    if (&other == this) {
        return *this;
    }

    m_lat_rad = std::exchange(other.m_lat_rad, 0.0);
    m_lon_rad = std::exchange(other.m_lon_rad, 0.0);
    m_alt_m = std::exchange(other.m_alt_m, 0.0);
    return *this;
}


double& GeoCoord::latitude() noexcept
{
    return m_lat_rad;
}


const double& GeoCoord::latitude() const noexcept
{
    return m_lat_rad;
}


double& GeoCoord::longitude() noexcept
{
    return m_lon_rad;
}


const double& GeoCoord::longitude() const noexcept
{
    return m_lon_rad;
}


double& GeoCoord::altitude() noexcept
{
    return m_alt_m;
}


const double& GeoCoord::altitude() const noexcept
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
