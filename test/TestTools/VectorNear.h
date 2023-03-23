/**
 * @file VectorNear.h
 * @author Michael Wrona
 * @date 2023-03-19
 */

#ifndef MATHUTILS_GTEST_TOOLS_VECTOR_NEAR_H_
#define MATHUTILS_GTEST_TOOLS_VECTOR_NEAR_H_

#include "LinAlg/Vector.h"

#include <cmath>
#include <gtest/gtest.h>
#include <iomanip>
#include <limits>
#include <sstream>

namespace MathUtils {
namespace TestTools {

/**
 * @brief Check two MathUtils::Vector for equality.
 *
 * @param v1 First vector.
 * @param v2 Second vector.
 * @param tol Absolute tolerance for each element. Defaults to 1e-14.
 * @returns Test assertion success or failure.
 *
 * @ref https://stackoverflow.com/a/7121785
 */

template<std::size_t N>
::testing::AssertionResult VectorNear(const MathUtils::Vector<N>& v1,
  const MathUtils::Vector<N>& v2,
  const double tol=1e-14)
{
  bool success = true;
  std::stringstream error_msgs;

  for (std::size_t ii = 0; ii < N; ii++)
  {
    const double diff = std::abs(v1(ii) - v2(ii));

    if (diff > tol)
    {
      success = false;
      error_msgs << "\nElement (" << ii << ") differs by " <<  std::scientific << diff;
    }
  }

  if (!success)
  {
    return ::testing::AssertionFailure() << "Vectors are not equal." << error_msgs.str();
  }

  return ::testing::AssertionSuccess();
}

}  // namespace TestTools
}  // namespace MathUtils

#endif  // MATHUTILS_GTEST_TOOLS_VECTOR_NEAR_H_
