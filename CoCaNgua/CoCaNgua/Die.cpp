#include "Die.h"


Die::Die(void)
{
  mIsRolling = false;
  mRollX = mRollY = mRollZ = 0;

  float _position[4] = {0, 0, 5, 1};
  float _ambient[4] = {0.2, 0.2, 0.2, 1.0};
  float _diffuse[4] = {0.7, 0.7, 0.7, 1.0};
  float _specular[4] = {1.0, 1.0, 1.0, 1.0};

  glLightfv(GL_LIGHT1, GL_POSITION, _position);
  glLightfv(GL_LIGHT1, GL_AMBIENT,  _ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  _diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, _specular);
}

void Die::drawModel()
{
  Model::drawModel();

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

      glRotatef(mRollX, 1, 0, 0);
      glRotatef(mRollY, 0, 1, 0);
      glRotatef(mRollZ, 0, 0, 1);

      draw();
    }
    glPopMatrix();
  }
  glPopMatrix();

  glDisable(GL_LIGHT1);
  glEnable(GL_LIGHT0);
}

void Die::update()
{
  double tEnlapse = mTimer.elapsed();

}

Die::~Die(void)
{
}
