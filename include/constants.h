/**
 * @file constants.h
 * @author Michael Wrona
 * @date 2023-03-04
 * @brief Commonly used constants.
 *
 * @details Computed with scripts/constants.py
 *
 * @ref https://www.unoosa.org/pdf/icg/2012/template/WGS_84.pdf
 * @ref https://en.wikipedia.org/wiki/Earth_radius#Arithmetic_mean_radius
 * @ref https://en.wikipedia.org/w/index.php?title=International_Standard_Atmosphere
 * @ref https://www.britannica.com/science/pi-mathematics
 */

#pragma once

#include <cmath>

namespace MathUtils {
namespace Constants {

constexpr inline double PI = 3.1415926535897931;  ///< Pi constant.
constexpr inline double TWO_PI = 2.0 * PI;  ///< Two time pi
constexpr inline double PI_DIV2 = 0.5 * PI;  ///< Pi divided by two, pi / 2
constexpr inline double PI_DIV4 = 0.25 * PI;  ///< Pi divided by four, pi / 4

constexpr inline double WGS84_INVF = 298.257223563;  ///< WGS84 inverse of flattening.
constexpr inline double WGS84_F = 1.0 / WGS84_INVF;  ///< WGS84 flattening.

constexpr inline double WGS84_ECC2 = (2.0 * WGS84_F) - (WGS84_F * WGS84_F);  ///< WGS84 eccentricity squared e^2.

/**
 * @brief WGS84 eccentricity.
 * @todo Use literal 0.0818191908426215 or compute at runtime?
 */
constexpr inline double WGS84_ECC = 0.0818191908426215;
// static inline const double WGS84_ECC = std::sqrt(WGS84_ECC2);

constexpr inline double WGS84_A_M = 6378137.0;  ///< WGS84 semimajor axis [m].
constexpr inline double WGS84_B_M = WGS84_A_M * (1.0 - WGS84_F);  ///< WGS semiminor axis [m].
constexpr inline double WGS84_GM_M3PS2 = 3.986004418e14;  ///< WGS84 gravitational parameter [m^3 / s^2].
constexpr inline double WGS84_RATE_RPS = 7.292115e-5;  ///< WGS84 mean angular velocity [rad/sec].

constexpr inline double EARTH_RADIUS_M = ((2.0 * WGS84_A_M) + WGS84_B_M) / 3.0;  ///< IUGG earth arithmetic mean radius, (2a + b) / 3 [m].

constexpr inline double EARTH_GRAV_MPS2 = 9.80665;  ///< Earth standard gravity [m/s/s].

}  // namespace Constants
}  // namespace MathUtils
