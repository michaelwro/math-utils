/**
 * @file ecefToGeocentric.cpp
 * @author michaelwro
 * @date 2025-04-06
 */

#include "geodesy/ecefToGeocentric.hpp"

#include <cassert>

#include "geodesy/GeoType.hpp"
#include "geodesy/ecefToGeodetic.hpp"
#include "math/safeArcsin.hpp"

namespace math {

GeoCoord ecefToGeocentric(const Vector3& pos_ecef_m,
                          const PlanetEllipsoidObject& ellipsoid) {
    // convert to geodetic
    GeoCoord geodetic_coord = ecefToGeodetic(pos_ecef_m, ellipsoid);
    assert(geodetic_coord.type() == GeoType::geodetic);

    // convert latitude to geocentric
    const double lat_geocentric = safeArcsin(pos_ecef_m(2) / pos_ecef_m.magnitude());

    return {lat_geocentric, geodetic_coord.longitude(), geodetic_coord.altitude(),
            GeoType::geocentric};
}

}  // namespace math
