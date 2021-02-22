#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <vector>
#include <string>

namespace util
{

using token_type = std::vector<std::string>;

token_type tokenize(std::string const& src, std::string const& delimiter = " \t\n");

}

#endif // __UTIL_HPP__