/**
 * @file GeoType.hpp
 * @author michaelwro
 * @date 2025-03-23
 */

#pragma once

#include <cstdint>
#include <ostream>

namespace math {

/**
 * @brief Geodetic coordinate (LLA) type.
 */
enum class GeoType : std::uint32_t {
    geodetic = 0,   ///< Geodetic (w.r.t. ellipse) coordinate
    geocentric = 1  ///< Geocentric (w.r.t. sphere) coordinate.
};

/**
 * @brief Output a GeoType to a stream. Converts to the corresponding INTEGER.
 *
 * @param[in,out] os The stream.
 * @param type The type.
 * @return Stream with the integer added.
 */
std::ostream& operator<<(std::ostream& os, const GeoType& type);

}  // namespace math
