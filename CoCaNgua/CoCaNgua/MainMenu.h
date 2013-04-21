#ifndef _CG_MAIN_MENU_H_
#define _CG_MAIN_MENU_H_

#include "Sprite2D.h"
#include "Game.h"
#include "Button.h"

class MainMenu
{
  Sprite2D* mBackground;
  Button* mStart;

  void drawScene();
public:
  MainMenu(void);
  ~MainMenu(void);

  static MainMenu& inst();
  void loop();
};  
#endif // !_MAIN_MENU_H_


