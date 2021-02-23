#include "core/loader/loader.hpp"
#include "core/loader/mod_template.hpp"
#include "common/common.hpp"
#include "util/util.hpp"

#include <Windows.h>
#include <map>
#include <memory>
#include <iomanip>
#include <iostream>

namespace core
{

const char* const plugin_ordinal = "hello";

#ifdef WINDOWS

template<class Signature>
struct module_base
{
  typedef Signature module_entry_type;

  std::string name;
  HMODULE mod;
  Signature entry;

  module_base()
    : mod(nullptr)
    , entry(nullptr)
  {
  }
  ~module_base()
  {
    entry = nullptr;
    if (mod)
    {
      ::FreeLibrary(mod);
      mod = nullptr;
    }
  }
};

using plugin_module = module_base<plugin_entry_type>;
using plugin_memory = std::shared_ptr<plugin_module>;

namespace win
{

int load(std::string const& _path, plugin_memory& _lib)
{
  std::string fullpath = util::executable_path();
  fullpath = fullpath + "\\" + _path;

  _lib->mod = ::LoadLibraryA(fullpath.c_str());
  if (_lib->mod == nullptr)
  {
    return ec::module_not_found;
  }
  _lib->entry = (plugin_module::module_entry_type)
                ::GetProcAddress(_lib->mod, plugin_ordinal);
  if (_lib->entry == nullptr)
  {
    return ec::module_format_is_not_supported;
  }

  return ec::no_error;
}

} // namespace win
#else
#endif // WINDOWS

class loader::implement
{
  loader* m_parent;

  std::map<std::string, plugin_memory> m_depot;
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
    plugin_memory lib = std::make_shared<plugin_module>();
    
    if (win::load(_path, lib) != ec::no_error)
    {
      return ec::failed_to_load_plugin;
    }
    lib->name = _path;

    m_depot.insert(std::make_pair(_name, lib));
    return ec::no_error;
  }
  int unload(std::string const& _name)
  {
    // TODO: if plugin is in use, stop using plugin
    m_depot.erase(_name);
    return ec::no_error;
  }
  int list() const
  {
    util::printline(std::cout, 20, '=');
    if (m_depot.empty())
    {
      std::cout << "empty" << std::endl;
    }
    else
    {
      int index = 0;
      for (auto const& e : m_depot)
      {
        printf("[%02d] %s, %s\n",
              index+1, e.first.c_str(), e.second->name.c_str());
      }
    }
    util::printline(std::cout, 2, '=');
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