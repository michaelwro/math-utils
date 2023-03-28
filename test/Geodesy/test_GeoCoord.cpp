/**
 * @file test_GeoCoord.cpp
 * @author Michael Wrona
 * @date 2023-03-27
 */

#include "Geodesy/GeoCoord.h"
#include "TestTools/GeoCoordNear.h"

#include <gtest/gtest.h>
#include <string>

using MathUtils::GeoCoord;
using MathUtils::TestTools::GeoCoordNear;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-geocoord.xml");

class GeoCoordTest : public ::testing::Test
{
public:
  GeoCoordTest()
    :c1{-0.1, 0.2, 34.0},
    c1_lat{-0.1},
    c1_lon{0.2},
    c1_alt{34.0},
    c2{0.2, 0.3, 56.0}
  {}
protected:
  void SetUp() override {}
  void TearDown() override {}

  const GeoCoord c1;
  const double c1_lat;
  const double c1_lon;
  const double c1_alt;
  const GeoCoord c2;
private:
};

// ====================================================================================================================
TEST_F(GeoCoordTest, DefaultConstruct)
{
  GeoCoord gc;

  EXPECT_DOUBLE_EQ(gc.latitude(), 0.0);
  EXPECT_DOUBLE_EQ(gc.longitude(), 0.0);
  EXPECT_DOUBLE_EQ(gc.altitude(), 0.0);
}

// ====================================================================================================================
TEST_F(GeoCoordTest, ThreeArgConstruct)
{
  GeoCoord gc(0.1, 0.2, 56);

  EXPECT_DOUBLE_EQ(gc.latitude(), 0.1);
  EXPECT_DOUBLE_EQ(gc.longitude(), 0.2);
  EXPECT_DOUBLE_EQ(gc.altitude(), 56);
}

// ====================================================================================================================
TEST(GeoCoordDeathTest, ThreeArgConstructAssertsInvalidLatitude)
{
  EXPECT_DEBUG_DEATH({
    GeoCoord gc(-12, 0.3, 123);
  }, "");
}

// ====================================================================================================================
TEST(GeoCoordDeathTest, ThreeArgConstructAssertsInvalidLongitude)
{
  EXPECT_DEBUG_DEATH({
    GeoCoord gc(0.3, 12, 123);
  }, "");
}

// ====================================================================================================================
TEST_F(GeoCoordTest, ListInitConstructor)
{
  GeoCoord gc ({-0.2, -0.4, 68.0});
}

// ====================================================================================================================
TEST_F(GeoCoordTest, ListInitConstructorThrowsInvalidSize)
{
  EXPECT_THROW({
    GeoCoord gc ({-0.2, -0.4, 68.0, 123.0});
  }, std::length_error);
}

// ====================================================================================================================
TEST_F(GeoCoordTest, CopyConstruct)
{
  GeoCoord gc_copy(c1);

  EXPECT_TRUE(GeoCoordNear(gc_copy, c1));
}

// ====================================================================================================================
TEST_F(GeoCoordTest, MoveConstruct)
{
  GeoCoord gc(0.1, 0.2, 345.0);

  GeoCoord gc_new(std::move(gc));

  EXPECT_DOUBLE_EQ(gc_new.latitude(), 0.1);
  EXPECT_DOUBLE_EQ(gc_new.longitude(), 0.2);
  EXPECT_DOUBLE_EQ(gc_new.altitude(), 345.0);
}

// ====================================================================================================================
TEST_F(GeoCoordTest, ListInitAssign)
{
  GeoCoord gc;
  gc = {-0.2, -0.4, 68.0};

  EXPECT_DOUBLE_EQ(gc.latitude(), -0.2);
  EXPECT_DOUBLE_EQ(gc.longitude(), -0.4);
  EXPECT_DOUBLE_EQ(gc.altitude(), 68.0);
}

// ====================================================================================================================
TEST_F(GeoCoordTest, ListInitAssignThrowsInvalidSize)
{
  GeoCoord gc;
  std::initializer_list<double> vals = {-0.5, 0.5};
  EXPECT_THROW({
    gc = vals;
  }, std::length_error);
}

// ====================================================================================================================
TEST_F(GeoCoordTest, CopyAssign)
{
  GeoCoord gc_copy;
  gc_copy = c1;

  EXPECT_TRUE(GeoCoordNear(gc_copy, c1));
}

// ====================================================================================================================
TEST_F(GeoCoordTest, MoveAssign)
{
  GeoCoord gc(0.1, 0.2, 345.0);

  GeoCoord gc_new;
  gc_new = std::move(gc);

  EXPECT_DOUBLE_EQ(gc_new.latitude(), 0.1);
  EXPECT_DOUBLE_EQ(gc_new.longitude(), 0.2);
  EXPECT_DOUBLE_EQ(gc_new.altitude(), 345.0);
}

// ====================================================================================================================
int main(int argc, char** argv)
{
  ::testing::GTEST_FLAG(output) = std::string("xml:") + test_reports_file;
  ::testing::GTEST_FLAG(death_test_style) = "threadsafe";

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

}  // namespace
