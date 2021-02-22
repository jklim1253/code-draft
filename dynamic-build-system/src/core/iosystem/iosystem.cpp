#include "core/iosystem/iosystem.hpp"
#include "common/common.hpp"

namespace core
{

iosystem::iosystem()
  : isystem("IOSystem")
{
}
// Inherited via isystem
int iosystem::Initialize()
{
  return ec::not_implemented_yet;
}
int iosystem::Release()
{
  return ec::not_implemented_yet;
}

} // namespace core