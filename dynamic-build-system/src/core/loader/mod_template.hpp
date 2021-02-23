#ifndef __CORE_LOADER_MOD_TEMPLATE_HPP__
#define __CORE_LOADER_MOD_TEMPLATE_HPP__

#ifdef CORE_LOADER_EXPORTS
# define CORE_API __declspec(dllexport)
#else
# define CORE_API __declspec(dllimport)
#endif

namespace core
{

extern "C"
{
typedef int (*plugin_entry_type)();
extern CORE_API const char* const plugin_ordinal; // hello
}

} // namespace core

#endif // __CORE_LOADER_MOD_TEMPLATE_HPP__