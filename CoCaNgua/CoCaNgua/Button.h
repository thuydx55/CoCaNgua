#pragma once

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Sprite2D.h"

class Button
{
  GLSYNTHESIZE(Vector2, mPos, Position);
  GLSYNTHESIZE(Vector2, mAnchor, AnchorPoint);

  Sprite2D *mNormalImg, *mHoverImg, *mPressedImg, *mDisabledImg;

  bool mVisible;
  ButtonState mState;

public:
  Button(void);
  Button(Sprite2D* pNormalImg, Sprite2D* pHoverImg);
  Button(Sprite2D* pNormalImg, Sprite2D* pHoverImg, Sprite2D* pPressedImg);
  Button(Sprite2D* pNormalImg, Sprite2D* pHoverImg, Sprite2D* pPressedImg, Sprite2D* pDisabledImg);
  ~Button(void);
  
  void initWithSprite(Sprite2D* pNormalImg, Sprite2D* pHoverImg, Sprite2D* pPressedImg,
    Sprite2D* pDisabledImg);

  void drawImg();

  void setVisible(bool visible);
  bool isVisible();

  void setDisable(bool disable);
  bool isDisable();
};  

inline void Button::setVisible(bool visible)
{
  mVisible = visible;
}

inline bool Button::isVisible()
{
  return mVisible;
}

inline void Button::setDisable(bool disable)
{
  if (disable)
    mState = BUTTON_DISABLE;
  else
    mState = BUTTON_NORMAL;
}

inline bool Button::isDisable()
{
  return mState == BUTTON_DISABLE;
}

#endif // !_BUTTON_H_
