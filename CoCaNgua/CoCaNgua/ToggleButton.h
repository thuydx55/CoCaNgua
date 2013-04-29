#ifndef _CG_TOGGLE_BUTTON_H_
#define _CG_TOGGLE_BUTTON_H_

#include "Sprite2D.h"
#include "Constants.h"

class ToggleButton
{
  GLSYNTHESIZE(Vector2, mPos, Position);
  GLSYNTHESIZE(Vector2, mAnchor, AnchorPoint);
  GLSYNTHESIZE(ToggleState, mState, ToggleState)

  Sprite2D* mImg[3]; // On,Off,Disable

  bool mVisible;

public:
  ToggleButton(void);
  ToggleButton(Sprite2D* pOnImg, Sprite2D* pOffImg);
  ToggleButton(Sprite2D* pOnImg, Sprite2D* pOffImg, Sprite2D* pDisabledImg);
  
  ToggleButton(const char* pOnImg, const char* pOffImg);
  ToggleButton(const char* pOnImg, const char* pOffImg, const char* pDisabledImg);
  ~ToggleButton(void);
  
  void initWithSprite(Sprite2D* pOnImg, Sprite2D* pOffImg, Sprite2D* pDisabledImg);

  void drawImg();

  void setVisible(bool visible);
  bool isVisible();

  void setDisable(bool disable);
  bool isDisable();

  void click();

  Rect boundingbox();
};  

inline void ToggleButton::setVisible(bool visible)
{
  mVisible = visible;
}

inline bool ToggleButton::isVisible()
{
  return mVisible;
}

inline void ToggleButton::setDisable(bool disable)
{
  if (disable)
    mState = TOGGLE_DISABLE;
  else
    mState = TOGGLE_OFF;
}

inline bool ToggleButton::isDisable()
{
  return mState == TOGGLE_DISABLE;
}

#endif // !_CG_TOGGLEBUTTON_H_
