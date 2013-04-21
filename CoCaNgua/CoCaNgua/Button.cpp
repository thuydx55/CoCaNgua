#include "Button.h"


Button::Button(void)
{
  for (int i = 0; i < 4; i++)
    mImg[i] = NULL;
}

Button::Button( Sprite2D* pNormalImg, Sprite2D* pHoverImg )
{
  for (int i = 0; i < 4; i++)
    mImg[i] = NULL;
  initWithSprite(pNormalImg, pHoverImg, NULL, NULL);
}

Button::Button( Sprite2D* pNormalImg, Sprite2D* pHoverImg, Sprite2D* pPressedImg )
{
  for (int i = 0; i < 4; i++)
    mImg[i] = NULL;
  initWithSprite(pNormalImg, pHoverImg, pPressedImg, NULL);
}

Button::Button( Sprite2D* pNormalImg, Sprite2D* pHoverImg, Sprite2D* pPressedImg, Sprite2D* pDisabledImg )
{
  for (int i = 0; i < 4; i++)
    mImg[i] = NULL;
  initWithSprite(pNormalImg, pHoverImg, pPressedImg, pDisabledImg);
}

Button::Button( const char* pNormalImg, const char* pHoverImg )
{
  for (int i = 0; i < 4; i++)
    mImg[i] = NULL;
  initWithSprite(Sprite2D::create(pNormalImg), Sprite2D::create(pHoverImg), NULL, NULL);
}

Button::Button( const char* pNormalImg, const char* pHoverImg, const char* pPressedImg )
{
  for (int i = 0; i < 4; i++)
    mImg[i] = NULL;
  initWithSprite(Sprite2D::create(pNormalImg), Sprite2D::create(pHoverImg), Sprite2D::create(pPressedImg), NULL);
}

Button::Button( const char* pNormalImg, const char* pHoverImg, const char* pPressedImg, const char* pDisabledImg )
{
  for (int i = 0; i < 4; i++)
    mImg[i] = NULL;
  initWithSprite(Sprite2D::create(pNormalImg), Sprite2D::create(pHoverImg), Sprite2D::create(pPressedImg), Sprite2D::create(pDisabledImg));
}

void Button::initWithSprite( Sprite2D* pNormalImg, Sprite2D* pHoverImg, Sprite2D* pPressedImg, Sprite2D* pDisabledImg )
{
  for (int i = 0; i < 4; i++)
  {
    if (mImg[i])
      delete mImg[i];
    mImg[i] = NULL;
  }

  mState = BUTTON_NORMAL;
  mImg[0] = pNormalImg;
  mImg[1] = pHoverImg;
  mImg[2] = pPressedImg; 
  mImg[3] = pDisabledImg;

  /*for (int i = 0; i < 4; i++)
  {
    if (mImg == NULL)
      continue;
    mImg[i]->setPosition(Vector2(0, 0));
    mImg[i]->setAnchorPoint(Vector2(0, 0));
  }*/
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
  /*Rect bound = mImg[mState]->boundingBox();
  glBegin(GL_LINE_LOOP);
    glVertex3f(bound.getMinX(), bound.getMinY(), 1);
    glVertex3f(bound.getMinX(), bound.getMaxY(), 1);
    glVertex3f(bound.getMaxX(), bound.getMaxY(), 1);
    glVertex3f(bound.getMaxX(), bound.getMinY(), 1);
  glEnd();*/

  glPopMatrix();
}

Rect Button::boundingbox()
{
  Rect bound = mImg[mState]->boundingBox();
  bound.origin += mPos;
  return bound;
}

Button::~Button(void)
{
  //for (int i = 0; i < 4; i++)
  //  if (!mImg[i])
  //    delete mImg[i];
}
