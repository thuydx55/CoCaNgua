#include "Button.h"


Button::Button(void)
{
}

Button::Button( Sprite2D* pNormalImg, Sprite2D* pHoverImg )
{
  initWithSprite(pNormalImg, pHoverImg, NULL, NULL);
}

Button::Button( Sprite2D* pNormalImg, Sprite2D* pHoverImg, Sprite2D* pPressedImg )
{
  initWithSprite(pNormalImg, pHoverImg, pPressedImg, NULL);
}

Button::Button( Sprite2D* pNormalImg, Sprite2D* pHoverImg, Sprite2D* pPressedImg, Sprite2D* pDisabledImg )
{
  initWithSprite(pNormalImg, pHoverImg, pPressedImg, pDisabledImg);
}

void Button::initWithSprite( Sprite2D* pNormalImg, Sprite2D* pHoverImg, Sprite2D* pPressedImg, Sprite2D* pDisabledImg )
{
  mState = BUTTON_NORMAL;
  mNormalImg = pNormalImg;
  mHoverImg = pHoverImg;
  mPressedImg = pPressedImg; 
  mDisabledImg = pDisabledImg;
}

void Button::drawImg()
{
  glPushMatrix();
  glTranslatef(mPos.x, mPos.y, 0);

  switch (mState)
  {
  case BUTTON_NORMAL:
    mNormalImg->drawImg();
    break;
  case BUTTON_HOVER:
    if (mHoverImg)
      mHoverImg->drawImg();
    else
      mNormalImg->drawImg();
    break;
  case BUTTON_PRESSED:
    if (mPressedImg)
      mPressedImg->drawImg();
    else
      mNormalImg->drawImg();
    break;
  case BUTTON_DISABLE:
    if (mDisabledImg)
      mDisabledImg->drawImg();
    else
      mNormalImg->drawImg();
    break;
  default:
    break;
  }

  glPopMatrix();
}

Button::~Button(void)
{
}
