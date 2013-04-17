#include "Die.h"


Die::Die(void)
{
  float _ambient[4] = {0.7, 0.7, 0.7, 0.7};
  glLightfv(GL_LIGHT1, GL_AMBIENT,  _ambient);
}

void Die::drawModel()
{
  glDisable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  float x, y, z;
  getCenter(x, y, z);

  glPushMatrix();
  {
    // Move Object to coordinate origin
    glTranslatef(-x, -y, -z);
    glPushMatrix();
    {
      glTranslated(mPos.x - mAnchor.x*getWidth(), 
        mPos.y - mAnchor.y*getHeight(),
        mPos.z - mAnchor.z*getLength());

      draw();
    }
    glPopMatrix();
  }
  glPopMatrix();

  glDisable(GL_LIGHT1);
  glEnable(GL_LIGHT0);
}

Die::~Die(void)
{
}
