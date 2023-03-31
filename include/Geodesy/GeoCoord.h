/**
 * @file GeoCoord.h
 * @author Michael Wrona
 * @date 2023-03-27
 */

#ifndef MATHUTILS_GEODETIC_COORDS_H_
#define MATHUTILS_GEODETIC_COORDS_H_

#include <initializer_list>
#include <utility>

namespace MathUtils {

/**
 * @brief Geodetic coordinate (latitude, longitude, altitude).
 *
 * @details Latitude is in [rad], longitude is [rad], and altitude is MSL in [m].
 */
class GeoCoord {
public:
    /**
     * @brief Create a GeoCoord.
     */
    GeoCoord();

    /**
     * @brief Create a GeoCoord.
     *
     * @param latitude_rad Latitude in [rad].
     * @param longitude_rad Longitude in [rad].
     * @param altitude_m Altitude in [m].
     */
    GeoCoord(const double latitude_rad, const double longitude_rad, const double altitude_m);

    /**
     * @brief Create a GeoCoord.
     *
     * @param lla Latitude [rad], longitude [rad], altitude [m].
     */
    explicit GeoCoord(const std::initializer_list<double> lla);

    /**
     * @brief Copy construct GeoCoord.
     *
     * @param other Other GoeCoord.
     */
    GeoCoord(const GeoCoord& other);

    /**
     * @brief Move construct GeoCoord
     *
     * @param other Other GeoCoord.
     */
    GeoCoord(GeoCoord&& other) noexcept;

    /**
     * @brief Assing GeoCoord values from an initializer list.
     *
     * @param lla New latitude [rad]. longitude [rad], altitude [m].
     * @return GeoCoord.
     */
    GeoCoord& operator=(const std::initializer_list<double> lla);

    /**
     * @brief Copy assign GeoCoord.
     *
     * @param other Other GeoCoord.
     * @return GeoCoord.
     */
    GeoCoord& operator=(const GeoCoord& other);

    /**
     * @brief Move assign GeoCoord.
     *
     * @param other Other GeoCoord.
     * @return GeoCoord.
     */
    GeoCoord& operator=(GeoCoord&& other) noexcept;

    /**
     * @brief Access latitude.
     *
     * @return Latitude [rad].
     */
    double& latitude() noexcept
    {
        return m_lat_rad;
    }

    /**
     * @brief Get latitude.
     *
     * @return Latitude [rad].
     */
    const double& latitude() const noexcept
    {
        return m_lat_rad;
    }

    /**
     * @brief Access longitude.
     *
     * @return Longitude [rad].
     */
    double& longitude() noexcept
    {
        return m_lon_rad;
    }

    /**
     * @brief Get longitude.
     *
     * @return Longitude [rad].
     */
    const double& longitude() const noexcept
    {
        return m_lon_rad;
    }

    /**
     * @brief Access altitude.
     *
     * @return Altitude [m].
     */
    double& altitude() noexcept
    {
        return m_alt_m;
    }

    /**
     * @brief Access altitude.
     *
     * @return Altitude [m].
     */
    const double& altitude() const noexcept
    {
        return m_alt_m;
    }

protected:
private:
    double m_lat_rad;  ///< Latitude in [rad], [-90, 90]
    double m_lon_rad;  ///< Longitude in [rad], [-180, 180].
    double m_alt_m;  ///< Altitude in [m].
};

}    // namespace MathUtils

#endif    // MATHUTILS_GEODETIC_COORDS_H_
