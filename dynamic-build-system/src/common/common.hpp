#ifndef __COMMON_COMMON_HPP__
#define __COMMON_COMMON_HPP__

#include "common/error_code.hpp"
#include "common/application_code.hpp"

#ifdef COMMON_EXPORTS
# define COMMON_API __declspec(dllexport)
#else
# define COMMON_API __declspec(dllimport)
#endif // COMMON_EXPORTS

namespace common
{

extern COMMON_API int version();

} // namespace common

#endif // __COMMON_COMMON_HPP__