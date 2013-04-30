#include "Piece.h"

int id = 0;
GLfloat floorPlane[4] = {
  0, 1, 0, 0
};
float circleAngle = 0;

Piece::Piece(void)
{
  mHighlight    = false;
  mShadow       = true;
  mSelected     = false;

  mHighlightThickness =  0.7;
  mHighlightColor[0] = 0.8;
  mHighlightColor[1] = 0.8;
  mHighlightColor[2] = 0.0;
  mHighlightColor[3] = 0.5;

  mState = MODEL_IDLE;
  mArea = AREA_OUT;

  mCircle = Sprite2D::create("Models/circle.png");
}

Piece::Piece( const Piece* other )
{
  memcpy(this, other, sizeof(*other));
}

void Piece::drawModel()
{
  Model::drawModel();

  if (mSelected)
  {
    glColor4f(1, 1, 1, 1);
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glTranslatef(mPos.x, mPos.y, mPos.z);
    glRotatef(circleAngle, 0, 1, 0);
    float size = getWidth() > getLength() ? getWidth()/2 : getLength()/2;
    mCircle->drawImg(Vector3( -PIECE_CIRCLE_SIZE*size, 0, -PIECE_CIRCLE_SIZE*size),
                     Vector3( -PIECE_CIRCLE_SIZE*size, 0,  PIECE_CIRCLE_SIZE*size),
                     Vector3(  PIECE_CIRCLE_SIZE*size, 0,  PIECE_CIRCLE_SIZE*size),
                     Vector3(  PIECE_CIRCLE_SIZE*size, 0, -PIECE_CIRCLE_SIZE*size));
    glEnable(GL_LIGHTING);
    glPopMatrix();
  }

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
    glPopMatrix();

    if(mShadow)
    {
      glEnable(GL_STENCIL_TEST);
      glStencilFunc(GL_EQUAL, 0x4, 0x4);
      glStencilMask(0x4);
      glStencilOp(GL_KEEP, GL_KEEP, GL_INVERT);

      //float fP[4] = {floorPlane[0], floorPlane[1], floorPlane[2], floorPlane[3] + mPos.y };
      shadowMatrix(floorShadow, floorPlane, Light::inst().getPosition());

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glDisable(GL_LIGHTING);  /* Force the 50% black. */
      glColor4f(0.0, 0.0, 0.0, 0.5);

      glPushMatrix();
      {
        glTranslatef(-mAnchor.x*getWidth(), -mAnchor.y*getHeight(), -mAnchor.z*getLength());
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
  }
  glPopMatrix();
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

void Piece::jumpTo( const vector<Field> &pTarget, MoveState pMoveState )
{
  if (mState == MODEL_IDLE)
  {
    mState = MODEL_JUMP;

    mStartPos = getPosition();
    mTarget = pTarget;

    if (pMoveState == MOVE_NORMAL || pMoveState == MOVE_HOME_INSIDE || pMoveState == MOVE_HOME_OUTSIDE)
    {
      Vector3 delta = (pTarget[0].position - mStartPos)/4;
      mJumps.push_back(delta.magnitude());
      mDuration.push_back(delta.magnitude() * 0.25);
      mHeight = 5;

      for (int i = 1; i < pTarget.size(); i++)
      {
        delta = (pTarget[i].position - pTarget[i-1].position)/4;
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
  circleAngle = (circleAngle > 360 ? circleAngle - 360 : circleAngle) + 0.3;

  double tEnlapse = mTimer.elapsed();

  if (mState == MODEL_JUMP)
  {
    Vector3 target = mTarget[id].position;

    float frac = fmodf((tEnlapse / mDuration[id]) * mJumps[id], 1);
    float y = (mHeight * 4 * frac * (1 - frac));
    y += target.y * tEnlapse;
    float x = (target - mStartPos).x * (tEnlapse / mDuration[id]);
    float z = (target - mStartPos).z * (tEnlapse / mDuration[id]);

    setPosition(Vector3(mStartPos.x + x, mStartPos.y + y, mStartPos.z + z));

    if (tEnlapse > mDuration[id])
    {
      setAngle(mTarget[id].direction);
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
