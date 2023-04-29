/**
 * @file Euler321.h
 * @author Michael Wrona
 * @date 2023-04-02
 */

#pragma once

#include "Internal/error_msg_helpers.h"

#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <type_traits>

namespace MathUtils {

/**
 * @brief Euler 321 (yaw, pitch, roll) attitude angles.
 *
 * @details Angles are in [rad].
 */
class Euler321 {
public:

    /**
     * @brief Create a Euler321.
     */
    Euler321() = default;

    /**
     * @brief Destroy a Euler321.
     */
    ~Euler321() = default;

    /**
     * @brief Create a Euler 321.
     *
     * @param yaw_rad Yaw angle in [rad].
     * @param pitch_rad Pitch angle in [rad].
     * @param roll_rad Roll angle in [rad].
     */
    Euler321(const double yaw_rad, const double pitch_rad, const double roll_rad);

    /**
     * @brief Create a Euler321.
     *
     * @tparam T Input type.
     * @param lla New yaw [rad], pitch [rad], and roll [rad].
     * @return Euler321.
     *
     * @exception std::length_error Did not pass three-value list.
     */
    template<typename T>
    Euler321(const std::initializer_list<T> angles);  //  cppcheck-suppress noExplicitConstructor

    /**
     * @brief Copy construct Euler321.
     *
     * @param other Other GoeCoord.
     */
    Euler321(const Euler321& other) = default;

    /**
     * @brief Move construct Euler321.
     *
     * @param other Other Euler321.
     */
    Euler321(Euler321&& other) = default;

    /**
     * @brief Assing Euler321 values from an initializer list.
     *
     * @tparam T Input type.
     * @param lla New yaw [rad], pitch [rad], and roll [rad].
     * @return Euler321.
     *
     * @exception std::length_error Did not pass three-value list.
     */
    template<typename T>
    Euler321& operator=(const std::initializer_list<T> angles);

    /**
     * @brief Copy assign Euler321.
     *
     * @param other Other Euler321.
     * @return Euler321.
     */
    Euler321& operator=(const Euler321& other);

    /**
     * @brief Move assign Euler321.
     *
     * @param other Other Euler321.
     * @return Euler321.
     */
    Euler321& operator=(Euler321&& other) noexcept;

    /**
     * @brief Access yaw angle.
     *
     * @return Yaw angle [rad].
     */
    [[nodiscard]] double& yaw() noexcept;

    /**
     * @brief Get yaw angle.
     *
     * @return Yaw angle [rad].
     */
    [[nodiscard]] const double& yaw() const noexcept;

    /**
     * @brief Access pitch angle.
     *
     * @return Pitch angle [rad].
     */
    [[nodiscard]] double& pitch() noexcept;

    /**
     * @brief Get pitch angle.
     *
     * @return Pitch angle [rad].
     */
    [[nodiscard]] const double& pitch() const noexcept;

    /**
     * @brief Access roll angle.
     *
     * @return Roll roll [rad].
     */
    [[nodiscard]] double& roll() noexcept;

    /**
     * @brief Get roll angle.
     *
     * @return Roll angle [rad].
     */
    [[nodiscard]] const double& roll() const noexcept;

    /**
     * @brief Print a Euler321 to a stream. Comma-separates values. No newline at the end.
     *
     * @param os Output stream.
     * @param coord Euler321 to print.
     * @return Output stream with Euler321.
     */
    friend std::ostream& operator<<(std::ostream& os, const Euler321& angles);

protected:
private:
    double m_yaw_rad {0};  ///< Yaw angle in [rad].
    double m_pitch_rad {0};  ///< Pitch angle in [rad].
    double m_roll_rad {0};  ///< Roll angle in [rad].
};

// =================================================================================================
// CLASS MEMBER FUNCTIONS
// =================================================================================================

template<typename T>
Euler321::Euler321(const std::initializer_list<T> angles)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");
    const std::size_t input_size = angles.size();

    if (input_size != 3) {
        throw std::length_error(Internal::invalid_init_list_length_error_msg(input_size, 3));
    }

    m_yaw_rad = *(angles.begin());
    m_pitch_rad = *(angles.begin() + 1);
    m_roll_rad = *(angles.begin() + 2);
}

template<typename T>
Euler321& Euler321::operator=(const std::initializer_list<T> angles)
{
    static_assert(std::is_fundamental<T>::value, "Fundamental types only.");
    const std::size_t input_size = angles.size();

    if (input_size != 3) {
        throw std::length_error(Internal::invalid_init_list_length_error_msg(input_size, 3));
    }

    m_yaw_rad = *(angles.begin());
    m_pitch_rad = *(angles.begin() + 1);
    m_roll_rad = *(angles.begin() + 2);

    return *this;
}

}    // namespace MathUtils
