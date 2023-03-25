/**
 * @file asin_safe.cpp
 * @author Michael Wrona
 * @date 2023-03-25
 */

#include "asin_safe.h"
#include "constants.h"

#include <cmath>
#include <cassert>

namespace MathUtils {

double asin_safe(const double val) noexcept
{
  assert(std::abs(val) <= 1.0);

  if (val >= 1.0)
  {
    return Constants::PI_DIV2;
  }
  else if (val <= -1.0)
  {
    return -Constants::PI_DIV2;
  }

  return std::asin(val);
}

}  // MathUtils
