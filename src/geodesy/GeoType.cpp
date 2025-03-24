/**
 * @file GeoType.cpp
 * @author michaelwro
 * @date 2025-03-23
 */

#include "geodesy/GeoType.hpp"

namespace math {

std::ostream& operator<<(std::ostream& os, const GeoType& type) {
    os << static_cast<std::uint32_t>(type);
    return os;
}

}  // namespace math