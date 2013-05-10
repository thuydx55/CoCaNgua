#include "Rock.h"

GLfloat floorPlaneRock[4] = {
  0, 1, 0, 0
};


Rock::Rock(void)
{
  mShadow = true;
}

Rock::Rock( const Rock* other )
{
  memcpy(this, other, sizeof(*other));
}

void Rock::drawModel()
{
  Model::drawModel();

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
      glRotatef(mAngleRotate, mRotateAxis.x, mRotateAxis.y, mRotateAxis.z);

      draw();
    }
    glPopMatrix();
  }
  glPopMatrix();

  glPushMatrix();
  //glTranslatef(x, y/2, z);
  if(mShadow)
  {
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL, 0x4, 0x4);
    glStencilMask(0x4);
    glStencilOp(GL_KEEP, GL_KEEP, GL_INVERT);

    //float fP[4] = {floorPlane[0], floorPlane[1], floorPlane[2], floorPlane[3] + mPos.y };
    shadowMatrix(floorShadow, floorPlaneRock, Light::inst().getPosition());

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);  /* Force the 50% black. */
    glColor4f(0.0, 0.0, 0.0, 0.5);

    glPushMatrix();
    {
      //glTranslatef(-mAnchor.x*getWidth(), -mAnchor.y*getHeight(), -mAnchor.z*getLength());
      /* Project the shadow. */
      glMultMatrixf((GLfloat *) floorShadow);
      glPushMatrix();
      {
        glTranslated(mPos.x, mPos.y, mPos.z);
        //glTranslatef(0, 8.01, 0);
        draw();
      }
      glPopMatrix(); 
    }

    glPopMatrix();

    glDisable(GL_BLEND);
    glDisable(GL_STENCIL_TEST);
    glEnable(GL_LIGHTING);
  }
  glPopMatrix();
}

Rock::~Rock(void)
{
}
