#include "ProgressTimerSprite2D.h"


ProgressTimerSprite2D::ProgressTimerSprite2D(void)
{
  mPercent = 0;
}

ProgressTimerSprite2D::ProgressTimerSprite2D( const char* pFilename )
{ 
  mPercent = 0;
  loadTexture(pFilename);
}

ProgressTimerSprite2D* ProgressTimerSprite2D::create()
{
  ProgressTimerSprite2D* temp = new ProgressTimerSprite2D();
  return temp;
}

ProgressTimerSprite2D* ProgressTimerSprite2D::create( const char* pFilename )
{
  ProgressTimerSprite2D* temp = new ProgressTimerSprite2D(pFilename);
  return temp;
}

void ProgressTimerSprite2D::drawImg()
{
  glPushMatrix();
  glTranslatef(mPos.x-mAnchor.x*size.width, mPos.y-mAnchor.y*size.height, 0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glBindTexture(GL_TEXTURE_2D,texID);
  glBegin(GL_QUADS); 
  glTexCoord2f(0.0f, 0.0f); 
  glVertex2f(-size.width/2, -size.height/2); 

  glTexCoord2f(1.0f*mPercent/100, 0.0f); 
  glVertex2f(-size.width/2 + size.width*mPercent/100, -size.height/2); 

  glTexCoord2f(1.0f*mPercent/100, 1.0f); 
  glVertex2f(-size.width/2 + size.width*mPercent/100,  size.height/2); 

  glTexCoord2f(0.0f, 1.0f); 
  glVertex2f(-size.width/2,  size.height/2);
  glEnd(); 

  glDisable(GL_BLEND);
  glPopMatrix();
}


ProgressTimerSprite2D::~ProgressTimerSprite2D(void)
{
  if (texID)
  {
    glDeleteTextures( 1, &texID ); 
  } 
}
