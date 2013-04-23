
#ifndef _LOADING_SCENE_H_
#define _LOADING_SCENE_H_

#define LOADING_DELAY_PER_LOOP 0.5

#include "Scene.h"
#include "Sprite2D.h"
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
#endif // !_LOADING_SCENE_H_


