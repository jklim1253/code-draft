#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <string>

namespace common
{

struct printer
{
  printer(std::string const& _what)
    : what(_what)
  {
  }
  printer(const char* _what)
    : what(_what)
  {
  }
  void operator()() const
  {
    std::cout << what << std::endl;
  }
  printer& operator=(std::string const& _what)
  {
    what = _what;
    return *this;
  }
  printer& operator=(const char* _what)
  {
    what.assign(_what);
    return *this;
  }
private:
  std::string what;
};

template<class Init, class Release>
struct atlast_base
{
  atlast_base(Init _init, Release _release)
    : init(std::move(_init))
    , release(std::move(_release))
  {
    init();
  }
  ~atlast_base()
  {
    release();
  }
private:
  Init init;
  Release release;
};

using atlast = atlast_base<printer, printer>;

} // namespace common

namespace normal
{
class task
{
public:
  virtual int operator()() = 0;
};

class timer
  : public task
{
public:
  timer(std::chrono::seconds const& duration)
    : m_st(std::chrono::steady_clock::now())
    , m_duration(duration)
    , is_completed(false)
  {
  }
  int async_wait(std::function<void()> _todo)
  {
    m_todo = _todo;
    if (!is_completed)
    {
      // immediately return, do not block current thread.
    }

    return 0; // mean nothing.
  }
  int wait(std::function<void()> _todo)
  {
    m_todo = _todo;
    while (!is_completed)
    {
      // block current thread.
    }

    return 0; // expired
  }
  int operator()() override
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
private:
  std::chrono::steady_clock::time_point m_st;
  std::chrono::seconds m_duration;
  bool is_completed;
  std::function<void()> m_todo;
};

class worker
{
public:
  worker(std::shared_ptr<task> t)
    : m_need_to_stop(false)
    , m_task(t)
  {
    m_thread = std::thread([&](){ loop(); });
  }
  ~worker()
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
protected:
private:
  void loop()
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
private:
  std::thread m_thread;
  std::mutex m_mutex;
  std::condition_variable m_cv;
  bool m_need_to_stop;
  std::shared_ptr<task> m_task;
};
} // namespace normal

void foo()
{
  std::cout << "world tour\n";
}

int main()
{
  // normal
  // * worker have task(timer).
  //    - worker dose not know about detail of task(timer).
  //    - worker use task interface.
  //    - specific task(timer) must follow task interface.
  //    - specific task(timer) can provide additional interface(wait).
  {
    common::atlast block
    (
      "[normal sync wait] start",
      "[normal sync wait] finish"
    );
    std::shared_ptr<normal::timer> t = std::make_shared<normal::timer>(std::chrono::seconds(5));
    normal::worker sample(t);
    t->wait(&foo); // block current thread until timer is expired.
    std::cout << "hello world" << std::endl;
  }
  {
    common::atlast block
    (
      common::printer("[normal async wait] start"),
      common::printer("[normal async wait] finish")
    );
    std::shared_ptr<normal::timer> t = std::make_shared<normal::timer>(std::chrono::seconds(5));
    normal::worker sample(t);
    t->async_wait(&foo); // block current thread until timer is expired.
    std::cout << "hello world" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5)); // force to wait for async task to be executed
  }

  std::cout << "press any key to exit...";
  std::cin.get();
  return 0;
}