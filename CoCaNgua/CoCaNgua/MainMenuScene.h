#ifndef _CG_MAIN_MENU_H_
#define _CG_MAIN_MENU_H_

#include "Sprite2D.h"

#include "Scene.h"
#include "GameScene.h"
#include "Button.h"

class MainMenuScene : Scene
{
  Sprite2D* mBackground;
  Button* mStart;
  Button* mOption;
  Button* mAbout;
  Button* mQuit;

  void drawScene();
public:
  MainMenuScene(void);
  ~MainMenuScene(void);

  void initSprite();

  static MainMenuScene& inst();
  void loop();

  void processMouseBegan(int x, int y);
  void processMouseEnded(int x, int y);
  void processMousePassiveMotion(int x, int y);
};  
#endif // !_MAIN_MENU_H_


