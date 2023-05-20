/**
 * @file conversions.h
 * @author Michael Wrona
 * @date 2023-03-25
 * @brief Unit conversions.
 *
 * @ref https://www.nist.gov/pml/special-publication-811/nist-guide-si-appendix-b-conversion-factors/nist-guide-si-appendix-b8
 */

#pragma once

#include "constants.h"

namespace MathUtils {
namespace Conversions {
namespace Internal {

constexpr double NIST_FT_TO_M = 0.3048;
constexpr double NIST_IN_TO_CM = 2.54;
constexpr double NIST_IN_TO_MM = 254.0;
constexpr double NIST_M_TO_CM = 100.0;
constexpr double NIST_NMI_TO_M = 1852.0;
constexpr double NIST_MI_TO_M = 1.609344e3;
constexpr double NIST_MI_TO_KM = 1.609344;
constexpr double NIST_KTS_TO_MPS = NIST_NMI_TO_M / 3600.0;
constexpr double NIST_LB_TO_N = 4.448222;
constexpr double NIST_BAR_TO_PA = 1e5;
constexpr double NIST_BAR_TO_HPA = 1e3;
constexpr double NIST_PA_TO_INHG_32F = 3.386389e-3;
constexpr double NIST_ATM_TO_PA = 101325.0;

}  // namespace Internal

// =================================================================================================
// ANGLES
// =================================================================================================

/**
 * @brief Radians to degrees.
 */
[[nodiscard]] inline double rad2deg(const double rad) noexcept
{
    return rad * (180.0 / Constants::PI);
}

/**
 * @brief Radians to degrees.
 */
[[nodiscard]] inline double deg2rad(const double deg) noexcept
{
    return deg * (Constants::PI / 180.0);
}

/**
 * @brief Rotations per minute to radians per second.
 */
[[nodiscard]] inline double rmp2rps(const double rpm) noexcept
{
    return rpm * (Constants::PI / 30.0);
}

/**
 * @brief Radians per second to rotations per minute.
 */
[[nodiscard]] inline double rps2rpm(const double rps) noexcept
{
    return rps * (30.0 / Constants::PI);
}

// =================================================================================================
// DISTANCE
// =================================================================================================

/**
 * @brief Feet to meters.
 */
[[nodiscard]] inline double ft2m(const double ft) noexcept
{
    return ft * Internal::NIST_FT_TO_M;
}

/**
 * @brief Meters to feet.
 */
[[nodiscard]] inline double m2ft(const double m) noexcept
{
    return m / Internal::NIST_FT_TO_M;
}

/**
 * @brief Inches to centimeters.
 */
[[nodiscard]] inline double in2cm(const double in) noexcept
{
    return in * Internal::NIST_IN_TO_CM;
}

/**
 * @brief Centimeters to inches.
 */
[[nodiscard]] inline double cm2in(const double cm) noexcept
{
    return cm / Internal::NIST_IN_TO_CM;
}

/**
 * @brief Inches to millimeters.
 */
[[nodiscard]] inline double in2mm(const double in) noexcept
{
    return in * Internal::NIST_IN_TO_MM;
}

/**
 * @brief Millimeters to inches.
 */
[[nodiscard]] inline double mm2in(const double mm) noexcept
{
    return mm / Internal::NIST_IN_TO_MM;
}

/**
 * @brief Meters to centimeters.
 */
[[nodiscard]] inline double m2cm(const double m) noexcept
{
    return m * Internal::NIST_M_TO_CM;
}

/**
 * @brief Centimeters to meters.
 */
[[nodiscard]] inline double cm2m(const double cm) noexcept
{
    return cm / Internal::NIST_M_TO_CM;
}

/**
 * @brief Nautical miles to meters.
 */
[[nodiscard]] inline double nmi2m(const double nmi) noexcept
{
    return nmi * Internal::NIST_NMI_TO_M;
}

/**
 * @brief Meters to nautical miles.
 */
[[nodiscard]] inline double m2nmi(const double m) noexcept
{
    return m / Internal::NIST_NMI_TO_M;
}

/**
 * @brief Statute miles to meters.
 */
[[nodiscard]] inline double mi2m(const double mi) noexcept
{
    return mi * Internal::NIST_MI_TO_M;
}

/**
 * @brief Meters to statute miles.
 */
[[nodiscard]] inline double m2mi(const double m) noexcept
{
    return m / Internal::NIST_MI_TO_M;
}

/**
 * @brief Statute miles to kilometers.
 */
[[nodiscard]] inline double mi2km(const double mi) noexcept
{
    return mi * Internal::NIST_MI_TO_KM;
}

/**
 * @brief Kilometers to statute miles.
 */
[[nodiscard]] inline double km2mi(const double km) noexcept
{
    return km / Internal::NIST_MI_TO_KM;
}

// =================================================================================================
// SPEED
// =================================================================================================

/**
 * @brief Knots to meters per second.
 */
[[nodiscard]] inline double kts2mps(const double kts) noexcept
{
    return kts * Internal::NIST_KTS_TO_MPS;
}

/**
 * @brief Meters per second to knots.
 */
[[nodiscard]] inline double mps2kts(const double mps) noexcept
{
    return mps / Internal::NIST_KTS_TO_MPS;
}

// =================================================================================================
// FORCE
// =================================================================================================

/**
 * @brief Pound-force (lbf) to Newtons.
 */
[[nodiscard]] inline double lb2n(const double lb) noexcept
{
    return lb * Internal::NIST_LB_TO_N;
}

/**
 * @brief Newtons to pound-force (lbf).
 */
[[nodiscard]] inline double n2lb(const double n) noexcept
{
    return n / Internal::NIST_LB_TO_N;
}

// =================================================================================================
// PRESSURE
// =================================================================================================

/**
 * @brief Bar to Pascals.
 */
[[nodiscard]] inline double bar2pa(const double bar) noexcept
{
    return bar * Internal::NIST_BAR_TO_PA;
}

/**
 * @brief Pascals to bar.
 */
[[nodiscard]] inline double pa2bar(const double pa) noexcept
{
    return pa / Internal::NIST_BAR_TO_PA;
}

/**
 * @brief Bar to hectopascals.
 */
[[nodiscard]] inline double bar2hpa(const double bar) noexcept
{
    return bar * Internal::NIST_BAR_TO_HPA;
}

/**
 * @brief Hectopascals to bar.
 */
[[nodiscard]] inline double hpa2bar(const double hpa) noexcept
{
    return hpa / Internal::NIST_BAR_TO_HPA;
}

/**
 * @brief Pascals to inches of mercury (~32 degF).
 */
[[nodiscard]] inline double pa2inhg(const double pa) noexcept
{
    return pa * Internal::NIST_PA_TO_INHG_32F;
}

/**
 * @brief Inches of mercury to Pascals (~32 degF).
 */
[[nodiscard]] inline double inhg2pa(const double inhg) noexcept
{
    return inhg / Internal::NIST_PA_TO_INHG_32F;
}

/**
 * @brief Atmospheres to Pascals.
 */
[[nodiscard]] inline double atm2pa(const double atm) noexcept
{
    return atm * Internal::NIST_ATM_TO_PA;
}

/**
 * @brief Pascals to atmospheres.
 */
[[nodiscard]] inline double pa2atm(const double pa) noexcept
{
    return pa / Internal::NIST_ATM_TO_PA;
}

// =================================================================================================
// TEMPERATURE
// =================================================================================================

/**
 * @brief Degrees fahrenheit to celsius.
 */
[[nodiscard]] inline double f2c(const double f) noexcept
{
    return (5.0 * (f - 32.0)) / 9.0;
}

/**
 * @brief Degrees celsius to Fahrenheit.
 */
[[nodiscard]] inline double c2f(const double c) noexcept
{
    return 32.0 + ((9.0 * c) / 5.0);
}

/**
 * @brief Degrees celsius to Kelvin.
 */
[[nodiscard]] inline double c2k(const double c) noexcept
{
    return c + 273.15;
}

/**
 * @brief Degrees Kelvin to celsius.
 */
[[nodiscard]] inline double k2c(const double k) noexcept
{
    return k - 273.15;
}

}  // namespace Conversions
}  // namespace MathUtils
