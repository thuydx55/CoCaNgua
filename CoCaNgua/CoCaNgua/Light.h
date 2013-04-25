#ifndef _CG_LIGHT_H_
#define _CG_LIGHT_H_

#include <GL/glut.h>
#include <iostream>

using namespace std;

#define M_PI 3.141592654

class Light
{
public:
  Light()
  {
    setPosition(10, 10, 10, 1);
    setAmbient(0.2, 0.2, 0.2, 1.0);
    setDiffuse(0.7, 0.7, 0.7, 1.0);
    setSpecular(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_LIGHT0);
  }

  Light(float px, float py, float pz, float pw)
  {
    setPosition(px, py, pz, pw);
    setAmbient(0.2, 0.2, 0.2, 1.0);
    setDiffuse(0.7, 0.7, 0.7, 1.0);
    setSpecular(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_LIGHT0);  
  }

  static Light& inst()
  {
    static Light gLight;
    return gLight;
  }

  void setPosition(float x, float y, float z, float w)
  {
    _position[0] = x;
    _position[1] = y;
    _position[2] = z;
    _position[3] = w;
    glLightfv(GL_LIGHT0, GL_POSITION, _position);
  }

  float* getPosition()
  {
    return _position;
  }

  void setAmbient(float r, float g, float b, float a)
  {
    _ambient[0] = r;
    _ambient[1] = g;
    _ambient[2] = b;
    _ambient[3] = a;
    glLightfv(GL_LIGHT0, GL_AMBIENT,  _ambient);
  }

  void setDiffuse(float r, float g, float b, float a)
  {
    _diffuse[0] = r;
    _diffuse[1] = g;
    _diffuse[2] = b;
    _diffuse[3] = a;
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  _diffuse);
  }

  void setSpecular(float r, float g, float b, float a)
  {
    _specular[0] = r;
    _specular[1] = g;
    _specular[2] = b;
    _specular[3] = a;
    glLightfv(GL_LIGHT0, GL_SPECULAR, _specular);
  }

  void drawLightSource(float lightAngle, float lightHeight)
  {
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 0.0);
      /* Draw an arrowhead. */
      glDisable(GL_CULL_FACE);
      glTranslatef(_position[0], _position[1], _position[2]);
      glRotatef(lightAngle * -180.0 / M_PI, 0, 1, 0);
      glRotatef(atan(lightHeight/12) * 180.0 / M_PI, 0, 0, 1);
      glBegin(GL_TRIANGLE_FAN);
      glVertex3f(0, 0, 0);
      glVertex3f(2, 1, 1);
      glVertex3f(2, -1, 1);
      glVertex3f(2, -1, -1);
      glVertex3f(2, 1, -1);
      glVertex3f(2, 1, 1);
      glEnd();
      /* Draw a white line from light direction. */
      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_LINES);
      glVertex3f(0.1, 0, 0);
      glVertex3f(5, 0, 0);
      glEnd();
      glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glPopMatrix();
  }

private:
  float _position[4];
  float _ambient[4];
  float _diffuse[4];
  float _specular[4];
};


#endif