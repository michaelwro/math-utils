/**
 * @file quaternion_to_dcm.cpp
 * @author Michael Wrona
 * @date 2023-03-19
 */

#include "Attitude/quaternion_to_dcm.h"

namespace MathUtils {

Matrix<3,3> quaternion_to_dcm(const Quaternion& q)
{
  const double q0 = q(0);
  const double q00 = q0 * q0;

  const double q1 = q(1);
  const double q11 = q1 * q1;

  const double q2 = q(2);
  const double q22 = q2 * q2;

  const double q3 = q(3);
  const double q33 = q3 * q3;

  const double q01 = q0 * q1;
  const double q02 = q0 * q2;
  const double q03 = q0 * q3;
  const double q12 = q1 * q2;
  const double q13 = q1 * q3;
  const double q23 = q2 * q3;

  return Matrix<3,3> {
    {(q00 + q11 - q22 - q33), 2.0 * (q12 + q03), 2.0 * (q13 - q02)},
    {2.0 * (q12 - q03), (q00 - q11 + q22 - q33), 2.0 * (q23 + q01)},
    {2.0 * (q13 + q02), 2.0 * (q23 - q01), (q00 - q11 - q22 + q33)}
  };
}

}  // namespace MathUtils
