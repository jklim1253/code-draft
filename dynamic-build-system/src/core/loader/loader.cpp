#include "core/loader/loader.hpp"
#include "core/loader/mod_template.hpp"
#include "common/common.hpp"
#include "util/util.hpp"

#include <Windows.h>
#include <map>

namespace core
{



#ifdef WINDOWS

struct module
{
  std::string name;
  HMODULE mod;
  hello_type entry;
};

namespace win
{

module load(std::string const& _path)
{
  module lib;
  std::string fullpath = util::executable_path();
  fullpath = fullpath + "\\" + _path;

  lib.mod = ::LoadLibraryA(fullpath.c_str());
  lib.entry = (hello_type)::GetProcAddress(lib.mod, "hello");

  return lib;
}

}
#else
#endif // WINDOWS

class loader::implement
{
  loader* m_parent;

  std::map<std::string, module> m_depot;
public:
  implement(loader* _parent)
    : m_parent(_parent)
  {
  }
  ~implement()
  {
  }
  int load(std::string const& _path, std::string const& _name)
  {
    module lib = win::load(_path);
    lib.name = _path;

    if (lib.entry == nullptr)
    {
      return ec::failed_to_load_plugin;
    }

    m_depot.insert(std::make_pair(_name, lib));
    return ec::no_error;
  }
  int unload(std::string const& _name)
  {
    return ec::not_implemented_yet;
  }
  int list() const
  {
    int index = 0;
    for (auto const& e : m_depot)
    {
      printf("[%02d] %s, %s\n",
            index+1, e.first.c_str(), e.second.name.c_str());
    }
    return ec::no_error;
  }
};

loader::loader()
  : impl(new implement(this))
{
}
loader::~loader()
{
  if (impl)
  {
    delete impl;
    impl = nullptr;
  }
}
int loader::load(std::string const& _path, std::string const& _name)
{
  return impl->load(_path, _name);
}
int loader::unload(std::string const& _name)
{
  return impl->unload(_name);
}
int loader::list() const
{
  return impl->list();
}

} // namespace core