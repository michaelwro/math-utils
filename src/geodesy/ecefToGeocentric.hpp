/**
 * @file ecefToGeocentric.hpp
 * @author michaelwro
 * @date 2025-04-06
 */

#pragma once

#include "geodesy/EGM2008Ellipsoid.hpp"
#include "geodesy/GeoCoord.hpp"
#include "geodesy/PlanetEllipsoidObject.hpp"
#include "math/Vector3.hpp"

namespace math {

/**
 * @brief Convert ECEF position into geocentric coordinates. Algorithm 12 from
 * "Fundamentals of Astrodynamics and Applications" (Vallado). Note that this is an
 * iterative algorithm, but has a max number of iterations.
 *
 * See also
 * https://github.com/CelesTrak/fundamentals-of-astrodynamics/blob/dbfe0d067606ec93a5957be2e6038205f85c7892/software/cpp/astrolib/AstroLib/AstroLib.cpp#L5766
 *
 * @param pos_ecef_m [m] ECEF position.
 * @param ellipsoid Planet ellipsoid. Default earth.
 * @return Geocentric coordinates.
 */
GeoCoord ecefToGeocentric(const Vector3& pos_ecef_m,
                          const PlanetEllipsoidObject& ellipsoid = EGM2008Ellipsoid {});
}  // namespace math
