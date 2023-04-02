/**
 * @file GeoCoordNear.cpp
 * @author Michael Wrona
 * @date 2023-03-28
 */

#include "TestTools/Euler321Near.h"

#include <cmath>
#include <iomanip>
#include <sstream>

namespace MathUtils {
namespace TestTools {

::testing::AssertionResult Euler321Near(const Euler321& e1,
    const Euler321& e2, const double tol)
{
    bool success = true;
    std::stringstream error_msgs;

    // compute diffs
    const double yaw_diff = std::abs(e1.yaw() - e2.yaw());
    const double pitch_diff = std::abs(e1.pitch() - e2.pitch());
    const double roll_diff = std::abs(e1.roll() - e2.roll());

    // check tolerance
    if (yaw_diff > tol) {
        success = false;
        error_msgs << "\nYaw differs by " << std::scientific << yaw_diff;
    }

    if (pitch_diff > tol) {
        success = false;
        error_msgs << "\nPitch differs by " << std::scientific << pitch_diff;
    }

    if (roll_diff > tol) {
        success = false;
        error_msgs << "\nRoll differs by " << std::scientific << roll_diff;
    }

    if (!success) {
        return ::testing::AssertionFailure() << "Euler321 are not equal." << error_msgs.str();
    }

    return ::testing::AssertionSuccess();
}

}  // namespace TestTools
}  // namespace MathUtils
