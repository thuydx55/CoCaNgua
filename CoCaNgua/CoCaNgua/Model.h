#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_

#include "ModelOBJ.h"
#include "Geometry.h"

#include "SOIL/SOIL.h"

#include <gl/glut.h>

#include <iostream>
#include <cstring>

#include "Timer.h"

using namespace std;

typedef std::map<std::string, GLuint> ModelTextures;

class Model : public ModelOBJ
{
  GLSYNTHESIZE(GLPoint3f, mPos, Position);       // Default is (0, 0, 0)
  GLSYNTHESIZE(GLPoint3f, mAnchor, AnchorPoint); // Default is (0, 0, 0)
                                                 // AnchorPoint is from -0.5 to 0.5
  GLSYNTHESIZE(GLPoint3f, mRotate, Rotate);
  GLSYNTHESIZE(GLfloat, mAngle, Angle);

  GLSYNTHESIZE(bool, g_enableTextures, EnableTextures);
  GLSYNTHESIZE(GLfloat, mHighlightThickness, HighLightThickness);

  GLSYNTHESIZE(GLPoint3f, mMedDis, MediateDistance);

  float mSteps;
  float mStepCounter;

  bool mHighlight;
  bool mMoving;
  GLfloat mHighlightColor[4];
  GLfloat mColorTint[3];
  ModelTextures       g_modelTextures;

  //Timer mMoveTimer;
  Timer mStepTimer;
  

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
  bool isMoving();

  void moveTo(GLPoint3f pTarget, float pDuration);

  void update();
};

#endif // !_MODEL_H_
