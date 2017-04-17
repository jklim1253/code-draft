#include <iostream>
#include <functional>
#include <list>

struct ISystem
{
    virtual int Initialize() = 0;
    virtual int Release() = 0;

    std::wstring name() const { return m_name; }
    void name(const std::wstring& in_name) { m_name = in_name; }

private :
    std::wstring m_name;
};

template<typename LogType>
struct ILogReceiver
{
    virtual void OnWrite(int type, LogType& log)
    {
        // TODO : implementation of log record.
    }
};

template<typename LogType, typename ...Elements>
LogType make_log(Elements&&... elements)
{

}

template<typename LogType>
struct ILogSender
{
    virtual void write(int type, std::wstring& log)
    {
        Logger.OnWrite(type, make_log(type, 0.0, log, this));
    }

private :
    static ILogReceiver Logger;
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
            if (sys->Initialize())
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
};

int main()
{
    Application app(new IOSystem, new MotorSystem, new VisionSystem);

    app.Initialize();


    app.Release();

    return 0;
}