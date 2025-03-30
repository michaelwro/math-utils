/**
 * @file Euler321.h
 * @author Michael Wrona
 * @date 2023-04-02
 */

#pragma once

#include <ostream>

namespace math {

/**
 * @brief Euler 321 (yaw, pitch, roll) attitude angles.
 *
 * @details Angles are in [rad].
 */
class Euler321 {
public:
    Euler321() = default;
    ~Euler321() = default;

    /**
     * @brief Create an Euler321.
     *
     * @param yaw_rad [rad] Yaw angle.
     * @param pitch_rad [rad] Pitch angle.
     * @param roll_rad [rad] Roll angle.
     */
    Euler321(const double yaw_rad, const double pitch_rad, const double roll_rad);

    /**
     * @brief Yaw angle.
     *
     * @return Yaw angle [rad].
     */
    [[nodiscard]] double& yaw() noexcept;

    /**
     * @brief Yaw angle.
     *
     * @return [rad] Yaw angle.
     */
    [[nodiscard]] const double& yaw() const noexcept;

    /**
     * @brief Pitch angle.
     *
     * @return [rad] Pitch angle.
     */
    [[nodiscard]] double& pitch() noexcept;

    /**
     * @brief Pitch angle.
     *
     * @return [rad] Pitch angle.
     */
    [[nodiscard]] const double& pitch() const noexcept;

    /**
     * @brief Roll angle.
     *
     * @return [rad] Roll roll.
     */
    [[nodiscard]] double& roll() noexcept;

    /**
     * @brief Roll angle.
     *
     * @return [rad] Roll roll.
     */
    [[nodiscard]] const double& roll() const noexcept;

private:
    double m_yaw_rad {0};    ///< [rad] Yaw angle.
    double m_pitch_rad {0};  ///< [rad] Pitch angle.
    double m_roll_rad {0};   ///< [rad] Roll angle.
};

// =======================================================================================
// OTHER FUNCTIONS
// =======================================================================================

/**
 * @brief Print a Euler321 to a stream. Comma-separates values. No newline at
 * the end.
 *
 * @details "{yaw},{pitch},{roll}".
 *
 * @param os Output stream.
 * @param coord Euler321 to print.
 * @return Output stream with Euler321.
 */
std::ostream& operator<<(std::ostream& os, const Euler321& angles);

}  // namespace math
