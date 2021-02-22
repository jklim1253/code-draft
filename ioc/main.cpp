#include <iostream>

#include "printer.hpp"
#include "timer.hpp"
#include "worker.hpp"

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
  // * worker - task interface - specific task

  // wait: block caller thread.
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

  // async_wait: does not block caller thread.
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