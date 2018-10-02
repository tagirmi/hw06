#include <iostream>
#include <cassert>

#include "matrix.h"

void test_matrix()
{
  hw06::Matrix<int, -1> matrix;
  assert(matrix.size() == 0);

  auto a = matrix[0][0];
  assert(a == -1);
  assert(matrix.size() == 0);

  matrix[100][100] = 314;
  assert(matrix[100][100] == 314);
  assert(matrix.size() == 1);

  matrix[100][100] = -1;
  assert(matrix[100][100] == -1);
  assert(matrix.size() == 0);
}

int main(int argc, char const *argv[])
{
  try
  {
    test_matrix();


  }
  catch(const std::exception& ex)
  {
    std::cerr << ex.what() << std::endl;
  }

  return 0;
}
