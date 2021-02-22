#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <list>
#include <vector>
#include <deque>
#include <mutex>

#include "util/util.hpp"

namespace ec
{
enum error_code
{
  no_error = 0,
  not_implemented_yet,

  // system
  failed_to_initialize,
  failed_to_release,

  critical_error = 0x40000000,
};
} // namespace ec

namespace ac
{
enum application_code
{
  idle = 0,
  need_to_stop,
  running,
  no_response,
};
} // namespace ac

struct ISystem
{
  virtual int Initialize() = 0;
  virtual int Release() = 0;

  ISystem(std::string const& _name)
    : m_name(_name)
  {
  }
  virtual ~ISystem()
  {
  }
  std::string name() const
  {
    return m_name;
  }

private :
  std::string m_name;
};

struct critical_section
{
};

template<typename LogType>
struct ILogReceiver
{
  virtual void OnWrite(LogType log)
  {
    // TODO : implementation of log record.
    depot.push_back(log);
  }

protected :
  std::deque<LogType> depot;
  mutable critical_section cs;
};

template<typename LogType, typename ...Elements>
LogType make_log(Elements&&... elements)
{
  return LogType{elements...};
}

template<typename LogType>
struct ILogSender
{
  virtual void write(int type, const std::string& log)
  {
    Logger.OnWrite(make_log<LogType>(type, 0.0, log, this));
  }

private :
  static ILogReceiver<LogType> Logger;
};
template<typename LogType>
ILogReceiver<LogType> ILogSender<LogType>::Logger;

struct LogData
{
  int type;
  double time;
  std::string msg;
  ILogSender<LogData>* sender;
};

class IOSystem
  : public ISystem
{
public :
  IOSystem()
    : ISystem("IOSystem")
  {
  }
  // Inherited via ISystem
  virtual int Initialize() override
  {
    return ec::not_implemented_yet;
  }
  virtual int Release() override
  {
    return ec::not_implemented_yet;
  }
};

class MotorSystem
  : public ISystem
{
public :
  MotorSystem()
    : ISystem("MotorSystem")
  {
  }
  // Inherited via ISystem
  virtual int Initialize() override
  {
    return ec::not_implemented_yet;
  }
  virtual int Release() override
  {
    return ec::not_implemented_yet;
  }
};

class VisionSystem
  : public ISystem
{
public :
  VisionSystem()
    : ISystem("Vision-System")
  {
  }
  // Inherited via ISystem
  virtual int Initialize() override
  {
    return ec::not_implemented_yet;
  }
  virtual int Release() override
  {
    return ec::not_implemented_yet;
  }
};

class TeachingSystem
  : public ISystem
{
public :
  TeachingSystem()
    : ISystem("Teaching-System")
  {
  }
  // Inherited via ISystem
  virtual int Initialize() override
  {
    return ec::not_implemented_yet;
  }
  virtual int Release() override
  {
    return ec::not_implemented_yet;
  }
};

class Application
  : public ISystem
  , public ILogSender<LogData>
{
public :
  template<typename First, typename ...Others>
  Application(First&& sys, Others&&... others)
    : ISystem("Application")
    , m_state(ac::idle)
  {
    _addsystem(sys, others...);
  }

private :
  template<typename First, typename ...Others>
  void _addsystem(First&& first, Others&&... others)
  {
    systems.push_back(first);
    _addsystem(others...);
  }
  template<typename Last>
  void _addsystem(Last&& last)
  {
    systems.push_back(last);
  }
private :
  std::list<ISystem*> systems;
  int m_state;

public :
  // Inherited via ISystem
  virtual int Initialize() override
  {
    write(0, "start to initialize all systems");
    int fault_count = 0;
    for (auto sys : systems)
    {
      if (sys->Initialize() == ec::no_error)
      {
        std::cout << sys->name().c_str() << " initialized successfully." << std::endl;
      }
      else
      {
        std::cout << sys->name().c_str() << " initialization failed." << std::endl;
        ++fault_count;
      }
    }
    std::cout << "initialization all systems finished" << std::endl;

    if (fault_count != 0)
    {
      return ec::failed_to_initialize;
    }
    return ec::no_error;
  }
  virtual int Release() override
  {
    std::cout << "start to release all systems" << std::endl;
    int fault_count = 0;
    for (auto sys : systems)
    {
      if (sys->Release() == ec::no_error)
      {
        std::cout << sys->name().c_str() << " released successfully." << std::endl;
      }
      else
      {
        std::cout << sys->name().c_str() << " releasing failed." << std::endl;
        ++fault_count;
      }
    }
    std::cout << "releasing all systems finished" << std::endl;

    if (fault_count != 0)
    {
      return ec::failed_to_release;
    }
    return ec::no_error;
  }

  int parse_command_line(const std::string& command)
  {
    util::token_type tokens = util::tokenize(command);
    if (tokens.size() == 1 && tokens[0] == "quit")
    {
      m_state = ac::need_to_stop;
    }
    return 0;
  }

  void error_process(int error_code)
  {
    if ((error_code & ec::critical_error) == ec::critical_error)
    {
      write(0, "[CERR] xxx");
    }
    else
    {
      write(0, "[ERR] xxx");
    }
  }
  int state() const
  {
    return m_state;
  }
};

int main()
{
  Application app(new IOSystem, new MotorSystem, new VisionSystem);

  app.Initialize();

  std::string command;
  while (ac::need_to_stop != app.state())
  {
    std::cout << "command:> ";
    std::getline(std::cin, command);

    int ret = app.parse_command_line(command);
    if (ret != ec::no_error)
    {
      app.error_process(ret);
    }
  }

  app.Release();

#ifdef _DEBUG
  std::cout << "presss enter to exit...";
  std::cin.get();
#endif
  return 0;
}
