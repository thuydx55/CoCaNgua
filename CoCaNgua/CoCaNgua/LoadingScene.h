
#ifndef _CG_LOADING_SCENE_H_
#define _CG_LOADING_SCENE_H_

#define LOADING_DELAY_PER_LOOP 0.5

#include "Sprite2D.h"
#include "Scene.h"
#include "ProgressTimerSprite2D.h"

#include <iostream>

using namespace std;

class LoadingScene : Scene
{
  Sprite2D* mBackground;
  ProgressTimerSprite2D* mProgress;

  char buffer[10];

  void drawScene();
  void load();
public:
  LoadingScene(void);
  ~LoadingScene(void);

  void initSprite();

  static LoadingScene& inst();

  void loop();
};  
#endif // !_CG_LOADING_SCENE_H_


