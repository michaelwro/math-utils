/**
 * @file EGM2008Ellipsoid.cpp
 * @author michaelwro
 * @date 2025-03-23
 */

#include "EGM2008Ellipsoid.hpp"

#include <cmath>

double EGM2008Ellipsoid::getGravParam() const {
    static_assert(m_grav_param_m3ps2 > 0.0, "Must be positive.");

    return m_grav_param_m3ps2;
}

double EGM2008Ellipsoid::getSemiMajorAxis() const {
    static_assert(m_sma_m > 0.0, "Must be positive.");
    return m_sma_m;
}

double EGM2008Ellipsoid::getSemiMinorAxis() const {
    return m_sma_m * (1.0 - m_flattening);
}

double EGM2008Ellipsoid::getFlattening() const {
    static_assert(m_flattening > 0.0, "Must be positive.");
    return m_flattening;
}

double EGM2008Ellipsoid::getEcc() const {
    return std::sqrt((2.0 * m_flattening) - (m_flattening * m_flattening));
}
