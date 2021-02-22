#include "timer.hpp"

namespace normal
{

timer::timer(std::chrono::seconds const& duration)
  : m_st(std::chrono::steady_clock::now())
  , m_duration(duration)
  , is_completed(false)
{
}
timer::~timer()
{
}
int timer::async_wait(std::function<void()> _todo)
{
  m_todo = _todo;
  if (!is_completed)
  {
    // immediately return, do not block current thread.
  }

  return 0; // mean nothing.
}
int timer::wait(std::function<void()> _todo)
{
  m_todo = _todo;
  while (!is_completed)
  {
    // block current thread.
  }

  return 0; // expired
}
int timer::operator()()
{
  if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - m_st).count() > std::chrono::duration_cast<std::chrono::nanoseconds>(m_duration).count())
  {
    is_completed = true;

    if (m_todo)
    {
      m_todo();
    }

    return 1; // stop task
  }

  return 0;
}

} // namespace normal