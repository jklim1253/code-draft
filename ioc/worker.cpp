#include "worker.hpp"

namespace normal
{

worker::worker(std::shared_ptr<task> t)
  : m_need_to_stop(false)
  , m_task(t)
{
  m_thread = std::thread([&](){ loop(); });
}
worker::~worker()
{
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_need_to_stop = true;
  }
  m_cv.notify_all();

  if (m_thread.joinable())
  {
    m_thread.join();
  }
}
void worker::loop()
{
  while (true)
  {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_cv.wait_for(lock, std::chrono::microseconds(1), [=]()->bool { return m_need_to_stop; }))
    {
      break;
    }

    if (m_task)
    {
      if ((*m_task)() != 0)
      {
        break;
      }
    }
  }
}

} // namespace normal
