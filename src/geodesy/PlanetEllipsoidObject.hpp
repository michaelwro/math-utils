/**
 * @file PlanetEllipsoidObject.hpp
 * @author michaelwro
 * @date 2025-03-23
 */

#pragma once

/**
 * @brief Abstract base class for planet ellipsoid properties.
 */
class PlanetEllipsoidObject {
public:
    PlanetEllipsoidObject() = default;
    virtual ~PlanetEllipsoidObject() = default;

    /**
     * @brief Gravity parameter `mu`.
     *
     * @return [m^3/s^2] Gravity parameter.
     */
    virtual double getGravParam() const = 0;

    /**
     * @brief Semi-major axis (equatorial radius).
     *
     * @return [m] Semi-major axis.
     */
    virtual double getSemiMajorAxis() const = 0;

    /**
     * @brief Semi-minor axis (polar radius).
     *
     * @return [m] Semi-minor axis.
     */
    virtual double getSemiMinorAxis() const = 0;

    /**
     * @brief Flattening `f` coefficient.
     *
     * @return Flattening.
     */
    virtual double getFlattening() const = 0;

    /**
     * @brief Eccentricity.
     *
     * @return Eccentricity.
     */
    virtual double getEcc() const = 0;
};