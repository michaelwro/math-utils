/**
 * @file lla_to_ecef.h
 * @author Michael Wrona
 * @date 2023-03-29
 */

#ifndef MATHUTILS_LLA_TO_ECEF_H_
#define MATHUTILS_LLA_TO_ECEF_H_

#include "Geodesy/GeoCoord.h"
#include "LinAlg/Vector.h"

namespace MathUtils {

/**
 * @brief Convert geodetic latitude, longitude, and altitude to ECEF position.
 *
 * @details Equation 3.14 from "Fundamentals of Astrodynamics and Applications" (Vallado).
 * Uses WGS84 semi-major axis.
 *
 * @param lla Latitude [rad], longitude [rad], altitude [m].
 * @return ECEF position [m].
 */
Vector<3> lla_to_ecef(const GeoCoord& lla);

}  // namespace MathUtils

#endif  // MATHUTILS_LLA_TO_ECEF_H_
