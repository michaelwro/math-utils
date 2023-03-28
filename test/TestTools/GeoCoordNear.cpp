/**
 * @file GeoCoordNear.cpp
 * @author Michael Wrona
 * @date 2023-03-28
 */

#include "TestTools/GeoCoordNear.h"

#include <cmath>
#include <iomanip>
#include <sstream>

namespace MathUtils {
namespace TestTools {

::testing::AssertionResult GeoCoordNear(const MathUtils::GeoCoord& c1,
  const MathUtils::GeoCoord& c2, const double tol)
{
  bool success = true;
  std::stringstream error_msgs;

  // compute diffs
  const double lat_diff = std::abs(c1.latitude() - c2.latitude());
  const double lon_diff = std::abs(c1.longitude() - c2.longitude());
  const double alt_diff = std::abs(c1.altitude() - c2.altitude());

  // check tolerance
  if (lat_diff > tol)
  {
    success = false;
    error_msgs << "\nLatitude differs by " << std::scientific << lat_diff;
  }

  if (lon_diff > tol)
  {
    success = false;
    error_msgs << "\nLongitude differs by " << std::scientific << lon_diff;
  }

  if (alt_diff > tol)
  {
    success = false;
    error_msgs << "\nAltitude differs by " << std::scientific << alt_diff;
  }

  if (!success)
  {
    return ::testing::AssertionFailure() << "GeoCoords are not equal." << error_msgs.str();
  }

  return ::testing::AssertionSuccess();
}

}  // namespace TestTools
}  // namespace MathUtils
