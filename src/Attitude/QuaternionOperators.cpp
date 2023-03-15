/**
 * @file QuaternionOperators.cpp
 * @author Michael Wrona
 * @date 2023-03-15
 * @brief Quaternion operator overloads.
 */

#include "Attitude/QuaternionOperators.h"

namespace MathUtils {

Quaternion operator*(const Quaternion& q_b, const Quaternion& q_c)
{
  // NOTE: Constructor normalizes result.
  return Quaternion(
    (q_c(0) * q_b(0)) - (q_c(1) * q_b(1)) - (q_c(2) * q_b(2)) - (q_c(3) * q_b(3)),
    (q_c(1) * q_b(0)) + (q_c(0) * q_b(1)) + (q_c(3) * q_b(2)) - (q_c(2) * q_b(3)),
    (q_c(2) * q_b(0)) - (q_c(3) * q_b(1)) + (q_c(0) * q_b(2)) + (q_c(1) * q_b(3)),
    (q_c(3) * q_b(0)) + (q_c(2) * q_b(1)) - (q_c(1) * q_b(2)) + (q_c(0) * q_b(3))
  );
}

}  // namespace MathUtils
