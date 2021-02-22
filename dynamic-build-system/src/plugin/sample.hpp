#ifndef __PLUGIN_SAMPLE_HPP__
#define __PLUGIN_SAMPLE_HPP__

#ifdef PLUGIN_EXPORTS
# define PLUGIN_API __declspec(dllexport)
#endif

namespace plugin
{

extern "C"
{
PLUGIN_API int hello();
}

} // namespace plugin

#endif // __PLUGIN_SAMPLE_HPP__