#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_

#include "ModelOBJ.h"
#include "Geometry.h"
#include <gl/glut.h>

class Model : public ModelOBJ
{
  GLSYNTHESIZE(GLPoint3f, mPos, Position);

  void DrawModelUsingFixedFuncPipeline();

public:
  Model(void);
  ~Model(void);

  void drawModel();

  
};

#endif // !_MODEL_H_
