/**
 * @file error_msg_helpers.h
 * @author Michael Wrona
 * @date 2023-03-22
 */

#pragma once
#include <cstddef>
#include <string>

namespace MathUtils {
namespace Internal {

/**
 * @brief Helper for printing divide-by-zero error messages.
 *
 * @return Error message.
 */
inline std::string divide_by_zero_error_msg()
{
    return std::string("Potential divide-by-zero.");
}

/**
 * @brief Helper for printing invalid length initializer length error messages.
 *
 * @details For 1D types such as Vector or Quaternion.
 *
 * @param input_len Input vector/quaternion length.
 * @param expected_len Expected vector/quaternion length.
 * @return Error message.
 *
 * @see MathUtils::Vector
 * @see Mathutils::Quaternion
 */
inline std::string invalid_init_list_length_error_msg(const std::size_t input_len,
    const std::size_t expected_len)
{
    return std::string("Expected ") +
        std::to_string(expected_len) +
        std::string(", got ") +
        std::to_string(input_len) +
        std::string(".");
}

/**
 * @brief Helper for printing invalid length initializer length error messages.
 *
 * @details For 2D types such as Matrix.
 *
 * @param input_rows Input rows.
 * @param input_cols Input columns.
 * @param expected_rows Expected matrix rows.
 * @param expected_cols Expected matrix columns.
 * @return Error message.
 *
 * @see MathUtils::Matrix
 */
inline std::string invalid_init_list_length_error_msg(const std::size_t input_rows,
    const std::size_t input_cols,
    const std::size_t expected_rows,
    const std::size_t expected_cols)
{
    return std::string("Expected ") +
        std::string("(") +
        std::to_string(expected_rows) +
        std::string(",") +
        std::to_string(expected_cols) +
        std::string(")") +
        std::string(", got ") +
        std::string("(") +
        std::to_string(input_rows) +
        std::string(",") +
        std::to_string(input_cols) +
        std::string(").");
}

/**
 * @brief Helper for printing invalid index error messages.
 *
 * @details For 1D types such as Vector or Quaternion.
 *
 * @param input_index Input index.
 * @param max_length Maximum length.
 * @return Error message.
 *
 * @see MathUtils::Vector
 * @see Mathutils::Quaternion
 */
inline std::string invalid_index_error_msg(const std::size_t input_index,
    const std::size_t max_length)
{
    return std::string("Index ") +
        std::to_string(input_index) +
        std::string(" is invalid for ") +
        std::to_string(max_length) +
        std::string(" size object.");
}

/**
 * @brief Helper for printing invalid index error messages.
 *
 * @details For 2D types such as Matrix.
 *
 * @param input_row Input row.
 * @param input_col Input column.
 * @param max_rows Maximum rows.
 * @param max_cols Maximum columns.
 * @return Error message.
 *
 * @see MathUtils::Matrix
 */
inline std::string invalid_index_error_msg(const std::size_t input_row,
    const std::size_t input_col,
    const std::size_t max_rows,
    const std::size_t max_cols)
{
    return std::string("Index ") +
        std::string("(") +
        std::to_string(input_row) +
        std::string(",") +
        std::to_string(input_col) +
        std::string(")") +
        std::string(" is invalid for ") +
        std::string("(") +
        std::to_string(max_rows) +
        std::string(",") +
        std::to_string(max_cols) +
        std::string(")") +
        std::string(" size object.");
}

}    // namespace Internal
}    // namespace MathUtils
