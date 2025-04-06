/**
 * @file GeoCoord.h
 * @author Michael Wrona
 * @date 2023-03-27
 */

#pragma once

#include <ostream>

// #include "Internal/error_msg_helpers.h"

#include "GeoType.hpp"
#include "geodesy/GeoType.hpp"

namespace math {

/**
 * @brief Geodetic coordinate (latitude, longitude, altitude).
 *
 * @details Latitude is in [rad] (+/- 90 deg), longitude is [rad] (+/- 180 deg), and
 * altitude is ellipsoidal altitude in [m].
 */
class GeoCoord {
public:
    GeoCoord() = default;
    ~GeoCoord() = default;

    /**
     * @brief Create a GeoCoord.
     *
     * @param latitude_rad Latitude in [rad] (+/- 90 deg).
     * @param longitude_rad Longitude in [rad] (+/- 180 deg).
     * @param altitude_m Altitude in [m].
     * @param coord_type Coordinate type. Default geodetic.
     */
    GeoCoord(const double latitude_rad, const double longitude_rad,
             const double altitude_m, GeoType coord_type = GeoType::geodetic);

    /**
     * @brief Get latitude.
     *
     * @return [rad] Latitude.
     */
    [[nodiscard]] const double& latitude() const noexcept;

    /**
     * @brief Get longitude.
     *
     * @return [rad] Longitude.
     */
    [[nodiscard]] const double& longitude() const noexcept;

    /**
     * @brief Get altitude.
     *
     * @return [m] Altitude.
     */
    [[nodiscard]] const double& altitude() const noexcept;

    /**
     * @brief Get coordinate type.
     *
     * @return Coordinate type.
     */
    [[nodiscard]] GeoType type() const noexcept;

protected:
private:
    double m_lat_rad {0};                ///< Latitude in [rad].
    double m_lon_rad {0};                ///< Longitude in [rad].
    double m_alt_m {0};                  ///< Altitude in [m].
    GeoType m_type {GeoType::geodetic};  ///< Coordinate type.
};

/**
 * @brief Print a GeoCoord to a stream. Comma-separates values. No newline at
 * the end.
 *
 * @param os Output stream.
 * @param coord GeoCoord to print.
 * @return Output stream with GeoCoord.
 */
std::ostream& operator<<(std::ostream& os, const GeoCoord& coord);

}  // namespace math
