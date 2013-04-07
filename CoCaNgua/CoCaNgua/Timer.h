
#ifndef _TIMER_H__
#define _TIMER_H__

#include <ctime>


class Timer
{
private:
  double Begin, End, Duration;

public:
  Timer() : Begin(0.0), End(0.0), Duration(0.0)
  {
  }
  void start()
  {
    Begin = clock();
  }
  double stop()
  {
    End = clock();
    return (End - Begin) / CLOCKS_PER_SEC;
  }
  double elapsed()
  {
    double tmp = clock();
    return (tmp - Begin) / CLOCKS_PER_SEC;
  }
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
