#include <iostream>

int main(int argc, char const *argv[])
{
  try
  {

  }
  catch(const std::exception& ex)
  {
    std::cerr << ex.what() << std::endl;
  }

  return 0;
}
