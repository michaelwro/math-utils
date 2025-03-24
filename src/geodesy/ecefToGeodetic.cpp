/**
 * @file ecefToGeodetic.cpp
 * @author michaelwro
 * @date 2025-03-23
 */

#pragma once

#include "geodesy/ecefToGeodetic.hpp"

#include <cmath>

#include "constants.hpp"
#include "conversions.hpp"
#include "geodesy/GeoCoord.hpp"
#include "math/sgn.hpp"
#include "math/wrapPi.hpp"

namespace math {

GeoCoord ecefToGeodetic(const Vector3& pos_ecef_m,
                        const PlanetEllipsoidObject& ellipsoid) {
    // get variables to match literature
    const double x = pos_ecef_m(0);
    const double y = pos_ecef_m(1);
    const double z = pos_ecef_m(2);
    const double r = pos_ecef_m.magnitude();

    const double re = ellipsoid.getSemiMajorAxis();
    const double ecc = ellipsoid.getEcc();
    const double ecc2 = ecc * ecc;

    auto c_planet = [&](const double lat) -> double {
        const double sin_lat = std::sin(lat);
        return re / std::sqrt(1.0 - (ecc2 * sin_lat * sin_lat));
    };

    auto s_planet = [&](const double lat) -> double {
        return c_planet(lat) * (1.0 - ecc2);
    };

    // equatorial projection of positon along the equator
    const double r_delta = std::sqrt((x * x) + (y * y));

    /**
     * If `r_delta` is small, that corresponds to a near +/- 90 deg latitude and a
     * divide-by-zero in the subsequent steps.
     */
    constexpr double RDELTA_SINGULARITY_THRESHOLD = 1e-8;
    double right_ascension {};

    if (r_delta <= RDELTA_SINGULARITY_THRESHOLD) {
        right_ascension = sgn(z) * constants::pi_div2;
    }
    else {
        right_ascension = std::atan2(y, x);
    }

    // make sure longitude is within [-180, 180] deg
    double longitude = wrapPi(right_ascension);

    // latitude iteration tolerance
    constexpr double latitude_tolerance = degreeToRadian(1e-9);

    // maximum number of iterations
    constexpr std::uint16_t max_iterations = 15;

    // start off with latitude = declination
    const double factor = z / r;
    assert(std::abs(factor) <= 1.0);
    double latitude = std::asin(factor);

    // perform iteration until latitude is converged
    double prev_latitude = latitude + 10.0;  // add big number to start with
    std::uint16_t iterations = 0;

    do {
        prev_latitude = latitude;
        latitude =
            std::atan((z + (c_planet(latitude) * ecc2 * std::sin(latitude))) / r_delta);
    } while (std::abs(latitude - prev_latitude) >= latitude_tolerance and
             ++iterations < max_iterations);

    /**
     * If near the poles by ~1 degree, use an alternative equation to calculate the
     * ellipsoid height.
     */
    constexpr double near_pole_threshold = degreeToRadian(1.0);
    double height {};

    if (constants::pi_div2 - std::abs(latitude) < near_pole_threshold) {
        height = (z / std::sin(latitude)) - s_planet(latitude);
    }
    else {
        height = (r_delta / std::cos(latitude)) - c_planet(latitude);
    }

    // return result
    return GeoCoord(latitude, longitude, height, GeoType::geodetic);
}

}  // namespace math