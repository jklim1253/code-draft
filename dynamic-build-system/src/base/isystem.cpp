#include "base/isystem.hpp"

namespace base
{

isystem::isystem(std::string const& _name)
  : m_name(_name)
{
}
isystem::~isystem()
{
}
std::string isystem::name() const
{
  return m_name;
}

} // namespace base