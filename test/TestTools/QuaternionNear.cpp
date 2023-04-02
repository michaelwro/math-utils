/**
 * @file QuaternionNear.cpp
 * @author Michael Wrona
 * @date 2023-04-02
 */

#include "TestTools/QuaternionNear.h"

#include <cmath>
#include <iomanip>
#include <limits>
#include <sstream>

namespace MathUtils {
namespace TestTools {

::testing::AssertionResult QuaternionNear(const Quaternion& q1,
    const Quaternion& q2,
    const double tol)
{
    bool success = true;
    std::stringstream error_msgs;

    for (std::size_t ii = 0; ii < 4; ii++) {
        const double diff = std::abs(q1(ii) - q2(ii));

        if (diff > tol) {
            success = false;
            error_msgs << "\nElement (" << ii << ") differs by " << std::scientific << diff;
        }
    }

    if (!success) {
        return ::testing::AssertionFailure() << "Quaternions are not equal." << error_msgs.str();
    }

    return ::testing::AssertionSuccess();
}

}  // namespace TestTools
}  // namespace MathUtils
