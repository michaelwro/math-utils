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

#ifndef MATHUTILS_CONSTANTS_H_
#define MATHUTILS_CONSTANTS_H_

namespace MathUtils { namespace Constants {

constexpr double PI = 3.1415926535897931;  ///< Pi constant.
constexpr double TWO_PI = 6.2831853071795862;  ///< Two time pi
constexpr double PI_DIV2 = 1.5707963267948966;  ///< Pi divided by two, pi / 2
constexpr double PI_DIV4 = 0.7853981633974483;  ///< Pi divided by four, pi / 4

constexpr double WGS84_A_M = 6378137.0;  ///< WGS84 semimajor axis [m].
constexpr double WGS84_INVF = 298.257223563;  ///< WGS84 inverse of flattening.
constexpr double WGS84_F = 0.0033528106647475;  ///< WGS84 flattening.
constexpr double WGS84_ECC2 = 0.0066943799901413;  ///< WGS84 eccentricity squared e^2.
constexpr double WGS84_ECC = 0.0818191908426215;  ///< WGS84 eccentricity.
constexpr double WGS84_B_M = 6356752.3142451792955399;  ///< WGS semiminor axis [m].
constexpr double WGS84_GM_M3PS2 = 3.986004418e14;  ///< WGS84 gravitational parameter [m^3 / s^2].
constexpr double WGS84_RATE_RPS = 7.292115e-5;  ///< WGS84 mean angular velocity [rad/sec].
constexpr double EARTH_GRAV_MPS2 = 9.80665;  ///< Earth standard gravity [m/s/s].
constexpr double EARTH_RADIUS_M = 6371008.7714150594547391;  ///< IUGG earth arithmetic mean radius, (2a + b) / 3 [m].

}  // namespace Constants
}  // namespace MathUtils

#endif  // MATHUTILS_CONSTANTS_H_
