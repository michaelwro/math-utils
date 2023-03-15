/**
 * @file QuaternionMath.cpp
 * @author Michael Wrona
 * @date 2023-03-15
 * @brief Quaternion math functions.
 */

#include "Attitude/QuaternionMath.h"

namespace MathUtils {

Vector<3> quatrotate(const Quaternion& q_a_b, const Vector<3>& v_b)
{
  const double q0 = q_a_b(0);
  const double q00 = q0 * q0;

  const double q1 = q_a_b(1);
  const double q11 = q1 * q1;

  const double q2 = q_a_b(2);
  const double q22 = q2 * q2;

  const double q3 = q_a_b(3);
  const double q33 = q3 * q3;

  const double q01 = q0 * q1;
  const double q02 = q0 * q2;
  const double q03 = q0 * q3;
  const double q12 = q1 * q2;
  const double q13 = q1 * q3;
  const double q23 = q2 * q3;

  Vector<3> v_a;

  v_a(0) = (q00 + q11 - q22 - q33) * v_b(0);
  v_a(0) += 2.0 * (q12 + q03) * v_b(1);
  v_a(0) += 2.0 * (q13 - q02) * v_b(2);

  v_a(1) = 2.0 * (q12 - q03) * v_b(0);
  v_a(1) += (q00 - q11 + q22 - q33) * v_b(1);
  v_a(1) += 2.0 * (q23 + q01) * v_b(2);

  v_a(2) = 2.0 * (q13 + q02) * v_b(0);
  v_a(2) += 2.0 * (q23 - q01) * v_b(1);
  v_a(2) += (q00 - q11 - q22 + q33) * v_b(2);

  return v_a;
}

}  // namespace MathUtils
