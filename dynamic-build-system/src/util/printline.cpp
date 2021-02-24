#include "util/util.hpp"

#include <iomanip>

namespace util
{

std::ostream& printline(std::ostream& os,
                        std::streamsize width,
                        char c/*='='*/)
{
  os << std::setw(width) << std::setfill(c) << c << std::endl;
  return os;
}

} // namespace util