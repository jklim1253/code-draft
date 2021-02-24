#ifndef __DELEGATE_HPP__
#define __DELEGATE_HPP__

#include <functional>
#ifdef _DEBUG
#include <iostream>
#endif

namespace test
{

template<class Signature>
struct delegate_base
{
  virtual int doit() = 0;

  std::function<Signature> m_func;
};

template<class Signature>
struct delegate_function_base
  : public delegate_base<Signature>
{
  template<class Function, class...Arguments>
  int set(Function func, Arguments...arguments)
  {
#ifdef _DEBUG
    std::cout << "function type: " << typeid(func).name() << std::endl;
    std::cout << "function: " << func << std::endl;
#endif
    m_func = [=](){
#ifdef _DEBUG
      std::cout << "in lambda of function" << std::endl;
#endif
      return (*func)(arguments...);
    };
    return 0;
  }
  int doit() override
  {
    return m_func();
  }
};

template<class Signature>
struct delegate_method_base
  : public delegate_base<Signature>
{
  template<class Instance, class Method, class...Arguments>
  int set(Instance* instance, Method method, Arguments...arguments)
  {
#ifdef _DEBUG
    std::cout << "method type: " << typeid(method).name() << std::endl;
    std::cout << "method: " << method << std::endl;
#endif
    m_func = [=](){
#ifdef _DEBUG
      std::cout << "in lambda of method" << std::endl;
#endif
      return (instance->*method)(arguments...);
    };
    return 0;
  }
  int doit() override
  {
    return m_func();
  }
};

} // namespace test

#endif // __DELEGATE_HPP__