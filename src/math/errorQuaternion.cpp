/**
 * @file errorQuaternion.cpp
 * @author michaelwro
 * @date 2025-04-06
 */

#include "math/errorQuaternion.hpp"

namespace math {

Quaternion errorQuaternion(const Quaternion& quat_true, const Quaternion& quat_measured) {
    return quat_true.getConjugate() * quat_measured;
}

}  // namespace math