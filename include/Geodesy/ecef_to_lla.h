/**
 * @file ecef_to_lla.h
 * @author Michael Wrona
 * @date 2023-04-04
 */

#pragma once

#include "Geodesy/GeoCoord.h"
#include "LinAlg/Vector.h"

namespace MathUtils {

/**
 * @brief Convert earth-centered, earth-fixed position to geodetic latitude, longitude, and
 * altitude.
 *
 * @details Method from https://danceswithcode.net/engineeringnotes/geodetic_to_ecef/geodetic_to_ecef.html
 *
 * @param pos_ecef_m ECEF position in [m].
 * @return Geodetic LLA in [rad] and [m].
 *
 * @see MathUtils::Constants
 */
GeoCoord ecef_to_lla(const Vector<3>& pos_ecef_m);

}  // namespace MathUtils
