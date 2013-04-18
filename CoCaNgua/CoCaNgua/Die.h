#pragma once
#ifndef _DIE_H_
#define _DIE_H_

#include "Model.h"
#include "Timer.h"

class Die : public Model
{
  bool mIsRolling;
  Timer mTimer;

public:
  float mRollX, mRollY, mRollZ;

  Die(void);
  ~Die(void);

  virtual void drawModel();
  virtual void update();

  bool isRolling();
};  

inline bool Die::isRolling()
{
  return mIsRolling;
}

#endif // !_DIE_H_
