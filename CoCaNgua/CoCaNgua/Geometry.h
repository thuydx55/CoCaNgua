#pragma once
#ifndef _GEOMETRY_H_
#define _GEOMETRY_H

#include <gl/glut.h>

class GLPoint3f
{
public:
  GLdouble x, y, z;

  GLPoint3f() : x(0), y(0), z(0) {};
  GLPoint3f(GLdouble _x, GLdouble  _y, GLdouble  _z) : x(_x), y(_y), z(_z) {};
  GLPoint3f(const GLPoint3f &other) : x(other.x), y(other.y), z(other.z) {};
};


#define GLSYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; glutPostRedisplay(); }

#define glp3f(__X__,__Y__,__Z__) GLPoint3f((GLdouble)__X__,(GLdouble)__Y__,(GLdouble)__Z__)

#endif // !_GEOMETRY_H_
