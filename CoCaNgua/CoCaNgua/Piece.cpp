#include "Piece.h"

int id = 0;
GLfloat floorPlane[4] = {
  0, 1, 0, 0
};

Piece::Piece(void)
{
  mHighlight = false;
  mShadow = true;

  mHighlightThickness =  1;
  mHighlightColor[0] = 0.8;
  mHighlightColor[1] = 0.8;
  mHighlightColor[2] = 0.0;
  mHighlightColor[3] = 0.5;

  mState = MODEL_IDLE;
}

Piece::Piece( const Piece* other )
{
  memcpy(this, other, sizeof(*other));
}

void Piece::drawModel()
{
  float x, y, z;
  getCenter(x, y, z);

  glPushMatrix();
  {
    // Move Object to coordinate origin
    glTranslatef(-x, -y, -z);

    float scaleX = (getWidth() + mHighlightThickness)/getWidth();
    float scaleY = (getHeight() + mHighlightThickness)/getHeight();
    float scaleZ = (getLength() + mHighlightThickness)/getLength();

    glPushMatrix();
    {
      glTranslated(mPos.x - mAnchor.x*getWidth(), 
        mPos.y - mAnchor.y*getHeight(),
        mPos.z - mAnchor.z*getLength());
      glRotatef(mAngle, mRotate.x, mRotate.y, mRotate.z);


      if(mHighlight)
      {
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS, 0x0, 0x4);
        glStencilMask(0x4);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
      }

      draw();

      if (mHighlight)
      {
        glStencilMask(0xffffffff);
        glClearStencil(0x4);

        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glEnable(GL_STENCIL_TEST);
        glColor4f(mHighlightColor[0], mHighlightColor[1], mHighlightColor[2], mHighlightColor[3]);  /* 30% sorta yellow. */
        glStencilFunc(GL_EQUAL, 0x4, 0x4);
        glStencilMask(0x4);
        glStencilOp(GL_KEEP, GL_KEEP, GL_INVERT);

        glPushMatrix();
        glScalef(scaleX, scaleY, scaleZ);
        //glTranslated(0, -getHeight()*(scaleY-1)/2, 0);
        draw();
        glPopMatrix();

        glDisable(GL_BLEND);
        glDisable(GL_STENCIL_TEST);
        glEnable(GL_LIGHTING);
      }
    }

    if(mShadow)
    {
      glEnable(GL_STENCIL_TEST);
      glStencilFunc(GL_EQUAL, 0x4, 0x4);
      glStencilMask(0x4);
      glStencilOp(GL_KEEP, GL_KEEP, GL_INVERT);


      shadowMatrix(floorShadow, floorPlane, Light::inst().getPosition());

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDisable(GL_LIGHTING);  /* Force the 50% black. */
      glColor4f(0.0, 0.0, 0.0, 0.5);

      glPushMatrix();
      {
        /* Project the shadow. */
        glMultMatrixf((GLfloat *) floorShadow);
        glPushMatrix();
        {
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
  glPopMatrix();

  update();
}

// shadow
void Piece::shadow(bool value)
{
  mShadow = value;
}

bool Piece::isShadow()
{
  return mShadow;
}

void Piece::shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4])
{
  GLfloat dot;

  /* Find dot product between light position vector and ground plane normal. */
  dot = groundplane[0] * lightpos[0] +
    groundplane[1] * lightpos[1] +
    groundplane[2] * lightpos[2] +
    groundplane[3] * lightpos[3];

  shadowMat[0][0] = dot - lightpos[0] * groundplane[0];
  shadowMat[1][0] = 0.f - lightpos[0] * groundplane[1];
  shadowMat[2][0] = 0.f - lightpos[0] * groundplane[2];
  shadowMat[3][0] = 0.f - lightpos[0] * groundplane[3];

  shadowMat[0][1] = 0.f - lightpos[1] * groundplane[0];
  shadowMat[1][1] = dot - lightpos[1] * groundplane[1];
  shadowMat[2][1] = 0.f - lightpos[1] * groundplane[2];
  shadowMat[3][1] = 0.f - lightpos[1] * groundplane[3];

  shadowMat[0][2] = 0.f - lightpos[2] * groundplane[0];
  shadowMat[1][2] = 0.f - lightpos[2] * groundplane[1];
  shadowMat[2][2] = dot - lightpos[2] * groundplane[2];
  shadowMat[3][2] = 0.f - lightpos[2] * groundplane[3];

  shadowMat[0][3] = 0.f - lightpos[3] * groundplane[0];
  shadowMat[1][3] = 0.f - lightpos[3] * groundplane[1];
  shadowMat[2][3] = 0.f - lightpos[3] * groundplane[2];
  shadowMat[3][3] = dot - lightpos[3] * groundplane[3];

}

void Piece::highlight(bool value)
{
  mHighlight = value;
}

bool Piece::isHighlight()
{
  return mHighlight;
}

void Piece::setHighLightColor( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
  mHighlightColor[0] = red;
  mHighlightColor[1] = green;
  mHighlightColor[2] = blue;
  mHighlightColor[3] = alpha;
}

void Piece::jumpTo( vector<Vector3> pTarget, MoveState pMoveState )
{
  if (mState == MODEL_IDLE)
  {
    mState = MODEL_JUMP;

    mStartPos = getPosition();
    mTarget = pTarget;

    if (pMoveState == MOVE_NORMAL || pMoveState == MOVE_HOME_INSIDE || pMoveState == MOVE_HOME_OUTSIDE)
    {
      Vector3 delta = (pTarget[0] - mStartPos)/4;
      mJumps.push_back(delta.magnitude());
      mDuration.push_back(delta.magnitude() * 0.25);
      mHeight = 5;

      for (int i = 1; i < pTarget.size(); i++)
      {
        delta = (pTarget[i] - pTarget[i-1])/4;
        mJumps.push_back(delta.magnitude());
        mDuration.push_back(delta.magnitude() * 0.25);
      }
    }
    else if (pMoveState == MOVE_ATTACK || pMoveState == MOVE_START || pMoveState == MOVE_START_ATTACK)
    {
      mHeight = 10;
      mJumps.push_back(1);
      mDuration.push_back(0.5);
    }

    mTimer.start();
  }
}

void Piece::update()
{
  double tEnlapse = mTimer.elapsed();

  if (mState == MODEL_JUMP)
  {
    Vector3 target = mTarget[id];

    float frac = fmodf((tEnlapse / mDuration[id]) * mJumps[id], 1);
    float y = (mHeight * 4 * frac * (1 - frac));
    y += target.y * tEnlapse;
    float x = (target - mStartPos).x * (tEnlapse / mDuration[id]);
    float z = (target - mStartPos).z * (tEnlapse / mDuration[id]);

    setPosition(Vector3(mStartPos.x + x, mStartPos.y + y, mStartPos.z + z));

    if (tEnlapse > mDuration[id])
    {
      id++;
      if (id >= mTarget.size())
      {
        id = 0;
        mTarget.clear();
        mJumps.clear();
        mDuration.clear();
      }
      //mState = IDLE;
      setPosition(target);
      mStartPos = target;
      mTimer.start();
    }

    if (mTarget.empty())
    {
      mState = MODEL_IDLE;
    }
  }
}


Piece::~Piece(void)
{
}
