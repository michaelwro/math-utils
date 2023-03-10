/**
 * @file conversions.h
 * @author Michael Wrona
 * @date 2023-03-04
 * @brief Unit conversion constants.
 *
 * @ref https://www.nist.gov/pml/special-publication-811/nist-guide-si-appendix-b-conversion-factors/nist-guide-si-appendix-b8
 */

#ifndef MATHUTILS_CONVERSIONS_H_
#define MATHUTILS_CONVERSIONS_H_

#include "constants.h"

namespace MathUtils { namespace Conversions {

// ANGLE
static constexpr double RAD_TO_DEG = 180.0 / Constants::PI;  ///< Radians to degrees.
static constexpr double DEG_TO_RAD = Constants::PI / 180.0;  ///< Degrees to radians.
static constexpr double RPM_TO_RPS = Constants::PI / 30.0;  ///< Rotations per minute to radians per second.
static constexpr double RPS_TO_RPM = 30.0 / Constants::PI;  ///< Rotations per minute to radians per second.

// DISTANCE
static constexpr double FT_TO_M = 0.3048;  ///< Feet to meters.
static constexpr double M_TO_FT = 1.0 / FT_TO_M;  ///< Meters to feet.
static constexpr double IN_TO_CM = 2.54;  ///< Inches to centimeters.
static constexpr double CM_TO_IN = 1.0 / IN_TO_CM;  ///< Centimeters to inches.
static constexpr double IN_TO_MM = 254.0;  ///< Inches to millimeters.
static constexpr double MM_TO_IN = 1.0 / IN_TO_MM;  ///< Millimeters to inches.
static constexpr double NMI_TO_M = 1852.0;  ///< Nautical miles to meters.
static constexpr double M_TO_NMI = 1.0 / NMI_TO_M;  ///< Meters to nautical miles.
static constexpr double MI_TO_M = 1.609344e3;  ///< Statute miles to meters.
static constexpr double M_TO_MI = 1.609344e-3;  ///< Meters to statute miles.
static constexpr double MI_TO_KM = 1.609344;  ///< Statute miles to kilometers.
static constexpr double KM_TO_MI = 1.0 / 1.609344;  ///< Kilometers to statute miles.

// SPEED
static constexpr double KNT_TO_MPS = 1852.0 / 3600.0;  ///< Knots to meters per second.
static constexpr double MPS_TO_KNT = 1.0 / KNT_TO_MPS;  ///< Meters per second to knots.

// MASS, WEIGHT, FORCE
static constexpr double LB_TO_N = 4.448222;  ///< Pound-force (lbf) to newtons.
static constexpr double N_TO_LB = 1.0 / LB_TO_N;  ///< Newtons to pound-force (lbf)

// PRESSURE
static constexpr double BAR_TO_PA = 1e5;  ///< Bar to pascals.
static constexpr double PA_TO_BAR = 1e-5;  ///< Pascals to bar.
static constexpr double BAR_TO_HPA = 1e3;  ///< Bar to hectopascals.
static constexpr double HPA_TO_BAR = 1e-3;  ///< Bar to hectopascals.
static constexpr double PA_TO_INHG = 3.386389e-3;  ///< Pascals to inches of mercury (~32degF).
static constexpr double INHG_TO_PA = 3.386389e3;  ///< Inches of mercury to pascals (~32degF).
static constexpr double ATM_TO_PA = 101325.0;  ///< Atmospheres to pascals.
static constexpr double PA_TO_ATM = 1.0 / ATM_TO_PA;  ///< Atmospheres to pascals.

}  // namespace MathUtils
}  // namespace Conversions

#endif  // MATHUTILS_CONVERSIONS_H_
