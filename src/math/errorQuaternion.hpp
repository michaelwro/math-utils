/**
 * @file errorQuaternion.hpp
 * @author michaelwro
 * @date 2025-04-06
 */

#pragma once

#include "math/Quaternion.hpp"

namespace math {

/**
 * @brief Calculate the error quaternion between two quaternions. Uses HAMILTON
 * convention. `qt^{-1} (*) qm`.
 *
 * @param quat_true "True" quaterrnion.
 * @param quat_measured "Measured" quaternion.
 * @return Error quaternion.
 */
Quaternion errorQuaternion(const Quaternion& quat_true, const Quaternion& quat_measured);

}  // namespace math