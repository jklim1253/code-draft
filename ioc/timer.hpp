#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <chrono>
#include <functional>

#include "task.hpp"

namespace normal
{

class timer
  : public task
{
public:
  timer(std::chrono::seconds const& duration);
  ~timer();

  int async_wait(std::function<void()> _todo);
  int wait(std::function<void()> _todo);
  virtual int operator()() override;

private:
  std::chrono::steady_clock::time_point m_st;
  std::chrono::seconds m_duration;
  bool is_completed;
  std::function<void()> m_todo;
};

} // namespace normal

#endif // __TIMER_HPP__