/**
 * @file GeoCoord.cpp
 * @author michaelwro
 * @date 2025-03-23
 */

#include "geodesy/GeoCoord.hpp"

namespace math {

const double& GeoCoord::latitude() const noexcept {
    return m_lat_rad;
}

const double& GeoCoord::longitude() const noexcept {
    return m_lon_rad;
}

const double& GeoCoord::altitude() const noexcept {
    return m_alt_m;
}

GeoType GeoCoord::type() const noexcept {
    return m_type;
}

std::ostream& operator<<(std::ostream& os, const GeoCoord& coord) {
    os << coord.latitude() << "," << coord.longitude() << "," << coord.altitude() << ","
       << coord.type();

    return os;
}

}  // namespace math