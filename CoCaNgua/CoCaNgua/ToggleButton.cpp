#include "ToggleButton.h"


ToggleButton::ToggleButton(void)
{
  for (int i = 0; i < 3; i++)
    mImg[i] = NULL;
}

ToggleButton::ToggleButton( Sprite2D* pOnImg, Sprite2D* pOffImg )
{
  for (int i = 0; i < 3; i++)
    mImg[i] = NULL;
  initWithSprite(pOnImg, pOffImg, NULL);
}

ToggleButton::ToggleButton( Sprite2D* pOnImg, Sprite2D* pOffImg, Sprite2D* pDisabledImg )
{
  for (int i = 0; i < 3; i++)
    mImg[i] = NULL;
  initWithSprite(pOnImg, pOffImg, pDisabledImg);
}

ToggleButton::ToggleButton( const char* pOnImg, const char* pOffImg )
{
  for (int i = 0; i < 3; i++)
    mImg[i] = NULL;
  initWithSprite(Sprite2D::create(pOnImg), Sprite2D::create(pOffImg), NULL);
}

ToggleButton::ToggleButton( const char* pOnImg, const char* pOffImg, const char* pDisabledImg )
{
  for (int i = 0; i < 3; i++)
    mImg[i] = NULL;
  initWithSprite(Sprite2D::create(pOnImg), Sprite2D::create(pOffImg), Sprite2D::create(pDisabledImg));
}

void ToggleButton::initWithSprite( Sprite2D* pOnImg, Sprite2D* pOffImg, Sprite2D* pDisabledImg )
{
  for (int i = 0; i < 3; i++)
  {
    if (mImg[i])
      delete mImg[i];
    mImg[i] = NULL;
  }

  mState = TOGGLE_OFF;
  mImg[0] = pOnImg;
  mImg[1] = pOffImg;
  mImg[2] = pDisabledImg;

  /*for (int i = 0; i < 4; i++)
  {
    if (mImg == NULL)
      continue;
    mImg[i]->setPosition(Vector2(0, 0));
    mImg[i]->setAnchorPoint(Vector2(0, 0));
  }*/
}

void ToggleButton::drawImg()
{
  glPushMatrix();
  glTranslatef(mPos.x-mAnchor.x*mImg[mState]->boundingBox().size.width,
               mPos.y-mAnchor.x*mImg[mState]->boundingBox().size.height, 0);

  if (mImg[mState])
    mImg[mState]->drawImg();
  else
    mImg[0]->drawImg();

  /*Rect bound = mImg[mState]->boundingBox();
  glBegin(GL_LINE_LOOP);
    glVertex3f(bound.getMinX(), bound.getMinY(), 1);
    glVertex3f(bound.getMinX(), bound.getMaxY(), 1);
    glVertex3f(bound.getMaxX(), bound.getMaxY(), 1);
    glVertex3f(bound.getMaxX(), bound.getMinY(), 1);
  glEnd();*/

  glPopMatrix();
}

void ToggleButton::click()
{
  if (mState != TOGGLE_DISABLE)
  {
    if (mState == TOGGLE_ON)
      mState = TOGGLE_OFF;
    else
      mState = TOGGLE_ON;
  }
}

Rect ToggleButton::boundingbox()
{
  Rect bound = mImg[mState]->boundingBox();
  bound.origin += mPos;
  bound.origin.x -= mAnchor.x*mImg[mState]->boundingBox().size.width;
  bound.origin.y -= mAnchor.x*mImg[mState]->boundingBox().size.height;

  return bound;
}

ToggleButton::~ToggleButton(void)
{
  for (int i = 0; i < 4; i++)
    if (!mImg[i])
      delete mImg[i];
}
