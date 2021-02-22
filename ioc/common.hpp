#ifndef __COMMON_HPP__
#define __COMMON_HPP__

namespace common
{

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

} // namespace common

#endif // __COMMON_HPP__