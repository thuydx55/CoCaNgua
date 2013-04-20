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
  mNormalImg = pNormalImg;
  mHoverImg = pHoverImg;
  mPressedImg = pPressedImg; 
  mDisabledImg = pDisabledImg;
}

void Button::drawImg()
{

}

Button::~Button(void)
{
}
