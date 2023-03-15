/**
 * @file test_Vector.cpp
 * @author Michael Wrona
 * @date 2023-03-08
 * @brief Vector unit tests.
 */

#include "LinAlg/Vector.h"

#include <cmath>
#include <gtest/gtest.h>
#include <initializer_list>
#include <string>
#include <utility>

using MathUtils::Vector;

namespace {

const std::string test_reports_file = std::string("TESTRESULTS-LinAlg-Vector.xml");

// ====================================================================================================================
TEST(LinAlg_Vector, DefaultConstructorZerosElements)
{
  Vector<3> vec;

  EXPECT_DOUBLE_EQ(vec(0), 0.0);
  EXPECT_DOUBLE_EQ(vec(1), 0.0);
  EXPECT_DOUBLE_EQ(vec(2), 0.0);
}

// ====================================================================================================================
TEST(LinAlg_Vector, InitListConstruction)
{
  Vector<4> vec({1, 2, 3, 4});

  EXPECT_DOUBLE_EQ(vec(0), 1);
  EXPECT_DOUBLE_EQ(vec(1), 2);
  EXPECT_DOUBLE_EQ(vec(2), 3);
  EXPECT_DOUBLE_EQ(vec(3), 4);
}

// ====================================================================================================================
TEST(LinAlg_Vector, AssertsInvalidLengthInitializerList)
{
  std::initializer_list<double> vals = {1, 2, 3, 4};

  ASSERT_DEBUG_DEATH({
    Vector<3> vec(vals);
    }, "");
}

// ====================================================================================================================
TEST(LinAlg_Vector, CopyConstruction)
{
  Vector<2> vec {-1, -2};
  Vector<2> vec2(vec);

  EXPECT_DOUBLE_EQ(vec2(0), -1);
  EXPECT_DOUBLE_EQ(vec2(1), -2);
}

// ====================================================================================================================
TEST(LinAlg_Vector, CopyAssigns)
{
  Vector<3> vec({1, 3, 2});
  Vector<3> vec2;

  vec2 = vec;

  EXPECT_DOUBLE_EQ(vec2(0), 1);
  EXPECT_DOUBLE_EQ(vec2(1), 3);
  EXPECT_DOUBLE_EQ(vec2(2), 2);
}

// ====================================================================================================================
TEST(LinAlg_Vector, MoveAssigns)
{
  Vector<4> vec {4, 3, 2, 1};
  Vector<4> vec2;

  vec2 = std::move(vec);

  EXPECT_DOUBLE_EQ(vec2(0), 4);
  EXPECT_DOUBLE_EQ(vec2(1), 3);
  EXPECT_DOUBLE_EQ(vec2(2), 2);
  EXPECT_DOUBLE_EQ(vec2(3), 1);
}

// ====================================================================================================================
TEST(LinAlg_Vector, InitializerListAssigns)
{
  Vector<4> vec;

  vec = {1, 3, 2, 4};

  EXPECT_DOUBLE_EQ(vec(0), 1);
  EXPECT_DOUBLE_EQ(vec(1), 3);
  EXPECT_DOUBLE_EQ(vec(2), 2);
  EXPECT_DOUBLE_EQ(vec(3), 4);
}

// ====================================================================================================================
TEST(LinAlg_Vector, InitListAssignAssertsIncompatibleSize)
{
  Vector<3> vec;
  std::initializer_list<double> four_vals = {1, 3, 2, 4};

  EXPECT_DEBUG_DEATH({
    vec = four_vals;
  }, "");
}

// ====================================================================================================================
TEST(LinAlg_Vector, ParenthesisAccessorModifiesValues)
{
  Vector<3> vec({1, 2, 3});

  vec(0) = 4;
  vec(1) = 5;
  vec(2) = 6;

  EXPECT_DOUBLE_EQ(vec(0), 4);
  EXPECT_DOUBLE_EQ(vec(1), 5);
  EXPECT_DOUBLE_EQ(vec(2), 6);
}

// ====================================================================================================================
TEST(LinAlg_Vector, SizeGetterReturnsCorrectLength)
{
  Vector<4> vec {1, 2, 3, 4};

  EXPECT_EQ(vec.size(), 4);
}

// ====================================================================================================================
TEST(LinAlg_Vector, FillsVector)
{
  Vector<3> vec {1, 1, 1};

  vec.fill(123.0);

  EXPECT_DOUBLE_EQ(vec(0), 123);
  EXPECT_DOUBLE_EQ(vec(1), 123);
  EXPECT_DOUBLE_EQ(vec(2), 123);
}

// ====================================================================================================================
TEST(LinAlg_Vector, ComputesMagnitude)
{
  Vector<3> vec {1, 1, 1};

  double mag = vec.magnitude();

  EXPECT_DOUBLE_EQ(
    mag, std::sqrt((vec(0)*vec(0)) + (vec(1)*vec(1)) + (vec(2)*vec(2)))
  );
}

// ====================================================================================================================
TEST(LinAlg_Vector, Normalizes)
{
  const double val0 = 3;
  const double val1 = 2;
  const double val2 = 1;
  Vector<3> vec({val0, val1, val2});

  double mag = std::sqrt((vec(0)*vec(0)) + (vec(1)*vec(1)) + (vec(2)*vec(2)));

  vec.normalize();

  EXPECT_DOUBLE_EQ(vec(0), val0 / mag);
  EXPECT_DOUBLE_EQ(vec(1), val1 / mag);
  EXPECT_DOUBLE_EQ(vec(2), val2 / mag);
}

// ====================================================================================================================
TEST(LinAlg_Vector, SumsElements)
{
  Vector<3> vec({5, 4, 3});

  EXPECT_DOUBLE_EQ(vec.sum(), 12);
}

// ====================================================================================================================
TEST(LinAlg_Vector, ScalarAddInPlace)
{
  Vector<3> vec({4, 5, 6});

  vec += 3.0;

  EXPECT_DOUBLE_EQ(vec(0), 7.0);
  EXPECT_DOUBLE_EQ(vec(1), 8.0);
  EXPECT_DOUBLE_EQ(vec(2), 9.0);
}

// ====================================================================================================================
TEST(LinAlg_Vector, VectorAddInPlace)
{
  Vector<3> vec1({1, 2, 3});
  Vector<3> vec2({4, 5, 6});

  vec1 += vec2;

  EXPECT_DOUBLE_EQ(vec1(0), 5.0);
  EXPECT_DOUBLE_EQ(vec1(1), 7.0);
  EXPECT_DOUBLE_EQ(vec1(2), 9.0);
}

// ====================================================================================================================
TEST(LinAlg_Vector, ScalarSubtractInPlace)
{
  Vector<3> vec({4, 5, 6});

  vec -= 3.0;

  EXPECT_DOUBLE_EQ(vec(0), 1.0);
  EXPECT_DOUBLE_EQ(vec(1), 2.0);
  EXPECT_DOUBLE_EQ(vec(2), 3.0);
}

// ====================================================================================================================
TEST(LinAlg_Vector, VectorSubtractInPlace)
{
  Vector<3> vec1({1, 2, 3});
  Vector<3> vec2({4, 5, 6});

  vec1 -= vec2;

  EXPECT_DOUBLE_EQ(vec1(0), -3.0);
  EXPECT_DOUBLE_EQ(vec1(1), -3.0);
  EXPECT_DOUBLE_EQ(vec1(2), -3.0);
}

// ====================================================================================================================
TEST(LinAlg_Vector, ScalarMultiplyInPlace)
{
  Vector<3> vec({1, 2, 3});

  vec *= -2.0;

  EXPECT_DOUBLE_EQ(vec(0), -2.0);
  EXPECT_DOUBLE_EQ(vec(1), -4.0);
  EXPECT_DOUBLE_EQ(vec(2), -6.0);
}

// ====================================================================================================================
TEST(LinAlg_Vector, ScalarDivideInPlace)
{
  Vector<3> vec({6, 8, 10});

  vec /= 2.0;

  EXPECT_DOUBLE_EQ(vec(0), 3.0);
  EXPECT_DOUBLE_EQ(vec(1), 4.0);
  EXPECT_DOUBLE_EQ(vec(2), 5.0);
}

// ====================================================================================================================
TEST(LinAlg_Vector, ScalarDivideInPlaceAssertSmallNumber)
{
  Vector<3> vec({6, 8, 10});

  EXPECT_DEBUG_DEATH({
    vec /= 1e-15;
  }, "");
}

// ====================================================================================================================
TEST(LinAlg_Vector, Negate)
{
  Vector<3> vec({6, -8, 10});

  vec.negate();

  EXPECT_DOUBLE_EQ(vec(0), -6);
  EXPECT_DOUBLE_EQ(vec(1), 8);
  EXPECT_DOUBLE_EQ(vec(2), -10);
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
