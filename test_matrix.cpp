#include <gtest/gtest.h>

#include "matrix.h"

namespace {

const int defaultValue = -1;
using Matrix = hw06::Matrix<int, defaultValue>;

}

TEST(TestMatrix, Construct)
{
  Matrix matrix;

  EXPECT_EQ(matrix.size(), 0);
}

TEST(TestMatrix, NotExistCell)
{
  Matrix matrix;

  auto a = matrix[0][0];

  EXPECT_EQ(a, defaultValue);
  EXPECT_EQ(matrix.size(), 0);
}

TEST(TestMatrix, Assign)
{
  Matrix matrix;

  matrix[100][100] = 123;

  EXPECT_EQ(matrix[100][100], 123);
  EXPECT_EQ(matrix.size(), 1);
}

TEST(TestMatrix, AssignDefaultValue)
{
  Matrix matrix;

  matrix[100][100] = 123;
  matrix[100][100] = defaultValue;

  EXPECT_EQ(matrix[100][100], defaultValue);
  EXPECT_EQ(matrix.size(), 0);
}

TEST(TestMatrix, Iterator)
{
  Matrix matrix;
  matrix[100][200] = 123;
  matrix[300][400] = 456;
  matrix[500][600] = 789;

  auto iter = matrix.begin();

  EXPECT_EQ(std::get<0>(*iter), 100);
  EXPECT_EQ(std::get<1>(*iter), 200);
  EXPECT_EQ(std::get<2>(*iter), 123);

  iter = std::next(iter);

  EXPECT_EQ(std::get<0>(*iter), 300);
  EXPECT_EQ(std::get<1>(*iter), 400);
  EXPECT_EQ(std::get<2>(*iter), 456);

  iter = std::next(iter);

  EXPECT_EQ(std::get<0>(*iter), 500);
  EXPECT_EQ(std::get<1>(*iter), 600);
  EXPECT_EQ(std::get<2>(*iter), 789);

  iter = std::next(iter);

  EXPECT_EQ(iter, matrix.end());
}

TEST(TestMatrix, AssignOperator)
{
  Matrix matrix;

  ((matrix[100][100] = 314) = 0) = 217;

  EXPECT_EQ(matrix[100][100], 217);
  EXPECT_EQ(matrix.size(), 1);
}
