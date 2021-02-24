#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <thread>
#include <functional>
#include <vector>
#include <algorithm>
#include <list>
#include <iomanip>
#include "delegate/delegate.hpp"

int foo()
{
  std::cout << "foo without argument" << std::endl;
  return 0;
}
int foo(int n)
{
  std::cout << "foo with " << n << std::endl;
  return 0;
}
int foo2()
{
  std::cout << "foo2 without argument" << std::endl;
  return 0;
}
int foo3(int x, int y)
{
  std::cout << "foo3 with argument " << (x + y) << std::endl;
  return 0;
}
struct bar
{
  int pass()
  {
    std::cout << "bar::pass without argument" << std::endl;
    return 0;
  }
  int pass(int n)
  {
    std::cout << "bar::pass with " << n << std::endl;
    return 0;
  }
  int pass2()
  {
    std::cout << "bar::pass2 without argument" << std::endl;
    return 0;
  }
  int pass3(int x, float y)
  {
    std::cout << "bar::pass3 with argument " << (x * y) << std::endl;
    return 0;
  }
};

int main()
{
  std::cout << "hello delegate" << std::endl;

  using delegate = test::delegate_base<int()>;
  using delegate_function = test::delegate_function_base<int()>;
  using delegate_method = test::delegate_method_base<int()>;

  std::list<std::shared_ptr<delegate>> test;

  // case #1. function delegate
  //
  // if function is overloaded,
  // template argument must be specified explicitly
  //  which function would be used.
  //
  // case #1-1, overloaded function without argument
  std::shared_ptr<delegate_function> foo_without = std::make_shared<delegate_function>();
  foo_without->set<int()>(&foo);
  test.push_back(foo_without);
  // case #1-2, overloaded function with argument
  std::shared_ptr<delegate_function> foo_with = std::make_shared<delegate_function>();
  foo_with->set<int(int)>(&foo, 5);
  test.push_back(foo_with);
  // case #1-3, function without argument
  std::shared_ptr<delegate_function> foo2_without = std::make_shared<delegate_function>();
  foo2_without->set(&foo2);
  test.push_back(foo2_without);
  // case #1-4, function with argument
  std::shared_ptr<delegate_function> foo3_with = std::make_shared<delegate_function>();
  foo3_with->set(&foo3, 3, 4);
  test.push_back(foo3_with);

  // case #2. member function delegate
  //
  // if member function is overloaded,
  // template argument must be specified explicitly
  //  which member function would be used.
  //
  // owner of member function MUST be alive until delegate is called
  //
  bar gg;
  // case #2-1, overloaded member function without argument
  std::shared_ptr<delegate_method> bar_without = std::make_shared<delegate_method>();
  bar_without->set<bar, int(bar::*)()>(&gg, &bar::pass);
  test.push_back(bar_without);
  // case #2-2, overloaded member function with argument
  std::shared_ptr<delegate_method> bar_with = std::make_shared<delegate_method>();
  bar_with->set<bar, int(bar::*)(int)>(&gg, &bar::pass, 8);
  test.push_back(bar_with);
  // case #2-3, member function without argument
  std::shared_ptr<delegate_method> bar2_without = std::make_shared<delegate_method>();
  bar2_without->set(&gg, &bar::pass2);
  test.push_back(bar2_without);
  // case #2-4, member function without argument
  std::shared_ptr<delegate_method> bar3_without = std::make_shared<delegate_method>();
  bar3_without->set(&gg, &bar::pass3, 3, 1.2f);
  test.push_back(bar3_without);

  // call all delegate
  for (auto& e : test)
  {
    std::cout << std::setw(20) << std::setfill('=') << '=' << std::endl;
    e->doit();
  }

  std::cout << "press enter to exit...";
  std::cin.get();
  return 0;
}