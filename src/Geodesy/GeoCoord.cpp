/**
 * @file GeoCoord.cpp
 * @author Michael Wrona
 * @date 2023-03-27
 */

#include "Geodesy/GeoCoord.h"

namespace MathUtils {

std::ostream& operator<<(std::ostream& os, const GeoCoord& coord)
{
    os << coord.latitude() << ", "
        << coord.longitude() << ", "
        << coord.altitude();

    return os;
}

}  // namespace MathUtils
