/**
 * @file conversions.h
 * @author Michael Wrona
 * @date 2023-03-25
 * @brief Unit conversions.
 */

#pragma once

#include "constants.hpp"

namespace math::internal {

/**
 * NOTE: all conversions are from:
 * https://www.nist.gov/pml/special-publication-811/nist-guide-si-appendix-b-conversion-factors/nist-guide-si-appendix-b8
 */

constexpr double ft_to_m = 0.3048;
constexpr double in_to_cm = 2.54;
constexpr double in_to_mm = 254.0;
constexpr double m_to_cm = 100.0;
constexpr double nmi_to_m = 1852.0;
constexpr double mi_to_m = 1.609344e3;
constexpr double mi_to_km = 1.609344;
constexpr double kts_to_mps = nmi_to_m / 3600.0;
constexpr double lb_to_n = 4.448222;
constexpr double bar_to_pa = 1e5;
constexpr double bar_to_hpa = 1e3;
constexpr double pa_to_inhg_32f = 3.386389e-3;
constexpr double atm_to_pa = 101325.0;

}  // namespace math::internal

namespace math {
// =======================================================================================
// ANGLES
// =======================================================================================

/**
 * @brief Radians to degrees.
 */
[[nodiscard]] constexpr double radianToDegree(const double rad) noexcept {
    return rad * (180.0 / constants::pi);
}

/**
 * @brief Radians to degrees.
 */
[[nodiscard]] constexpr double degreeToRadian(const double deg) noexcept {
    return deg * (constants::pi / 180.0);
}

/**
 * @brief Rotations per minute to radians per second.
 */
[[nodiscard]] constexpr double rotPerMinToRadPerSec(const double rpm) noexcept {
    return rpm * (2.0 * constants::pi / 60.0);
}

/**
 * @brief Radians per second to rotations per minute.
 */
[[nodiscard]] constexpr double radPerSecToRotPerMin(const double rps) noexcept {
    return rps * (0.5 * 60.0 / constants::pi);
}

// =======================================================================================
// DISTANCE
// =======================================================================================

/**
 * @brief Feet to meters.
 */
[[nodiscard]] constexpr double footToMeter(const double ft) noexcept {
    return ft * internal::ft_to_m;
}

/**
 * @brief Meters to feet.
 */
[[nodiscard]] constexpr double meterToFoot(const double m) noexcept {
    return m / internal::ft_to_m;
}

/**
 * @brief Inches to centimeters.
 */
[[nodiscard]] constexpr double inchToCentimeter(const double in) noexcept {
    return in * internal::in_to_cm;
}

/**
 * @brief Centimeters to inches.
 */
[[nodiscard]] constexpr double centimeterToInch(const double cm) noexcept {
    return cm / internal::in_to_cm;
}

/**
 * @brief Inches to millimeters.
 */
[[nodiscard]] constexpr double inchToMillimeter(const double in) noexcept {
    return in * internal::in_to_mm;
}

/**
 * @brief Millimeters to inches.
 */
[[nodiscard]] constexpr double millimeterToInch(const double mm) noexcept {
    return mm / internal::in_to_mm;
}

/**
 * @brief Meters to centimeters.
 */
[[nodiscard]] constexpr double meterToCentimeter(const double m) noexcept {
    return m * internal::m_to_cm;
}

/**
 * @brief Centimeters to meters.
 */
[[nodiscard]] constexpr double centimeterToMeter(const double cm) noexcept {
    return cm / internal::m_to_cm;
}

/**
 * @brief Nautical miles to meters.
 */
[[nodiscard]] constexpr double nauticalMileToMeter(const double nmi) noexcept {
    return nmi * internal::nmi_to_m;
}

/**
 * @brief Meters to nautical miles.
 */
[[nodiscard]] constexpr double meterToNauticalMile(const double m) noexcept {
    return m / internal::nmi_to_m;
}

/**
 * @brief Statute miles to meters.
 */
[[nodiscard]] constexpr double mileToMeter(const double mi) noexcept {
    return mi * internal::mi_to_m;
}

/**
 * @brief Meters to statute miles.
 */
[[nodiscard]] constexpr double meterToMile(const double m) noexcept {
    return m / internal::mi_to_m;
}

/**
 * @brief Statute miles to kilometers.
 */
[[nodiscard]] constexpr double mileToKilometer(const double mi) noexcept {
    return mi * internal::mi_to_km;
}

/**
 * @brief Kilometers to statute miles.
 */
[[nodiscard]] constexpr double kilometerToMile(const double km) noexcept {
    return km / internal::mi_to_km;
}

// =======================================================================================
// SPEED
// =======================================================================================

/**
 * @brief Knots to meters per second.
 */
[[nodiscard]] constexpr double knotsToMeterPerSec(const double kts) noexcept {
    return kts * internal::kts_to_mps;
}

/**
 * @brief Meters per second to knots.
 */
[[nodiscard]] constexpr double meterPerSecToKnots(const double mps) noexcept {
    return mps / internal::kts_to_mps;
}

// =======================================================================================
// FORCE
// =======================================================================================

/**
 * @brief Pound-force (lbf) to Newtons.
 */
[[nodiscard]] constexpr double poundfToNewton(const double lb) noexcept {
    return lb * internal::lb_to_n;
}

/**
 * @brief Newtons to pound-force (lbf).
 */
[[nodiscard]] constexpr double newtonToPoundf(const double n) noexcept {
    return n / internal::lb_to_n;
}

// =======================================================================================
// PRESSURE
// =======================================================================================

/**
 * @brief Bar to Pascals.
 */
[[nodiscard]] constexpr double barToPascal(const double bar) noexcept {
    return bar * internal::bar_to_pa;
}

/**
 * @brief Pascals to bar.
 */
[[nodiscard]] constexpr double pascalToBar(const double pa) noexcept {
    return pa / internal::bar_to_pa;
}

/**
 * @brief Bar to hectopascals.
 */
[[nodiscard]] constexpr double barToHectoPascal(const double bar) noexcept {
    return bar * internal::bar_to_hpa;
}

/**
 * @brief Hectopascals to bar.
 */
[[nodiscard]] constexpr double hectoPascalToBar(const double hpa) noexcept {
    return hpa / internal::bar_to_hpa;
}

/**
 * @brief Pascals to inches of mercury (~32 degF).
 */
[[nodiscard]] constexpr double pascalToInHg(const double pa) noexcept {
    return pa * internal::pa_to_inhg_32f;
}

/**
 * @brief Inches of mercury to Pascals (~32 degF).
 */
[[nodiscard]] constexpr double inHgToPascal(const double inhg) noexcept {
    return inhg / internal::pa_to_inhg_32f;
}

/**
 * @brief Atmospheres to Pascals.
 */
[[nodiscard]] constexpr double atmosphereToPascal(const double atm) noexcept {
    return atm * internal::atm_to_pa;
}

/**
 * @brief Pascals to atmospheres.
 */
[[nodiscard]] constexpr double pascalToAtmosphere(const double pa) noexcept {
    return pa / internal::atm_to_pa;
}

// =======================================================================================
// TEMPERATURE
// =======================================================================================

/**
 * @brief Degrees fahrenheit to celsius.
 */
[[nodiscard]] constexpr double fahrenheitToCelsius(const double f) noexcept {
    return (5.0 / 9.0) * (f - 32.0);
}

/**
 * @brief Degrees celsius to Fahrenheit.
 */
[[nodiscard]] constexpr double celsiusToFahrenheit(const double c) noexcept {
    return 32.0 + ((9.0 / 5.0) * c);
}

/**
 * @brief Degrees celsius to Kelvin.
 */
[[nodiscard]] constexpr double celsiusToKelvin(const double c) noexcept {
    return c + 273.15;
}

/**
 * @brief Degrees Kelvin to celsius.
 */
[[nodiscard]] constexpr double kelvinToCelsius(const double k) noexcept {
    return k - 273.15;
}

}  // namespace math
