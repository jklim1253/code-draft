#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <vector>
#include <string>
#include <iostream>

#ifdef UTIL_EXPORTS
# define UTIL_API __declspec(dllexport)
#else
# define UTIL_API __declspec(dllimport)
#endif

namespace util
{

using token_type = std::vector<std::string>;

UTIL_API token_type tokenize(std::string const& src,
                             std::string const& delimiter = " \t\n");

UTIL_API std::string executable_path();

UTIL_API std::ostream& printline(std::ostream& os,
                                 std::streamsize width,
                                 char c = '=');
}

#endif // __UTIL_HPP__