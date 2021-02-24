#include <string>
#include <iostream>

template<class T>
struct id_holder
{
  typedef long id_type;
protected:
  id_holder()
    : m_id(s_id++)
  {
  }
  id_holder(id_holder const& o)
    : m_id(s_id++)
  {
  }
  id_holder(id_holder && o)
    : m_id(o.m_id)
  {
    o.m_id = -1;
  }
  id_holder& operator = (id_holder const& o)
  {
    return *this;
  }
  id_holder& operator = (id_holder && o)
  {
    this->m_id = o.m_id;
    return *this;
  }
public:
  id_type id() const
  {
    return m_id;
  }
private:
  id_type m_id;
  static id_type s_id;
};
template<class T>
typename id_holder<T>::id_type id_holder<T>::s_id = 0L;

struct object_base
  : private id_holder<object_base>
{
  typedef id_holder<object_base>::id_type id_type;
protected:
  id_type uid() const
  {
    return id_holder<object_base>::id();
  }
};

template<class T>
struct object
  : public id_holder<T>
  , public object_base
{
  typedef int class_type;
  typedef object_base::id_type uid_type;
  typedef id_holder<T>::id_type id_type;
protected:
  object(class_type _ct)
    : m_ct(_ct)
  {
  }
public:
  class_type type() const
  {
    return m_ct;
  }
  uid_type uid() const
  {
    return object_base::uid();
  }

private:
  class_type m_ct;
};

namespace cc
{
enum class_code : long
{
  application = 1L,
  library,
};
} // namespace class_code

template<class T>
struct name_holder
{
  name_holder(std::string const& _name)
    : m_name(_name)
  {
  }
  std::string name() const
  {
    return m_name;
  }
private:
  std::string m_name;
};

class App
  : public object<App>
  , public name_holder<App>
{
public:
  App(std::string const& _name = "App")
    : object(cc::application)
    , name_holder(_name)
  {
  }
  virtual ~App()
  {
  }
  // safe to quit
  int quit()
  {
    std::cout << "request quit" << std::endl;
    return 0;
  }
  // force to quit
  int exit(int retcode)
  {
    std::cout << "request exit with " << retcode << std::endl;
    return 0;
  }
};

class Library
  : public object<Library>
  , public name_holder<Library>
{
public:
  Library(std::string const& _name = "Library")
    : object(cc::application)
    , name_holder(_name)
  {
  }
  virtual ~Library()
  {
  }
  int load(std::string const& path)
  {
    std::cout << '[' << name() << "] request load with " << path << std::endl;
    return 0;
  }
  int unload()
  {
    std::cout << '[' << name() << "] request unload" << std::endl;
    return 0;
  }
  int process(std::string const& command)
  {
    std::cout << '[' << name() << "] request process with " << command << std::endl;
    return 0;
  }
};
