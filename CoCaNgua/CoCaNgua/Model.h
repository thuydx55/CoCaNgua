#ifndef _CG_MODEL_H_
#define _CG_MODEL_H_

#include "ModelOBJ.h"
#include "Constants.h"
#include "mathlib.h"
#include "Timer.h"
#include "Light.h"
#include "SOIL/SOIL.h"
#include "collision.h"

#include <gl/glut.h>

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

typedef std::map<std::string, GLuint> ModelTextures;

class Model : public ModelOBJ
{
  GLSYNTHESIZE(Vector3, mPos, Position);          // Default is (0, 0, 0)
  GLSYNTHESIZE(Vector3, mAnchor, AnchorPoint);    // Default is (0, 0, 0)
                                                  // AnchorPoint is from -0.5 to 0.5
  GLSYNTHESIZE(Vector3, mRotateAxis, RotateAxis);
  GLSYNTHESIZE(GLfloat, mAngleRotate, AngleRotate);

  GLSYNTHESIZE(bool, g_enableTextures, EnableTextures);

  Vector3 minVec, maxVec;

  ModelTextures       mModelTextures;  
  GLfloat             mColorTint[3];

  bool mWaitIsCalled;

  Timer mTimer;

  void draw();
  GLuint loadTexture(const char *pszFilename);

protected:
  void shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4]);

public:
  Model(void);
  Model(const Model* other);
  ~Model(void);

  void setColorTint(GLfloat red, GLfloat green, GLfloat blue);

  void loadModel(const char *pszFilename);
  virtual void drawModel();
  virtual void update();

  BoundingBox boundingbox();

  bool wait(float sec);
};

inline bool Model::wait(float sec)
{
  if (!mWaitIsCalled)
  {
    mTimer.start();
    mWaitIsCalled = true;
  }
  if (mTimer.elapsed() < sec)
    return false;
  else
  {
    mWaitIsCalled = false;
    return true;
  }
}

#endif // !_CG_MODEL_H_
