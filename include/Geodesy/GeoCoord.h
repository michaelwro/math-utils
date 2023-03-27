/**
 * @file GeoCoord.h
 * @author Michael Wrona
 * @date 2023-03-27
 */

#ifndef MATHUTILS_GEODETIC_COORDS_H_
#define MATHUTILS_GEODETIC_COORDS_H_

#include <initializer_list>

namespace MathUtils {

/**
 * @brief Geodetic coordinate (latitude, longitude, altitude).
 *
 * @details Uses WGS84 geoid. Latitude is geodetic latitude [-90, 90] in [rad], longitude is [-180, 180] in [rad], and
 * altitude is MSL in [m].
 */
class GeoCoord
{
public:
  /**
   * @brief Create a GeoCoord.
   */
  GeoCoord();
protected:
private:
  double m_lat;  ///< Latitude in [rad], [-90, 90]
  double m_lon;  ///< Longitude in [rad], [-180, 180].
  double m_alt;  ///< Altitude in [m].

};

}  // namespace MathUtils

#endif  // MATHUTILS_GEODETIC_COORDS_H_
