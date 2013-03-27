#ifndef _CG_LIGHT_H_
#define _CG_LIGHT_H_

#include <GL/glut.h>

class Light
{
public:
  Light(float px, float py, float pz, float pw)
  {
    setPosition(px, py, pz, pw);
    setAmbient(1.0, 1.0, 1.0, 1.0);
    setDiffuse(1.0, 1.0, 1.0, 1.0);
    setSpecular(1.0, 1.0, 1.0, 1.0);
  }

  void setPosition(float x, float y, float z, float w)
  {
    _position[0] = x;
    _position[1] = y;
    _position[2] = z;
    _position[3] = w;
  }

  void setAmbient(float r, float g, float b, float a)
  {
    _ambient[0] = r;
    _ambient[1] = g;
    _ambient[2] = b;
    _ambient[3] = a;
  }

  void setDiffuse(float r, float g, float b, float a)
  {
    _diffuse[0] = r;
    _diffuse[1] = g;
    _diffuse[2] = b;
    _diffuse[3] = a;
  }

  void setSpecular(float r, float g, float b, float a)
  {
    _specular[0] = r;
    _specular[1] = g;
    _specular[2] = b;
    _specular[3] = a;
  }

  void setupLight(int glIndex)
  {
    glLightfv(GL_LIGHT0 + glIndex, GL_POSITION, _position);
    glLightfv(GL_LIGHT0 + glIndex, GL_AMBIENT,  _ambient);
    glLightfv(GL_LIGHT0 + glIndex, GL_DIFFUSE,  _diffuse);
    glLightfv(GL_LIGHT0 + glIndex, GL_SPECULAR, _specular);
  }
private:
  float _position[4];
  float _ambient[4];
  float _diffuse[4];
  float _specular[4];
};


#endif