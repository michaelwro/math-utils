/**
 * @file constants.h
 * @author Michael Wrona
 * @date 2023-03-04
 * @brief Commonly used constants.
 */

#pragma once

#include <cmath>

namespace math::constants {

constexpr double pi = M_PI;            ///< Pi constant
constexpr double two_pi = 2.0 * pi;    ///< Two times pi
constexpr double pi_div2 = 0.5 * pi;   ///< Pi divided by two, pi / 2
constexpr double pi_div4 = 0.25 * pi;  ///< Pi divided by four, pi / 4

// constexpr inline double WGS84_INVF = 298.257'223'563;  ///< WGS84 inverse of
// flattening. constexpr inline double WGS84_F = 1.0 / WGS84_INVF;    ///< WGS84
// flattening.

// constexpr inline double WGS84_ECC2 =
//     (2.0 * WGS84_F) - (WGS84_F * WGS84_F);  ///< WGS84 eccentricity squared e^2.

// extern double WGS84_ECC;

// constexpr inline double WGS84_A_M = 6'378'137.0;  ///< WGS84 semimajor axis [m].
// constexpr inline double WGS84_B_M =
//     WGS84_A_M * (1.0 - WGS84_F);  ///< WGS semiminor axis [m].

// constexpr inline double WGS84_GM_M3PS2 =
//     3.986'004'418e14;  ///< WGS84 gravitational parameter [m^3 / s^2].

// constexpr inline double WGS84_RATE_RPS =
//     7.292'115e-5;  ///< WGS84 mean angular velocity [rad/sec].

// constexpr inline double EARTH_MEAN_RADIUS_M =
//     ((2.0 * WGS84_A_M) + WGS84_B_M) /
//     3.0;  ///< IUGG earth arithmetic mean radius, (2a + b) / 3 [m].

// constexpr inline double EARTH_GRAV_MPS2 = 9.806'65;  ///< Earth standard gravity
// [m/s/s].

}  // namespace math::constants
