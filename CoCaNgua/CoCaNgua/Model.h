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

using namespace std;

typedef std::map<std::string, GLuint> ModelTextures;

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

  Turn mType;
  Vector3 mDefaultStartPos;

  bool                mHighlight;
  GLfloat             mHighlightColor[4];
  GLfloat             mColorTint[3];
  ModelTextures       mModelTextures;

  Timer mTimer;

  vector<int>       mJumps;
  float             mHeight;
  vector<float>     mDuration;
  Vector3           mStartPos;
  vector<Vector3>   mTarget;

  void draw();
  GLuint loadTexture(const char *pszFilename);

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

  Vector3 getCenterLocation();

  Turn getType();
  void setType(Turn pType);
  Vector3 getDefaultStartPos();

  void jumpTo(Vector3 pStart, vector<Vector3> pTarget, JumpState j);

  void update();

};

inline Turn Model::getType()
{
  return mType;
}

inline void Model::setType(Turn pType)
{
  mType = pType;
  switch (mType) {
  case RED:
    mDefaultStartPos = Vector3(-20, 0, -4);
    break;
  case BLUE:
    mDefaultStartPos = Vector3(4, 0, -20);
    break;
  case GREEN:
    mDefaultStartPos = Vector3(20, 0, 4);
    break;
  case YELLOW:
    mDefaultStartPos = Vector3(-4, 0, 20);
    break;
  }
}

inline Vector3 Model::getDefaultStartPos()
{
  return mDefaultStartPos;
}

#endif // !_MODEL_H_
