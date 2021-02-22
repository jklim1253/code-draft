#ifndef __TASK_HPP__
#define __TASK_HPP__

namespace normal
{

class task
{
public:
  virtual int operator()() = 0;
};

} // namespace normal

#endif // __TASK_HPP__