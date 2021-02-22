#ifndef __BASE_SYSTEM_HPP__
#define __BASE_SYSTEM_HPP__

#include <string>

#ifdef BASE_EXPORTS
# define BASE_API __declspec(dllexport)
#else
# define BASE_API __declspec(dllimport)
#endif // BASE_EXPORTS

namespace base
{

struct BASE_API isystem
{
  virtual int Initialize() = 0;
  virtual int Release() = 0;

  isystem(std::string const& _name);
  virtual ~isystem();
  std::string name() const;

private :
  std::string m_name;
};

} // namespace

#endif // __BASE_SYSTEM_HPP__