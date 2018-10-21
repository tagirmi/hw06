#include <iostream>
#include <cassert>

#include "matrix.h"

int main(int argc, char const *argv[])
{
  try
  {
    hw06::Matrix<int, 0> matrix;

    for (int i = 0; i < 10; ++i) {
      matrix[i][i] = i;
      matrix[i][9 - i] = 9 - i;
    }

    std::cout << "Matrix:" << std::endl;
    for (int i = 1; i < 9; ++i ) {
      for (int j = 1; j < 9; ++j) {
        std::cout << matrix[i][j] << ' ';
      }
      std::cout << std::endl;
    }

    std::cout << "\nMatrix size:" << std::endl;
    std::cout << matrix.size() << std::endl;

    std::cout << "\nMatrix not empty cells:" << std::endl;
    for (auto cell : matrix) {
      size_t i, j;
      int v;
      std::tie(i, j, v) = cell;
      std::cout << i << j << v << std::endl;
    }
  }
  catch(const std::exception& ex)
  {
    std::cerr << ex.what() << std::endl;
  }

  return 0;
}
