/**
 * @file EGM2008Ellipsoid.hpp
 * @author michaelwro
 * @date 2025-03-23
 */

#pragma once

#include "PlanetEllipsoidObject.hpp"

/**
 * @brief EGM-2008 earth ellipsoid properties.
 * https://earth-info.nga.mil/index.php?dir=wgs84&action=wgs84
 */
class EGM2008Ellipsoid : public PlanetEllipsoidObject {
public:
    EGM2008Ellipsoid() = default;
    ~EGM2008Ellipsoid() override = default;

    /**
     * @brief EGM-2008 gravity parameter `mu`.
     *
     * @return [m^3/s^2] Gravity parameter.
     */
    double getGravParam() const override;

    /**
     * @brief EGM-2008 ellipsoid semi-major axis.
     *
     * @return [m] SMA.
     */
    double getSemiMajorAxis() const override;

    /**
     * @brief EGM-2008 ellipsoid semi-minor axis. Calculated from flattening and SMA.
     *
     * @return [m] Semi-minor axis.
     */
    double getSemiMinorAxis() const override;

    /**
     * @brief EGM-2008 / WGS-84 earth flattening coefficient.
     *
     * @return Flattening.
     */
    double getFlattening() const override;

    /**
     * @brief EGM-2008 / WGS-84 earth eccentricity. Calculated from flattening.
     *
     * @return Eccentricity.
     */
    double getEcc() const override;

private:
    /**
     * @brief EGM-2008 gravity parameter from NGA docs.
     */
    static constexpr double m_grav_param_m3ps2 {3'986'004.415e8};

    /**
     * @brief EGM-2008 semi-major axis from NGA docs.
     */
    static constexpr double m_sma_m {6'378'136.3};

    /**
     * @brief Earth flattening from NGA docs.
     */
    static constexpr double m_flattening {3.352'810'664'747'5e-03};
};
