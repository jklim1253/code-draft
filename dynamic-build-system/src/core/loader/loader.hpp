#ifndef __CORE_LOADER_HPP__
#define __CORE_LOADER_HPP__

#include <string>

#ifdef CORE_EXPORTS
# define CORE_API __declspec(dllexport)
#else
# define CORE_API __declspec(dllimport)
#endif // CORE_EXPORTS

namespace core
{

class CORE_API loader
{
public:
  loader();
  ~loader();

  int load(std::string const& _path, std::string const& _name = "");
  int unload(std::string const& _name);
  int list() const;

private:
  class implement;
  implement* impl;
};

} // namespace core

#endif // __CORE_LOADER_HPP__