/**
 * @file conversions.h
 * @author Michael Wrona
 * @date 2023-03-25
 * @brief Unit conversions.
 *
 * @ref https://www.nist.gov/pml/special-publication-811/nist-guide-si-appendix-b-conversion-factors/nist-guide-si-appendix-b8
 */

#ifndef MATHUTILS_CONVERSIONS_H_
#define MATHUTILS_CONVERSIONS_H_

#include "constants.h"

namespace MathUtils { namespace Conversions {

namespace Internal {

constexpr double NIST_FT_TO_M {0.3048};
constexpr double NIST_IN_TO_CM {2.54};
constexpr double NIST_IN_TO_MM {254.0};
constexpr double NIST_M_TO_CM {100.0};
constexpr double NIST_NMI_TO_M {1852.0};
constexpr double NIST_MI_TO_M {1.609344e3};
constexpr double NIST_MI_TO_KM {1.609344};
constexpr double NIST_KTS_TO_MPS {NIST_NMI_TO_M / 3600.0};
constexpr double NIST_LB_TO_N {4.448222};
constexpr double NIST_BAR_TO_PA {1e5};
constexpr double NIST_BAR_TO_HPA {1e3};
constexpr double NIST_PA_TO_INHG_32F {3.386389e-3};
constexpr double NIST_ATM_TO_PA {101325.0};

}  // namespace Internal

/**
 * @brief Radians to degrees.
 */
inline double rad2deg(const double rad)
{
  return rad * (180.0 / Constants::PI);
}

/**
 * @brief Radians to degrees.
 */
inline double deg2rad(const double deg)
{
  return deg * (Constants::PI / 180.0);
}

/**
 * @brief Rotations per minute to radians per second.
 */
inline double rmp2rps(const double rpm)
{
  return rpm * (Constants::PI / 30.0);
}

/**
 * @brief Radians per second to rotations per minute.
 */
inline double rps2rpm(const double rps)
{
  return rps * (30.0 / Constants::PI);
}

/**
 * @brief Feet to meters.
 */
inline double ft2m(const double ft)
{
  return ft * Internal::NIST_FT_TO_M;
}

/**
 * @brief Meters to feet.
 */
inline double m2ft(const double m)
{
  return m / Internal::NIST_FT_TO_M;
}

/**
 * @brief Inches to centimeters.
 */
inline double in2cm(const double in)
{
  return in * Internal::NIST_IN_TO_CM;
}

/**
 * @brief Centimeters to inches.
 */
inline double cm2in(const double cm)
{
  return cm / Internal::NIST_IN_TO_CM;
}

/**
 * @brief Inches to millimeters.
 */
inline double in2mm(const double in)
{
  return in * Internal::NIST_IN_TO_MM;
}

/**
 * @brief Millimeters to inches.
 */
inline double mm2in(const double mm)
{
  return mm / Internal::NIST_IN_TO_MM;
}

/**
 * @brief Meters to centimeters.
 */
inline double m2cm(const double m)
{
  return m * Internal::NIST_M_TO_CM;
}

/**
 * @brief Centimeters to meters.
 */
inline double cm2m(const double cm)
{
  return cm / Internal::NIST_M_TO_CM;
}

/**
 * @brief Nautical miles to meters.
 */
inline double nmi2m(const double nmi)
{
  return nmi * Internal::NIST_NMI_TO_M;
}

/**
 * @brief Meters to nautical miles.
 */
inline double m2nmi(const double m)
{
  return m / Internal::NIST_NMI_TO_M;
}

/**
 * @brief Statute miles to meters.
 */
inline double mi2m(const double mi)
{
  return mi * Internal::NIST_MI_TO_M;
}

/**
 * @brief Meters to statute miles.
 */
inline double m2mi(const double m)
{
  return m / Internal::NIST_MI_TO_M;
}

/**
 * @brief Statute miles to kilometers.
 */
inline double mi2km(const double mi)
{
  return mi * Internal::NIST_MI_TO_KM;
}

/**
 * @brief Kilometers to statute miles.
 */
inline double km2mi(const double km)
{
  return km / Internal::NIST_MI_TO_KM;
}

/**
 * @brief Knots to meters per second.
 */
inline double kts2mps(const double kts)
{
  return kts * Internal::NIST_KTS_TO_MPS;
}

/**
 * @brief Meters per second to knots.
 */
inline double mps2kts(const double mps)
{
  return mps / Internal::NIST_KTS_TO_MPS;
}

/**
 * @brief Pound-force (lbf) to Newtons.
 */
inline double lb2n(const double lb)
{
  return lb * Internal::NIST_LB_TO_N;
}

/**
 * @brief Newtons to pound-force (lbf).
 */
inline double n2lb(const double n)
{
  return n / Internal::NIST_LB_TO_N;
}

/**
 * @brief Bar to Pascals.
 */
inline double bar2pa(const double bar)
{
  return bar * Internal::NIST_BAR_TO_PA;
}

/**
 * @brief Pascals to bar.
 */
inline double pa2bar(const double pa)
{
  return pa / Internal::NIST_BAR_TO_PA;
}

/**
 * @brief Bar to hectopascals.
 */
inline double bar2hpa(const double bar)
{
  return bar * Internal::NIST_BAR_TO_HPA;
}

/**
 * @brief Hectopascals to bar.
 */
inline double hpa2bar(const double hpa)
{
  return hpa / Internal::NIST_BAR_TO_HPA;
}

/**
 * @brief Pascals to inches of mercury (~32 degF).
 */
inline double pa2inhg(const double pa)
{
  return pa * Internal::NIST_PA_TO_INHG_32F;
}

/**
 * @brief Inches of mercury to Pascals (~32 degF).
 */
inline double inhg2pa(const double inhg)
{
  return inhg / Internal::NIST_PA_TO_INHG_32F;
}

/**
 * @brief Atmospheres to Pascals.
 */
inline double atm2pa(const double atm)
{
  return atm * Internal::NIST_ATM_TO_PA;
}

/**
 * @brief Pascals to atmospheres.
 */
inline double pa2atm(const double pa)
{
  return pa / Internal::NIST_ATM_TO_PA;
}

/**
 * @brief Degrees fahrenheit to celsius.
 */
inline double f2c(const double f)
{
  return (5.0 * (f - 32.0)) / 9.0;
}

/**
 * @brief Degrees celsius to Fahrenheit.
 */
inline double c2f(const double c)
{
  return 32.0 + ((9.0 * c) / 5.0);
}

/**
 * @brief Degrees celsius to Kelvin.
 */
inline double c2k(const double c)
{
  return c + 273.15;
}

/**
 * @brief Degrees Kelvin to celsius.
 */
inline double k2c(const double k)
{
  return k - 273.15;
}

}  // namespace Conversions
}  // namespace MathUtils

#endif  // MATHUTILS_CONVERSIONS_H_
