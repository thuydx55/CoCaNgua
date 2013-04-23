#ifndef _CG_PROGRESS_TIMER_H_
#define _CG_PROGRESS_TIMER_H_

#include "Sprite2D.h"

class ProgressTimer
{
public:
  ProgressTimer(void);
  ~ProgressTimer(void);

  static ProgressTimer* create(Sprite2D* sp);
};  
#endif // !_CG_PROGRESS_TIMER_H_


