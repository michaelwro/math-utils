/**
 * @file dcmToEuler321.hpp
 * @author michaelwro
 * @date 2025-04-06
 */

#pragma once

#include "math/Euler321.hpp"
#include "math/Matrix3.hpp"

namespace math {

/**
 * @brief Convert a direction cosine matrix to Euler321 angles. Equation 3.34 from
 * "Analytical Mechanics of Aerospace Systems" (Schaub).
 *
 * @param dcm The DCM.
 * @return [rad] Corresponding Euler321 angles.
 */
[[nodiscard]] Euler321 dcmToEuler321(const Matrix3& dcm);

}  // namespace math
