/**
 * @file VectorMath.cpp
 * @author Michael Wrona
 * @date 2023-03-08
 * @brief Vector math functions and operator overloads.
 */

#include "LinAlg/Vector.h"
#include "LinAlg/VectorMath.h"

#include <cstddef>

namespace MathUtils { namespace LinAlg {


Vector<3> cross(const Vector<3>& v1, const Vector<3>& v2)
{
  return Vector<3>{
    (v1(1) * v2(2)) - (v1(2) * v2(1)),
    (v1(2) * v2(0)) - (v1(0) * v2(2)),
    (v1(0) * v2(1)) - (v1(1) * v2(0))
  };
}

}  // namespace LinAlg
}  // namespace MathUtils
