/**
 * @file constants.h
 * @author Michael Wrona
 * @date 2023-03-04
 * @brief Commonly used constants.
 *
 * @ref https://www.unoosa.org/pdf/icg/2012/template/WGS_84.pdf
 * @ref https://en.wikipedia.org/wiki/Earth_radius#Arithmetic_mean_radius
 */

#ifndef MATHUTILS_CONSTANTS_H_
#define MATHUTILS_CONSTANTS_H_

namespace MathUtils { namespace Constants {

static constexpr double PI = 3.14159265358979;  ///< Pi constant.
static constexpr double TWO_PI = 2.0 * PI;  ///< Two time pi
static constexpr double PI_DIV2 = 0.5 * PI;  ///< Pi divided by two, `pi /2`

static constexpr double WGS84_RADIUS_M = 6371008.77141505945474;  ///< IUGG earth arithmetic mean radius, (2a + b) / 3 [m].
static constexpr double WGS84_INVF = 298.257223563;  ///< WGS84 inverse of flattening.
static constexpr double WGS84_F = 1.0 / WGS84_INVF;  ///< WGS84 flattening.
static constexpr double WGS84_ECC2 = 0.00669437999014;  ///< WGS84 eccentricity squared e^2.
static constexpr double WGS84_ECC = 0.08181919084262;  ///< WGS84 eccentricity.
static constexpr double WGS84_A_M = 6378137.0;  ///< WGS84 semimajor axis [m].
static constexpr double WGS84_B_M = 6356752.31424517929554;  ///< WGS semiminor axis [m].
static constexpr double WGS84_GRAV_MPS2 = 9.80665;  ///< WGS84 standard gravity [m/s/s].
static constexpr double WGS84_GM_M3PS2 = 3.986004418e14;  ///< WGS84 gravitational parameter [m^3 / s^2].
static constexpr double WGS84_RATE_RPS = 7.292115e-5;  ///< WGS84 mean angular velocity [rad/sec].

}  // namespace Constants
}  // namespace MathUtils

#endif  // MATHUTILS_CONSTANTS_H_
