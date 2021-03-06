#ifndef __COMMON_ERROR_CODE_HPP__
#define __COMMON_ERROR_CODE_HPP__

namespace ec
{
enum error_code
{
  no_error = 0,
  not_implemented_yet,

  // system
  failed_to_initialize,
  failed_to_release,
  failed_to_load_plugin,

  // loader
  module_not_found,
  module_format_is_not_supported,

  critical_error = 0x40000000,
};
} // namespace ec

#endif // __COMMON_ERROR_CODE_HPP__