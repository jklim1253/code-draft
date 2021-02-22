#include "util/util.hpp"
#include <Windows.h>

namespace util
{

std::string executable_path()
{
  static std::string s_exe_path;
  if (!s_exe_path.empty())
  {
    return s_exe_path;
  }

  auto mod = ::GetModuleHandleA(NULL);

  DWORD size = 256;
  char* buffer = nullptr;

  DWORD err = ERROR_SUCCESS;
  do {
    if (buffer)
    {
      delete[] buffer;
    }
    buffer = new char[size];

    size = ::GetModuleFileNameA(mod, buffer, size);
    err = ::GetLastError();

    size *= 2;

  } while (err == ERROR_INSUFFICIENT_BUFFER);

  std::string fullpath(buffer, size);

  s_exe_path = fullpath.substr(0, fullpath.find_last_of('\\'));

  return s_exe_path;
}

} // namespace util