/**
 * @file MatrixNear.h
 * @author Michael Wrona
 * @date 2023-03-19
 */

#ifndef MATHUTILS_GTEST_TOOLS_MATRIX_NEAR_H_
#define MATHUTILS_GTEST_TOOLS_MATRIX_NEAR_H_

#include "LinAlg/Matrix.h"

#include <cmath>
#include <gtest/gtest.h>
#include <iomanip>
#include <sstream>

namespace MathUtils {
namespace TestTools {

/**
 * @brief Check two MathUtils::Matrix for equality.
 *
 * @param mat1 First matrix.
 * @param mat2 Second matrix.
 * @param tol Absolute tolerance for each element. Defaults to 1e-14.
 * @returns Test assertion success or failure.
 *
 * @ref https://stackoverflow.com/a/7121785
 */

template<std::size_t N, std::size_t M>
::testing::AssertionResult MatrixNear(const MathUtils::Matrix<N,M>& mat1,
    const MathUtils::Matrix<N,M>& mat2, const double tol=1e-14)
{
    bool success = true;
    std::stringstream error_msgs;

    for (std::size_t ii = 0; ii < N; ii++) {
        for (std::size_t jj = 0; jj < M; jj++) {
            const double diff = std::abs(mat1(ii, jj) - mat2(ii, jj));

            if (diff > tol) {
                success = false;
                error_msgs << "\nElement (" << ii << "," << jj << ") differs by " << std::scientific << diff;
            }
        }
    }

    if (!success) {
        return ::testing::AssertionFailure() << "Matrices are not equal." << error_msgs.str();
    }

    return ::testing::AssertionSuccess();
}

}  // namespace TestTools
}  // namespace MathUtils

#endif  // MATHUTILS_GTEST_TOOLS_MATRIX_NEAR_H_
