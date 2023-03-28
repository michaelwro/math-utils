/**
 * @file GeoCoord.cpp
 * @author Michael Wrona
 * @date 2023-03-27
 */

#include "constants.h"
#include "Geodesy/GeoCoord.h"
#include "Internal/error_msg_helpers.h"

#include <cassert>
#include <cmath>
#include <cstddef>
#include <stdexcept>

namespace MathUtils {


GeoCoord::GeoCoord()
  :m_lat_rad{},
  m_lon_rad{},
  m_alt_m{}
{}


GeoCoord::GeoCoord(const double latitude_rad, const double longitude_rad, const double altitude_m)
  :m_lat_rad{latitude_rad},
  m_lon_rad{longitude_rad},
  m_alt_m{altitude_m}
{
  assert(std::abs(m_lat_rad) <= Constants::PI_DIV2);  // within [-90, 90] deg
  assert(std::abs(m_lon_rad) <= Constants::PI);  // within [-180, 180] deg
}


GeoCoord::GeoCoord(const std::initializer_list<double> lla)
{
  const std::size_t input_size = lla.size();

  if (input_size != 3)
  {
    throw std::length_error(Internal::invalid_init_list_length_error_msg(input_size, 3));
  }

  auto vals = lla.begin();

  m_lat_rad = *(vals++);
  assert(vals != lla.end());

  m_lon_rad = *(vals++);
  assert(vals != lla.end());

  m_alt_m = *(vals++);
  assert(vals == lla.end());

  assert(std::abs(m_lat_rad) <= Constants::PI_DIV2);  // within [-90, 90] deg
  assert(std::abs(m_lon_rad) <= Constants::PI);  // within [-180, 180] deg
}


GeoCoord::GeoCoord(const GeoCoord& other)
  :m_lat_rad{other.m_lat_rad},
  m_lon_rad{other.m_lon_rad},
  m_alt_m{other.m_alt_m}
{}


GeoCoord::GeoCoord(GeoCoord&& other) noexcept
  :m_lat_rad{std::exchange(other.m_lat_rad, 0.0)},
  m_lon_rad{std::exchange(other.m_lon_rad, 0.0)},
  m_alt_m{std::exchange(other.m_alt_m, 0.0)}
{}


GeoCoord& GeoCoord::operator=(const std::initializer_list<double> lla)
{
  const std::size_t input_size = lla.size();

  if (input_size != 3)
  {
    throw std::length_error(Internal::invalid_init_list_length_error_msg(input_size, 3));
  }

  auto vals = lla.begin();

  m_lat_rad = *(vals++);
  assert(vals != lla.end());

  m_lon_rad = *(vals++);
  assert(vals != lla.end());

  m_alt_m = *(vals++);
  assert(vals == lla.end());

  assert(std::abs(m_lat_rad) <= Constants::PI_DIV2);  // within [-90, 90] deg
  assert(std::abs(m_lon_rad) <= Constants::PI);  // within [-180, 180] deg

  return *this;
}


GeoCoord& GeoCoord::operator=(const GeoCoord& other)
{
  if (&other == this)
  {
    return *this;
  }

  m_lat_rad = other.m_lat_rad;
  m_lon_rad = other.m_lon_rad;
  m_alt_m = other.m_alt_m;
  return *this;
}


GeoCoord& GeoCoord::operator=(GeoCoord&& other) noexcept
{
  if (&other == this)
  {
    return *this;
  }

  m_lat_rad = std::exchange(other.m_lat_rad, 0.0);
  m_lon_rad = std::exchange(other.m_lon_rad, 0.0);
  m_alt_m = std::exchange(other.m_alt_m, 0.0);
  return *this;
}

}  // namespace MathUtils
