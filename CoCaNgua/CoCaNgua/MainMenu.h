#ifndef _CG_MAIN_MENU_H_
#define _CG_MAIN_MENU_H_

#include "Sprite2D.h"
#include "Game.h"
#include "Button.h"

class MainMenu
{
  Sprite2D* mBackground;
  Button* mStart;
  Button* mOption;
  Button* mAbout;
  Button* mQuit;

  void drawScene();
public:
  MainMenu(void);
  ~MainMenu(void);

  void initSprite();

  static MainMenu& inst();
  void loop();

  void processMouseBegan(int x, int y);
  void processMouseEnded(int x, int y);
  void processMousePassiveMotion(int x, int y);
};  
#endif // !_MAIN_MENU_H_


