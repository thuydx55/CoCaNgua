#include "Sky.h"


Sky::Sky(void)
{
}

void Sky::drawModel()
{
  Model::drawModel();

  //float x, y, z;
  //getCenter(x, y, z);

  glPushMatrix();
  // Move Object to coordinate origin
  //glTranslatef(-x, -y, -z);
  glPushMatrix();
  glTranslated(mPos.x - mAnchor.x*getWidth(), 
    mPos.y - mAnchor.y*getHeight(),
    mPos.z - mAnchor.z*getLength());
  float _ambient[4] = {1, 1, 1, 1};
  glLightfv(GL_LIGHT0, GL_AMBIENT,  _ambient);
  draw();
  Light::inst().setAmbient();
  glPopMatrix();
  glPopMatrix();
}


Sky::~Sky(void)
{
}
