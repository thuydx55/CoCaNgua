#ifndef _CG_DIE_H_
#define _CG_DIE_H_

#include "Model.h"
#include "Timer.h"

class Die : public Model
{
  GLSYNTHESIZE(DieState, mState, State);

  bool mIsRolling;
  bool mUserIsViewed;
  Timer mTimer;

  float phi, theta;
  float phiTarget, thetaTarget;
  float phiOld, thetaOld;

public:

  Die(void);
  ~Die(void);

  virtual void drawModel();
  virtual void update();

  int rollDie();

  bool isRolling();
};  

inline bool Die::isRolling()
{
  return mIsRolling;
}

#endif // !_CG_DIE_H_
