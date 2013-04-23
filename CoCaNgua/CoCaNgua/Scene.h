#ifndef _CG_SCENE_H_
#define _CG_SCENE_H_

#include "Timer.h"

class Scene
{
  Timer mTimer;

  bool mWaitIsCalled;
public:
  Scene(void);
  ~Scene(void);

  virtual void update() {};

  bool wait(float sec);
};  

inline bool Scene::wait(float sec)
{
  if (!mWaitIsCalled)
  {
    mTimer.start();
    mWaitIsCalled = true;
  }
  if (mTimer.elapsed() < sec)
    return false;
  else
  {
    mWaitIsCalled = false;
    return true;
  }
}

#endif // !_CG_SCENE_H_


