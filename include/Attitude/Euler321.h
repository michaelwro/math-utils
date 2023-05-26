/**
 * @file Euler321.h
 * @author Michael Wrona
 * @date 2023-04-02
 */

#pragma once

#include "Internal/error_msg_helpers.h"

#include <concepts>
#include <initializer_list>
#include <ostream>
#include <stdexcept>

namespace MathUtils {

/**
 * @brief Criteria for a valid MathUtils::Euler321 element.
 *
 * @tparam T Element type.
 */
template<typename T>
concept valid_euler321_element = std::integral<T> || std::floating_point<T>;

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
     * @param yaw_rad Yaw angle in [rad].
     * @param pitch_rad Pitch angle in [rad].
     * @param roll_rad Roll angle in [rad].
     */
    Euler321(const double yaw_rad, const double pitch_rad, const double roll_rad)
        :m_yaw_rad(yaw_rad),
        m_pitch_rad(pitch_rad),
        m_roll_rad(roll_rad)
    {}

    /**
     * @brief Create an Euler321.
     *
     * @tparam T Input type.
     * @param angles New yaw [rad], pitch [rad], and roll [rad].
     * @return Euler321.
     *
     * @exception std::length_error Did not pass three-value list.
     */
    template<typename T>
    requires valid_euler321_element<T>
    Euler321(const std::initializer_list<T> angles)  //  cppcheck-suppress noExplicitConstructor
    {
        const std::size_t input_size = angles.size();

        if (input_size != 3)
        {
            throw std::length_error(Internal::invalid_init_list_length_error_msg(input_size, 3));
        }

        m_yaw_rad = *(angles.begin());
        m_pitch_rad = *(angles.begin() + 1);
        m_roll_rad = *(angles.begin() + 2);
    }

    Euler321(const Euler321& other) = default;

    Euler321(Euler321&& other) = default;

    /**
     * @brief Assing Euler321 values from an initializer list.
     *
     * @tparam T Input type.
     * @param angles New yaw [rad], pitch [rad], and roll [rad].
     * @return Euler321.
     *
     * @exception std::length_error Did not pass three-value list.
     */
    template<typename T>
    requires valid_euler321_element<T>
    Euler321& operator=(const std::initializer_list<T> angles)
    {
        const std::size_t input_size = angles.size();

        if (input_size != 3)
        {
            throw std::length_error(Internal::invalid_init_list_length_error_msg(input_size, 3));
        }

        m_yaw_rad = *(angles.begin());
        m_pitch_rad = *(angles.begin() + 1);
        m_roll_rad = *(angles.begin() + 2);

        return *this;
    }

    Euler321& operator=(const Euler321& other) = default;

    Euler321& operator=(Euler321&& other) noexcept = default;

    /**
     * @brief Access yaw angle.
     *
     * @return Yaw angle [rad].
     */
    [[nodiscard]] double& yaw() noexcept
    {
        return m_yaw_rad;
    }

    /**
     * @brief Get yaw angle.
     *
     * @return Yaw angle [rad].
     */
    [[nodiscard]] const double& yaw() const noexcept
    {
        return m_yaw_rad;
    }

    /**
     * @brief Access pitch angle.
     *
     * @return Pitch angle [rad].
     */
    [[nodiscard]] double& pitch() noexcept
    {
        return m_pitch_rad;
    }

    /**
     * @brief Get pitch angle.
     *
     * @return Pitch angle [rad].
     */
    [[nodiscard]] const double& pitch() const noexcept
    {
        return m_pitch_rad;
    }

    /**
     * @brief Access roll angle.
     *
     * @return Roll roll [rad].
     */
    [[nodiscard]] double& roll() noexcept
    {
        return m_roll_rad;
    }

    /**
     * @brief Get roll angle.
     *
     * @return Roll angle [rad].
     */
    [[nodiscard]] const double& roll() const noexcept
    {
        return m_roll_rad;
    }

protected:
private:
    double m_yaw_rad {0};  ///< Yaw angle in [rad].
    double m_pitch_rad {0};  ///< Pitch angle in [rad].
    double m_roll_rad {0};  ///< Roll angle in [rad].
};

// =================================================================================================
// OTHER FUNCTIONS
// =================================================================================================

/**
 * @brief Print a Euler321 to a stream. Comma-separates values. No newline at the end.
 *
 * @details "{yaw}, {pitch}, {roll}".
 *
 * @param os Output stream.
 * @param coord Euler321 to print.
 * @return Output stream with Euler321.
 */
std::ostream& operator<<(std::ostream& os, const Euler321& angles);

}    // namespace MathUtils
