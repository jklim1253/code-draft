#ifndef __CORE_HELPER_HPP__
#define __CORE_HELPER_HPP__

#include <string>

#ifdef CORE_HELPER_EXPORTS
# define CORE_HELPER_API __declspec(dllexport)
#else
# define CORE_HELPER_API __declspec(dllimport)
#endif // CORE_HELPER_EXPORTS

namespace core
{

// provide help contents and manage help contents.
// - what is current stage?
// - what is available help contents in each stage?
//
// stage
//   +-- functionality #1
//   +-- functionality #2
//   +-- functionality #x
//        +-- command #1
//        +-- command #2
//        +-- command #xx
//              +-- usage
//              +-- description
//              +-- affection to stage: stage will be chaged.
//                    +-- exit: default command provided by system
//              +-- example (optional)
class CORE_HELPER_API helper_base
{
public:
  helper_base();
  ~helper_base();

  helper_base& process_command(std::string const& command);

  friend helper_base& operator << (helper_base& self, std::string const& command);

private:
  class implement;
  implement* impl;
};

extern CORE_HELPER_API helper_base& helper;

} // namespace core

#endif // __CORE_HELPER_HPP__