#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_

#include "ModelOBJ.h"
#include "Geometry.h"
#include "mathlib.h"

#include "SOIL/SOIL.h"

#include <gl/glut.h>

#include <iostream>
#include <cstring>
#include <vector>

#include "Timer.h"
#include "Geometry.h"
#include "Light.h"

using namespace std;

typedef std::map<std::string, GLuint> ModelTextures;

enum {
  X, Y, Z, W
};
enum {
  A, B, C, D
};

class Model : public ModelOBJ
{
  GLSYNTHESIZE(Vector3, mPos, Position);       // Default is (0, 0, 0)
  GLSYNTHESIZE(Vector3, mAnchor, AnchorPoint); // Default is (0, 0, 0)
                                                 // AnchorPoint is from -0.5 to 0.5
  GLSYNTHESIZE(Vector3, mRotate, Rotate);
  GLSYNTHESIZE(GLfloat, mAngle, Angle);

  GLSYNTHESIZE(bool, g_enableTextures, EnableTextures);
  GLSYNTHESIZE(GLfloat, mHighlightThickness, HighLightThickness);

  GLSYNTHESIZE(ModelState, mState, State);
  GLSYNTHESIZE(Vector3, mInitPos, InitPosition);

  Turn mType;
  int mIndexFirstPos;

  bool                mHighlight;
  GLfloat             mHighlightColor[4];
  GLfloat             mColorTint[3];
  ModelTextures       mModelTextures;

  bool				  mShadow;
  //float				  lightAngle;
  float floorShadow[4][4];

  Timer mTimer;

  vector<int>       mJumps;
  float             mHeight;
  vector<float>     mDuration;
  Vector3           mStartPos;
  vector<Vector3>   mTarget;

  void draw();
  GLuint loadTexture(const char *pszFilename);
  void shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4]);

public:
  Model(void);
  Model(const Model* other);
  ~Model(void);

  void loadModel(const char *pszFilename);
  void drawModel();

  void highlight(bool value);
  void setHighLightColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

  void setColorTint(GLfloat red, GLfloat green, GLfloat blue);

  bool isHighlight();

  void shadow(bool value);
  bool isShadow();

  Vector3 getCenterLocation();

  Turn getType();
  void setType(Turn pType);
  int getIndexFirstPos();

  void jumpTo(vector<Vector3> pTarget, MoveState pMoveState);

  void update();

};

inline Turn Model::getType()
{
  return mType;
}

inline void Model::setType(Turn pType)
{
  mType = pType;
  mIndexFirstPos = mType*10;
}

inline int Model::getIndexFirstPos()
{
  return mIndexFirstPos;
}

#endif // !_MODEL_H_
