#include <iostream>
#include "printer.hpp"

namespace common
{

printer::printer(std::string const& _what)
  : what(_what)
{
}
printer::printer(const char* _what)
  : what(_what)
{
}
void printer::operator()() const
{
  std::cout << what << std::endl;
}
printer& printer::operator=(std::string const& _what)
{
  what = _what;
  return *this;
}
printer& printer::operator=(const char* _what)
{
  what.assign(_what);
  return *this;
}

} // namespace common