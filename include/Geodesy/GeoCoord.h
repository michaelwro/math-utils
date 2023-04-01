/**
 * @file GeoCoord.h
 * @author Michael Wrona
 * @date 2023-03-27
 */

#ifndef MATHUTILS_GEODETIC_COORDS_H_
#define MATHUTILS_GEODETIC_COORDS_H_

#include "Internal/error_msg_helpers.h"

#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <type_traits>

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
     * @tparam T Input type.
     * @param lla Latitude [rad], longitude [rad], altitude [m].
     *
     * @exception std::length_error Did not pass three-value list.
     */
    template<typename T>
    explicit GeoCoord(const std::initializer_list<T> lla)
    {
        static_assert(std::is_fundamental<T>::value, "Fundamental types only.");
        const std::size_t input_size = lla.size();

        if (input_size != 3) {
            throw std::length_error(Internal::invalid_init_list_length_error_msg(input_size, 3));
        }

        m_lat_rad = *(lla.begin());
        m_lon_rad = *(lla.begin() + 1);
        m_alt_m = *(lla.begin() + 2);
    }

    /**
     * @brief Copy construct GeoCoord.
     *
     * @param other Other GoeCoord.
     */
    GeoCoord(const GeoCoord& other);

    /**
     * @brief Move construct GeoCoord.
     *
     * @param other Other GeoCoord.
     */
    GeoCoord(GeoCoord&& other) noexcept;

    /**
     * @brief Assing GeoCoord values from an initializer list.
     *
     * @tparam T Input type.
     * @param lla New latitude [rad]. longitude [rad], altitude [m].
     * @return GeoCoord.
     *
     * @exception std::length_error Did not pass three-value list.
     */
    template<typename T>
    GeoCoord& operator=(const std::initializer_list<T> lla)
    {
        static_assert(std::is_fundamental<T>::value, "Fundamental types only.");
        const std::size_t input_size = lla.size();

        if (input_size != 3) {
            throw std::length_error(Internal::invalid_init_list_length_error_msg(input_size, 3));
        }

        m_lat_rad = *(lla.begin());
        m_lon_rad = *(lla.begin() + 1);
        m_alt_m = *(lla.begin() + 2);

        return *this;
    }

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
    double& latitude() noexcept;

    /**
     * @brief Get latitude.
     *
     * @return Latitude [rad].
     */
    const double& latitude() const noexcept;

    /**
     * @brief Access longitude.
     *
     * @return Longitude [rad].
     */
    double& longitude() noexcept;

    /**
     * @brief Get longitude.
     *
     * @return Longitude [rad].
     */
    const double& longitude() const noexcept;

    /**
     * @brief Access altitude.
     *
     * @return Altitude [m].
     */
    double& altitude() noexcept;

    /**
     * @brief Access altitude.
     *
     * @return Altitude [m].
     */
    const double& altitude() const noexcept;

    /**
     * @brief Print a GeoCoord to a stream. Comma-separates values. No newline at the end.
     *
     * @param os Output stream.
     * @param coord GeoCoord to print.
     * @return Output stream with GeoCoord.
     */
    friend std::ostream& operator<<(std::ostream& os, const GeoCoord& coord);

protected:
private:
    double m_lat_rad;  ///< Latitude in [rad].
    double m_lon_rad;  ///< Longitude in [rad].
    double m_alt_m;  ///< Altitude in [m].
};

}    // namespace MathUtils

#endif    // MATHUTILS_GEODETIC_COORDS_H_
