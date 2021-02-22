#ifndef __CORE_LOADER_MOD_TEMPLATE_HPP__
#define __CORE_LOADER_MOD_TEMPLATE_HPP__

#ifdef CORE_EXPORTS
# define CORE_API __declspec(dllexport)
#else
# define CORE_API __declspec(dllimport)
#endif // CORE_EXPORTS

namespace core
{

extern "C"
{
typedef int (*hello_type)();
CORE_API int hello();
}

} // namespace core

#endif // __CORE_LOADER_MOD_TEMPLATE_HPP__