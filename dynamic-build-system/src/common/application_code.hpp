#ifndef __COMMON_APPLICATION_CODE_HPP__
#define __COMMON_APPLICATION_CODE_HPP__

namespace ac
{
enum application_code
{
  idle = 0,
  need_to_stop,
  running,
  no_response,
};
} // namespace ac

#endif // __COMMON_APPLICATION_CODE_HPP__