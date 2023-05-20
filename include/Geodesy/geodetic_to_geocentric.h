/**
 * @file geodetic_to_geocentric.h
 * @author Michael Wrona
 * @date 2023-04-28
 */

#pragma once

#include "Geodesy/GeoCoord.h"

#include <utility>

namespace MathUtils {

/**
 * @brief Convert WGS84 geodetic latitude and altitude to geocentric latitude and radius.
 *
 * @param lat_gd_rad WGS84 geodetic latitude in [rad].
 * @param alt_m WGS84 altitude in [m].
 * @return {geocentric latitude [rad]}, {geocentric radius in [m]}.
 *
 * @ref https://www.mathworks.com/help/aeroblks/geodetictogeocentriclatitude.html
 */
std::pair<double, double> geodetic_to_geocentric(const double lat_gd_rad, const double alt_m);

/**
 * @brief Convert WGS84 geodetic latitude, longitude, and altitude to geocentric latitude and
 * radius.
 *
 * @details Uses `geodetic_to_geocentric(double, double)`.
 *
 * @param lla_gd WGS84 geodetic LLA in [rad, rad, m].
 * @return {geocentric latitude [rad]}, {geocentric radius in [m]}.
 *
 * @ref https://www.mathworks.com/help/aeroblks/geodetictogeocentriclatitude.html
 */
std::pair<double, double> geodetic_to_geocentric(const GeoCoord& lla);


}  // namespace MathUtils
