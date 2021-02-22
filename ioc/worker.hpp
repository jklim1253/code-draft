#ifndef __WORKER_HPP__
#define __WORKER_HPP__

#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

#include "task.hpp"

namespace normal
{

class worker
{
public:
  worker(std::shared_ptr<task> t);
  ~worker();

private:
  void loop();

private:
  std::thread m_thread;
  std::mutex m_mutex;
  std::condition_variable m_cv;
  bool m_need_to_stop;
  std::shared_ptr<task> m_task;
};
} // namespace normal

#endif // __WORKER_HPP__