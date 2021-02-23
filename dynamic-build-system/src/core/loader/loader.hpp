#ifndef __CORE_LOADER_HPP__
#define __CORE_LOADER_HPP__

#include <string>

#ifdef CORE_LOADER_EXPORTS
# define CORE_LOADER_API __declspec(dllexport)
#else
# define CORE_LOADER_API __declspec(dllimport)
#endif // CORE_LOADER_EXPORTS

namespace core
{

class CORE_LOADER_API loader
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