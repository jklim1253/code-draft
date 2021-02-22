#include "plugin/sample.hpp"

#include <iostream>

namespace plugin
{

int hello()
{
  std::cout << "hello plugin sample" << std::endl;
  return 0;
}

} // namespace plugin