#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <list>
#include <deque>

enum error_code
{
    no_error = 0,

    CRITICAL_ERROR = 0x40000000,
};

namespace util
{
    typedef std::list<std::wstring> token_type;

    token_type tokenize(const std::wstring& src, const std::wstring& delimiter = L" \t\n")
    {
        token_type tokens;
        bool need_to_ticket = true;
        std::for_each(src.cbegin(), src.cend(), [&](std::wstring::value_type c) {
                if (delimiter.cend() == std::find(delimiter.cbegin(), delimiter.cend(), c))
                {
                    if (need_to_ticket)
                    {
                        tokens.push_back(std::wstring());
                        need_to_ticket = false;
                    }
                    tokens.back().append(c, 1);
                }
                else
                {
                    need_to_ticket = true;
                }
            });
    }
}

struct ISystem
{
    virtual int Initialize() = 0;
    virtual int Release() = 0;

    std::wstring name() const { return m_name; }
    void name(const std::wstring& in_name) { m_name = in_name; }

private :
    std::wstring m_name;
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
    return LogType(elements...);
}

template<typename LogType>
struct ILogSender
{
    virtual void write(int type, const std::wstring& log)
    {
        Logger.OnWrite(make_log(type, 0.0, log, this));
    }

private :
    static ILogReceiver<LogType> Logger;
};

struct LogData
{
    int type;
    double time;
    std::wstring msg;
    ILogSender<LogData>* sender;
};

class IOSystem : public ISystem
{
public :
    IOSystem() { name(L"DIO-System"); }
    // Inherited via ISystem
    virtual int Initialize() override
    {
        return 0;
    }
    virtual int Release() override
    {
        return 0;
    }
};

class MotorSystem : public ISystem
{
public :
    MotorSystem() { name(L"Motor-System"); }
    // Inherited via ISystem
    virtual int Initialize() override
    {
        return 0;
    }
    virtual int Release() override
    {
        return 0;
    }
};

class VisionSystem : public ISystem
{
public :
    VisionSystem() { name(L"Vision-System"); }
    // Inherited via ISystem
    virtual int Initialize() override
    {
        return 0;
    }
    virtual int Release() override
    {
        return 0;
    }
};

class TeachingSystem : public ISystem
{
public :
    TeachingSystem() { name(L"Teaching-System"); }
    // Inherited via ISystem
    virtual int Initialize() override
    {
        return 0;
    }
    virtual int Release() override
    {
        return 0;
    }
};

class Application : public ISystem, public ILogSender<LogData>
{
public :
    template<typename First, typename ...Others>
    Application(First&& sys, Others&&... others)
    {
        _addsystem(sys, others...);
    }

private :
    template<typename First, typename ...Others>
    void _addsystem(First&& sys, Others&&... others)
    {
        systems.push_back(sys);
        _addsystem(others...);
    }
    template<typename Last>
    void _addsystem(Last&& sys)
    {
        systems.push_back(sys);
    }
private :
    std::list<ISystem*> systems;

public :
    // Inherited via ISystem
    virtual int Initialize() override
    {
        write(0, L"start to initialize all systems");
        for (auto sys : systems)
        {
            if (sys->Initialize() == no_error)
            {
                std::wcout << sys->name().c_str() << L" initialized successfully." << std::endl;
            }
            else
            {
                std::wcout << sys->name().c_str() << L" initialization failed." << std::endl;
            }
        }
        std::wcout << L"initialization all systems finished" << std::endl;
        return 0;
    }
    virtual int Release() override
    {
        std::wcout << L"start to release all systems" << std::endl;
        for (auto sys : systems)
        {
            if (sys->Release())
            {
                std::wcout << sys->name().c_str() << L" released successfully." << std::endl;
            }
            else
            {
                std::wcout << sys->name().c_str() << L" releasing failed." << std::endl;
            }
        }
        std::wcout << L"releasing all systems finished" << std::endl;
        return 0;
    }

    int parse_command_line(const std::wstring& command)
    {
        util::token_type tokens = util::tokenize(command);
        return 0;
    }

    void error_process(int error_code)
    {
        if ((error_code & CRITICAL_ERROR) == CRITICAL_ERROR)
        {
            write(0, L"[CERR] xxx");
        }
        else
        {
            write(0, L"[ERR] xxx");
        }
    }
};

int main()
{
    Application app(new IOSystem, new MotorSystem, new VisionSystem);

    app.Initialize();

    std::wstring command;
    while (std::getline(std::wcin, command) && command != L"quit")
    {
        int ret = app.parse_command_line(command);
        if (ret != no_error)
        {
            app.error_process(ret);
        }
    }

    app.Release();

    return 0;
}
