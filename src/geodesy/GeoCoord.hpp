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
 * @details Latitude is in [rad], longitude is [rad], and altitude is MSL in
 * [m].
 */
class GeoCoord {
public:
    GeoCoord() = default;
    ~GeoCoord() = default;

    /**
     * @brief Create a GeoCoord.
     *
     * @param latitude_rad Latitude in [rad].
     * @param longitude_rad Longitude in [rad].
     * @param altitude_m Altitude in [m].
     * @param coord_type Coordinate type. Default geodetic.
     */
    GeoCoord(const double latitude_rad, const double longitude_rad,
             const double altitude_m, GeoType coord_type = GeoType::geodetic)
        : m_lat_rad {latitude_rad},
          m_lon_rad {longitude_rad},
          m_alt_m {altitude_m},
          m_type {coord_type} {
    }

    // /**
    //  * @brief Create a GeoCoord.
    //  *
    //  * @tparam T Input type.
    //  * @param lla Latitude [rad], longitude [rad], altitude [m].
    //  *
    //  * @exception std::length_error Did not pass three-value list.
    //  */
    // template <typename T>
    // requires valid_geocoord_element<T> GeoCoord(
    //     const std::initializer_list<T> lla)  //  cppcheck-suppress
    //     noExplicitConstructor
    // {
    //   const std::size_t input_size = lla.size();

    //   if (input_size != 3) {
    //     throw std::length_error(
    //         internal::invalid_init_list_length_error_msg(input_size, 3));
    //   }

    //   m_lat_rad = *(lla.begin());
    //   m_lon_rad = *(lla.begin() + 1);
    //   m_alt_m = *(lla.begin() + 2);
    // }

    GeoCoord(const GeoCoord& other) = default;

    GeoCoord(GeoCoord&& other) = default;

    // /**
    //  * @brief Assing GeoCoord values from an initializer list.
    //  *
    //  * @tparam T Input type.
    //  * @param lla New latitude [rad]. longitude [rad], altitude [m].
    //  * @return GeoCoord.
    //  *
    //  * @exception std::length_error Did not pass three-value list.
    //  */
    // template <typename T>
    // requires valid_geocoord_element<T> GeoCoord& operator=(
    //     const std::initializer_list<T> lla) {
    //   const std::size_t input_size = lla.size();

    //   if (input_size != 3) {
    //     throw std::length_error(
    //         internal::invalid_init_list_length_error_msg(input_size, 3));
    //   }

    //   m_lat_rad = *(lla.begin());
    //   m_lon_rad = *(lla.begin() + 1);
    //   m_alt_m = *(lla.begin() + 2);

    //   return *this;
    // }

    // GeoCoord& operator=(const GeoCoord& other) = default;

    // GeoCoord& operator=(GeoCoord&& other) = default;

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
