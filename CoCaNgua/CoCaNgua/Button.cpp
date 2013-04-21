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

Button::Button( const char* pNormalImg, const char* pHoverImg )
{
  initWithSprite(&Sprite2D(pNormalImg), &Sprite2D(pHoverImg), NULL, NULL);
}

Button::Button( const char* pNormalImg, const char* pHoverImg, const char* pPressedImg )
{
  initWithSprite(&Sprite2D(pNormalImg), &Sprite2D(pHoverImg), &Sprite2D(pPressedImg), NULL);
}

Button::Button( const char* pNormalImg, const char* pHoverImg, const char* pPressedImg, const char* pDisabledImg )
{
  initWithSprite(&Sprite2D(pNormalImg), &Sprite2D(pHoverImg), &Sprite2D(pPressedImg), &Sprite2D(pDisabledImg));
}

void Button::initWithSprite( Sprite2D* pNormalImg, Sprite2D* pHoverImg, Sprite2D* pPressedImg, Sprite2D* pDisabledImg )
{
  /*for (int i = 0; i < 4; i++)
  {
    if (mImg[i])
      delete mImg[i];
    mImg[i] = NULL;
  }*/

  mState = BUTTON_NORMAL;
  mImg[0] = pNormalImg;
  mImg[1] = pHoverImg;
  mImg[2] = pPressedImg; 
  mImg[3] = pDisabledImg;
}

void Button::drawImg()
{
  glPushMatrix();
  glTranslatef(mPos.x, mPos.y, 0);

  switch (mState)
  {
  case BUTTON_NORMAL:
    mImg[0]->drawImg();
    break;
  case BUTTON_HOVER:
    if (mImg[1])
      mImg[1]->drawImg();
    else
      mImg[0]->drawImg();
    break;
  case BUTTON_PRESSED:
    if (mImg[2])
      mImg[2]->drawImg();
    else
      mImg[0]->drawImg();
    break;
  case BUTTON_DISABLE:
    if (mImg[3])
      mImg[3]->drawImg();
    else
      mImg[0]->drawImg();
    break;
  default:
    break;
  }

  glPopMatrix();
}

Button::~Button(void)
{
  //for (int i = 0; i < 4; i++)
  //  if (!mImg[i])
  //    delete mImg[i];
}
