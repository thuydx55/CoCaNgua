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

using namespace std;


enum ModelState
{
  IDLE,
  MOVE,
  JUMP
};

enum JumpState
{
  JUMP_MOVE,
  JUMP_ATTACK
};

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

  GLSYNTHESIZE(Vector3, mMedDis, MediateDistance);
  GLSYNTHESIZE(ModelState, mState, State);

  int mSteps;
  int mStepCounter;

  bool mHighlight;
  GLfloat mHighlightColor[4];
  GLfloat mColorTint[3];
  ModelTextures       g_modelTextures;

  Timer mTimer;
  Timer mStepTimer;

  vector<int> mJumps;
  float mHeight;
  vector<float> mDuration;
  Vector3 mStartPos;
  vector<Vector3> mTarget;
  

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

  void moveTo(Vector3 pTarget, float pDuration);

  void jumpTo(Vector3 pStart, vector<Vector3> pTarget, JumpState j);

  void update();

};

#endif // !_MODEL_H_
