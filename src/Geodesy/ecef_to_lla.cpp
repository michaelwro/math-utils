/**
 * @file ecef_to_lla.cpp
 * @author Michael Wrona
 * @date 2023-04-04
 */

#include "Geodesy/ecef_to_lla.h"

#include "constants.h"

#include <cassert>
#include <cmath>

namespace MathUtils {

GeoCoord ecef_to_lla(const Vector<3>& pos_ecef_m)
{
    // pre-computed variables
    constexpr double a1 = Constants::WGS84_A_M * Constants::WGS84_ECC2;
    constexpr double a2 = a1 * a1;
    constexpr double a3 = 0.5 * a1 * Constants::WGS84_ECC2;
    constexpr double a4 = 2.5 * a2;
    constexpr double a5 = a1 + a3;
    constexpr double a6 = 1.0 - Constants::WGS84_ECC2;

    const double x = pos_ecef_m(0);
    const double y = pos_ecef_m(1);
    const double z = pos_ecef_m(2);

    const double longitude_rad = std::atan2(y, x);  // final longitude [rad]

    const double zp = std::abs(z);

    const double w2 = x*x + y*y;
    const double w = std::sqrt(w2);

    const double r2 = w2 + z*z;
    const double r = std::sqrt(r2);

    const double s2 = z*z/r2;
    const double c2 = w2/r2;

    double u = a2/r;
    double v = a3 - a4/r;

    double s{};
    double ss{};
    double c{};
    double latitude_rad{};

    // TODO: Use safe trig?
    if (c2 > 0.3) {
        s = (zp/r) * (1.0 + c2*(a1 + u + s2*v)/r);
        latitude_rad = std::asin(s);
        ss = s * s;
        c = std::sqrt(1.0 - ss);
    }
    else {
        c = (w/r) * (1.0 - s2*(a5 - u - c2*v)/r);
        latitude_rad = std::acos(c);
        ss = 1.0 - c*c;
        s = std::sqrt(ss);
    }

    const double g = 1.0 - Constants::WGS84_ECC2*ss;
    const double rg = Constants::WGS84_A_M / std::sqrt(g);
    const double rf = a6 * rg;

    u = w - rg*c;
    v = zp - rf*s;

    const double f = c*u + s*v;
    const double m = c*v - s*u;
    const double p = m / (rf/g + f);

    latitude_rad += p;
    const double altitude_m = f + m*p*0.5;  // final altitude [m]

    if (z < 0.0) {
        latitude_rad *= -1.0;  // final latitude
    }

    return GeoCoord(latitude_rad, longitude_rad, altitude_m);
}

}  // namespace MathUtils
