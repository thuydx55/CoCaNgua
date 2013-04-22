#ifndef _CG_ABOUT_SCENE_H_
#define _CG_ABOUT_SCENE_H_

#include "Sprite2D.h"
#include "GameScene.h"
#include "ToggleButton.h"
#include "RadioGroup.h"

class AboutScene
{
  Sprite2D* mBackground;
  ToggleButton* mStart;
  ToggleButton* mOption;
  ToggleButton* mAbout;
  ToggleButton* mQuit;

  RadioGroup* mRadioGroup;

  void drawScene();
public:
  AboutScene(void);
  ~AboutScene(void);

  void initSprite();

  static AboutScene& inst();
  void loop();

  void processMouseBegan(int x, int y);
  void processMouseEnded(int x, int y);
  void processMousePassiveMotion(int x, int y);
};  
#endif // !_ABOUT_SCENE_H_


