#ifndef _CG_PROGRESS_TIMER_SPRITE2D_H_
#define _CG_PROGRESS_TIMER_SPRITE2D_H_

#include "Sprite2D.h"

class ProgressTimerSprite2D : public Sprite2D
{
  GLSYNTHESIZE(int, mPercent, Percent);
public:
  ProgressTimerSprite2D(void);
  ProgressTimerSprite2D(const char* pFilename);
  ~ProgressTimerSprite2D(void);

  static ProgressTimerSprite2D* create();
  static ProgressTimerSprite2D* create(const char* pFilename);

  virtual void drawImg();

};  
#endif // !_CG_PROGRESS_TIMER_SPRITE2D_H_


