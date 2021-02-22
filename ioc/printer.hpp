#ifndef __PRINTER_HPP__
#define __PRINTER_HPP__

#include <string>

#include "common.hpp"

namespace common
{

struct printer
{
  printer(std::string const& _what);
  printer(const char* _what);
  void operator()() const;
  printer& operator=(std::string const& _what);
  printer& operator=(const char* _what);
private:
  std::string what;
};

using atlast = atlast_base<printer, printer>;

} // namespace common

#endif // __PRINTER_HPP__