/**
 * @file acos_safe.cpp
 * @author Michael Wrona
 * @date 2023-03-25
 */

#include "acos_safe.h"

#include "constants.h"

#include <cmath>
#include <cassert>

namespace MathUtils {

double acos_safe(const double val) noexcept
{
    assert(std::abs(val) <= 1.0);

    if (val >= 1.0) {
        return 0.0;
    }
    else if (val <= -1.0) {
        return Constants::PI;
    }

    return std::acos(val);
}

}  // namespace MathUtils
