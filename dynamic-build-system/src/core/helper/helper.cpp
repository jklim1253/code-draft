#include "core/helper/helper.hpp"

namespace core
{
static helper_base s_helper;
helper_base& helper = s_helper;

class helper_base::implement
{
  helper_base* m_parent;
public:
  implement(helper_base* _parent)
    : m_parent(_parent)
  {
  }
  ~implement()
  {
  }
  helper_base& process_command(std::string const& command)
  {
    return *m_parent;
  }
};

helper_base::helper_base()
  : impl(new implement(this))
{
}
helper_base::~helper_base()
{
  if (impl)
  {
    delete impl;
    impl = nullptr;
  }
}
helper_base& helper_base::process_command(std::string const& command)
{
  return impl->process_command(command);
}
helper_base& operator << (helper_base& self, std::string const& command)
{
  return self.process_command(command);
}

} // namespace core