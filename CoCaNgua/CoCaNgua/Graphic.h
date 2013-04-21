#ifndef _CG_GRAPHIC_H_
#define _CG_GRAPHIC_H_

#include "Model.h"
#include "Constants.h"

class Graphic
{
  GLSYNTHESIZE(AppScene, mAppScene, AppScene);
public:
  Graphic(void);
  ~Graphic(void);
  
  static Graphic& inst();

  void drawString(const char *str, int x, int y, float color[4], void *font);
  void drawString3D(const char *str, float pos[3], float color[4], void *font);

};

#endif
