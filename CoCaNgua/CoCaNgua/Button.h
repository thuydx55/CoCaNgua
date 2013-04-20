#pragma once

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Sprite2D.h"

class Button
{
  Sprite2D *mNormalImg, *mHoverImg, *mPressedImg, *mDisabledImg;

  bool mVisible;

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
};  

inline void Button::setVisible(bool visible)
{
  mVisible = visible;
}

inline bool Button::isVisible()
{
  return mVisible;
}

#endif // !_BUTTON_H_
