/**
 * @file dcm_to_euler.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "Attitude/dcm_to_euler.h"

#include <cmath>

namespace MathUtils {

Euler321 dcm_to_euler(const Matrix<3,3>& dcm)
{
    return Euler321 {
        std::atan2(dcm(0,1), dcm(0,0)),
        -std::asin(dcm(0,2)),
        std::atan2(dcm(1,2), dcm(2,2))
    };
}

}  // namespace MathUtils
