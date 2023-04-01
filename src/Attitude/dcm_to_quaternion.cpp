/**
 * @file dcm_to_quaternion.cpp
 * @author Michael Wrona
 * @date 2023-03-26
 */

#include "Attitude/dcm_to_quaternion.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iterator>
#include <stdexcept>

namespace MathUtils {

Quaternion dcm_to_quaternion(const Matrix<3,3>& dcm)
{
    const double dcm_trace = trace(dcm);

    std::array<double, 4> q_squared_terms {
        0.25 * (1.0 + dcm_trace),
        0.25 * (1.0 + (2.0 * dcm(0,0)) - dcm_trace),
        0.25 * (1.0 + (2.0 * dcm(1,1)) - dcm_trace),
        0.25 * (1.0 + (2.0 * dcm(2,2)) - dcm_trace)
    };

    // find largest element and its index
    const auto largest_q_squared_term = std::max_element(
        q_squared_terms.cbegin(), q_squared_terms.cend()
    );

    const std::size_t largest_element = std::distance(
        q_squared_terms.cbegin(), largest_q_squared_term
    );

    // std::distance can return neg. if inputs are std::distance(end,begin)
    assert(*largest_q_squared_term >= 0);
    assert(largest_element <= 3);

    const double largest_q_term = std::sqrt(*largest_q_squared_term);

    // compute the quaternion depending on the largest element
    switch (largest_element) {
        case 0:
            return Quaternion {
                largest_q_term,
                0.25 * (dcm(1,2) - dcm(2,1)) / largest_q_term,
                0.25 * (dcm(2,0) - dcm(0,2)) / largest_q_term,
                0.25 * (dcm(0,1) - dcm(1,0)) / largest_q_term
            };
        case 1:
            return Quaternion {
                0.25 * (dcm(1,2) - dcm(2,1)) / largest_q_term,
                largest_q_term,
                0.25 * (dcm(0,1) + dcm(1,0)) / largest_q_term,
                0.25 * (dcm(2,0) + dcm(0,2)) / largest_q_term
            };
        case 2:
            return Quaternion {
                0.25 * (dcm(2,0) - dcm(0,2)) / largest_q_term,
                0.25 * (dcm(0,1) + dcm(1,0)) / largest_q_term,
                largest_q_term,
                0.25 * (dcm(1,2) + dcm(2,1)) / largest_q_term
            };
        case 3:
            return Quaternion {
                0.25 * (dcm(0,1) - dcm(1,0)) / largest_q_term,
                0.25 * (dcm(2,0) + dcm(0,2)) / largest_q_term,
                0.25 * (dcm(1,2) + dcm(2,1)) / largest_q_term,
                largest_q_term
            };
        default:
            // should never get here
            throw std::runtime_error("Error converting DCM to quaternion.");
    }
}

}  // namespace MathUtils
