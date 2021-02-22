#include "util.hpp"

namespace util
{

token_type tokenize(std::string const& src, std::string const& delimiter/*=" \t\n"*/)
{
  token_type tokens;
  bool need_to_ticket = true;

  for (auto const& c : src)
  {
    if (delimiter.cend() == std::find(delimiter.cbegin(), delimiter.cend(), c))
    {
      if (need_to_ticket)
      {
        tokens.push_back(std::string());
        need_to_ticket = false;
      }
      tokens.back().append(1, c);
    }
    else
    {
      need_to_ticket = true;
    }
  }

  return tokens;
}

} // namespace util