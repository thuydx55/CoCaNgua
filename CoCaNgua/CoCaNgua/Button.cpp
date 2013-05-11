#include "Button.h"


Button::Button(void)
{
  for (int i = 0; i < 4; i++)
    mSprite[i] = NULL;
}

Button::Button( Sprite2D* pNormalSprite, Sprite2D* pHoverSprite )
{
  for (int i = 0; i < 4; i++)
    mSprite[i] = NULL;
  initWithSprite(pNormalSprite, pHoverSprite, NULL, NULL);
}

Button::Button( Sprite2D* pNormalSprite, Sprite2D* pHoverSprite, Sprite2D* pPressedSprite )
{
  for (int i = 0; i < 4; i++)
    mSprite[i] = NULL;
  initWithSprite(pNormalSprite, pHoverSprite, pPressedSprite, NULL);
}

Button::Button( Sprite2D* pNormalSprite, Sprite2D* pHoverSprite, Sprite2D* pPressedSprite, Sprite2D* pDisabledSprite )
{
  for (int i = 0; i < 4; i++)
    mSprite[i] = NULL;
  initWithSprite(pNormalSprite, pHoverSprite, pPressedSprite, pDisabledSprite);
}

Button::Button( const char* pNormalImg, const char* pHoverImg )
{
  for (int i = 0; i < 4; i++)
    mSprite[i] = NULL;
  initWithSprite(Sprite2D::create(pNormalImg), Sprite2D::create(pHoverImg), NULL, NULL);
}

Button::Button( const char* pNormalImg, const char* pHoverImg, const char* pPressedImg )
{
  for (int i = 0; i < 4; i++)
    mSprite[i] = NULL;
  initWithSprite(Sprite2D::create(pNormalImg), Sprite2D::create(pHoverImg), Sprite2D::create(pPressedImg), NULL);
}

Button::Button( const char* pNormalImg, const char* pHoverImg, const char* pPressedImg, const char* pDisabledImg )
{
  for (int i = 0; i < 4; i++)
    mSprite[i] = NULL;
  initWithSprite(Sprite2D::create(pNormalImg), Sprite2D::create(pHoverImg), Sprite2D::create(pPressedImg), Sprite2D::create(pDisabledImg));
}

Button* Button::create()
{
  Button* temp = new Button();
  return temp;
}

Button* Button::create( Sprite2D* pNormalSprite, Sprite2D* pHoverSprite )
{
  Button* temp = new Button(pNormalSprite, pHoverSprite);
  return temp;
}

Button* Button::create( Sprite2D* pNormalSprite, Sprite2D* pHoverSprite, Sprite2D* pPressedSprite )
{
  Button* temp = new Button(pNormalSprite, pHoverSprite, pPressedSprite);
  return temp;
}

Button* Button::create( Sprite2D* pNormalSprite, Sprite2D* pHoverSprite, Sprite2D* pPressedSprite, Sprite2D* pDisabledSprite )
{
  Button* temp = new Button(pNormalSprite, pHoverSprite, pPressedSprite, pDisabledSprite);
  return temp;
}

Button* Button::create( const char* pNormalImg, const char* pHoverImg )
{
  Button* temp = new Button(pNormalImg, pHoverImg);
  return temp;
}

Button* Button::create( const char* pNormalImg, const char* pHoverImg, const char* pPressedImg )
{
  Button* temp = new Button(pNormalImg, pHoverImg, pPressedImg);
  return temp;
}

Button* Button::create( const char* pNormalImg, const char* pHoverImg, const char* pPressedImg, const char* pDisabledImg )
{
  Button* temp = new Button(pNormalImg, pHoverImg, pPressedImg, pDisabledImg);
  return temp;
}

void Button::initWithSprite( Sprite2D* pNormalImg, Sprite2D* pHoverImg, Sprite2D* pPressedImg, Sprite2D* pDisabledImg )
{
  for (int i = 0; i < 4; i++)
  {
    if (mSprite[i])
      delete mSprite[i];
    mSprite[i] = NULL;
  }

  mState = BUTTON_NORMAL;
  mSprite[0] = pNormalImg;
  mSprite[1] = pHoverImg;
  mSprite[2] = pPressedImg; 
  mSprite[3] = pDisabledImg;

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

  if (mSprite[mState])
    mSprite[mState]->drawImg();
  else
    mSprite[0]->drawImg();

  //Rect bound = mSprite[mState]->boundingbox();
  //glBegin(GL_LINE_LOOP);
  //  glVertex3f(bound.getMinX(), bound.getMinY(), 1);
  //  glVertex3f(bound.getMinX(), bound.getMaxY(), 1);
  //  glVertex3f(bound.getMaxX(), bound.getMaxY(), 1);
  //  glVertex3f(bound.getMaxX(), bound.getMinY(), 1);
  //glEnd();

  glPopMatrix();
}

Rect Button::boundingbox()
{
  Rect bound = mSprite[mState]->boundingbox();
  bound.origin += mPos;
  return bound;
}

Button::~Button(void)
{
  for (int i = 0; i < 4; i++)
    if (!mSprite[i])
      delete mSprite[i];
}
