#include "Graphic.h"


Graphic::Graphic(void)
{
  mAppScene = APP_LOADING;
}

Graphic& Graphic::inst()
{
  static Graphic Instance;
  return Instance;
}

void Graphic::drawString(const char *str, int x, int y, float color[4], void *font)
{
  glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
  glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
  glDisable(GL_TEXTURE_2D);

  glColor4fv(color);          // set text color
  glRasterPos2i(x, y);        // place text position

  // loop all characters in the string
  while(*str)
  {
    glutBitmapCharacter(font, *str);
    ++str;
  }

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glPopAttrib();
}

void Graphic::drawString3D(const char *str, float pos[3], float color[4], void *font)
{
  glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
  glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
  glDisable(GL_TEXTURE_2D);

  glColor4fv(color);          // set text color
  glRasterPos3fv(pos);        // place text position

  // loop all characters in the string
  while(*str)
  {
    glutBitmapCharacter(font, *str);
    ++str;
  }

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glPopAttrib();
}

Graphic::~Graphic(void)
{
}
