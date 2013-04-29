#ifndef _CG_TIMER_H_
#define _CG_TIMER_H_

#include <ctime>

#include "gl/glut.h"

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
    Begin = glutGet(GLUT_ELAPSED_TIME);
  }
  double stop()
  {
    End = glutGet(GLUT_ELAPSED_TIME);
    return (End - Begin) / CLOCKS_PER_SEC;
  }
  double elapsed()
  {
    double tmp = glutGet(GLUT_ELAPSED_TIME);
    return (tmp - Begin) / CLOCKS_PER_SEC;
  }
};

#endif // !_CG_TIMER_H_
