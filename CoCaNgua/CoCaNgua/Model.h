#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_

#include "ModelOBJ.h"
#include "Geometry.h"

#include "SOIL/SOIL.h"

#include <gl/glut.h>

#include <iostream>

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

  ModelTextures       g_modelTextures;

  void DrawModelUsingFixedFuncPipeline();
  GLuint loadTexture(const char *pszFilename);

public:
  Model(void);
  ~Model(void);

  void loadModel(const char *pszFilename);
  void drawModel();
};

#endif // !_MODEL_H_
