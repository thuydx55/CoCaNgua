#ifndef _CG_SPRITE_H_
#define _CG_SPRITE_H_

//#include "gl/glut.h"

#include "SOIL/SOIL.h"
#include "mathlib.h"
#include "Constants.h"
#include "Geometry.h"

#include <iostream>

using namespace std;

class Sprite2D
{
  GLSYNTHESIZE(Vector2, mPos, Position);
  GLSYNTHESIZE(Vector2, mAnchor, AnchorPoint);
  GLSYNTHESIZE(int, mOpacity, Opacity);

  int texID;
  bool mVisible;

  void loadTexture(const char *pszFilename);

public:

  int channel;
  Size size;

  Sprite2D(void);
  Sprite2D(const char* pFilename);
  ~Sprite2D(void);

  static Sprite2D* create();
  static Sprite2D* create(const char* pFilename);

  void initWithFile(const char* pFilename);

  void drawImg();

  void setVisible(bool visible);
  bool isVisible();

  Rect boundingBox();
};  

inline void Sprite2D::setVisible(bool visible)
{
  mVisible = visible;
}

inline bool Sprite2D::isVisible()
{
  return mVisible;
}

#endif // !_SPRITE_H_


