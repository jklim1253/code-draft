#ifndef __CORE_IOSYSTEM_HPP__
#define __CORE_IOSYSTEM_HPP__

#include "base/isystem.hpp"

#ifdef CORE_EXPORTS
# define CORE_API __declspec(dllexport)
#else
# define CORE_API __declspec(dllimport)
#endif // CORE_EXPORTS

namespace core
{

class CORE_API iosystem
  : public base::isystem
{
public :
  iosystem();
  virtual int Initialize() override;
  virtual int Release() override;
};

} // namespace core

#endif // __CORE_IOSYSTEM_HPP__