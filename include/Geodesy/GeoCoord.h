/**
 * @file GeoCoord.h
 * @author Michael Wrona
 * @date 2023-03-27
 */

#pragma once

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
    GeoCoord() = default;

    /**
     * @brief Destroy the GeoCoord.
     */
    ~GeoCoord() = default;

    /**
     * @brief Create a GeoCoord.
     *
     * @param latitude_rad Latitude in [rad].
     * @param longitude_rad Longitude in [rad].
     * @param altitude_m Altitude in [m].
     */
    GeoCoord(const double latitude_rad,
        const double longitude_rad,
        const double altitude_m);

    /**
     * @brief Create a GeoCoord.
     *
     * @tparam T Input type.
     * @param lla Latitude [rad], longitude [rad], altitude [m].
     *
     * @exception std::length_error Did not pass three-value list.
     */
    template<typename T>
    GeoCoord(const std::initializer_list<T> lla)  //  cppcheck-suppress noExplicitConstructor
    {
        static_assert(std::is_fundamental<T>::value, "Fundamental types only.");
        const std::size_t input_size = lla.size();

        if (input_size != 3)
        {
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
    GeoCoord(const GeoCoord& other) = default;

    /**
     * @brief Move construct GeoCoord.
     *
     * @param other Other GeoCoord.
     */
    GeoCoord(GeoCoord&& other) = default;

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

        if (input_size != 3)
        {
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
    GeoCoord& operator=(const GeoCoord& other) = default;

    /**
     * @brief Move assign GeoCoord.
     *
     * @param other Other GeoCoord.
     * @return GeoCoord.
     */
    GeoCoord& operator=(GeoCoord&& other) = default;

    /**
     * @brief Access latitude.
     *
     * @return Latitude [rad].
     */
    [[nodiscard]] double& latitude() noexcept
    {
        return m_lat_rad;
    }

    /**
     * @brief Get latitude.
     *
     * @return Latitude [rad].
     */
    [[nodiscard]] const double& latitude() const noexcept
    {
        return m_lat_rad;
    }

    /**
     * @brief Access longitude.
     *
     * @return Longitude [rad].
     */
    [[nodiscard]] double& longitude() noexcept
    {
        return m_lon_rad;
    }

    /**
     * @brief Get longitude.
     *
     * @return Longitude [rad].
     */
    [[nodiscard]] const double& longitude() const noexcept
    {
        return m_lon_rad;
    }

    /**
     * @brief Access altitude.
     *
     * @return Altitude [m].
     */
    [[nodiscard]] double& altitude() noexcept
    {
        return m_alt_m;
    }

    /**
     * @brief Access altitude.
     *
     * @return Altitude [m].
     */
    [[nodiscard]] const double& altitude() const noexcept
    {
        return m_alt_m;
    }

protected:
private:
    double m_lat_rad {0};  ///< Latitude in [rad].
    double m_lon_rad {0};  ///< Longitude in [rad].
    double m_alt_m {0};  ///< Altitude in [m].
};

// =================================================================================================
// OTHER FUNCTIONS
// =================================================================================================

/**
 * @brief Print a GeoCoord to a stream. Comma-separates values. No newline at the end.
 *
 * @param os Output stream.
 * @param coord GeoCoord to print.
 * @return Output stream with GeoCoord.
 */
std::ostream& operator<<(std::ostream& os, const GeoCoord& coord);

}    // namespace MathUtils
