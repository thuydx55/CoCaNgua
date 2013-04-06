#pragma once
#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <gl/glut.h>

#define GLSYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; glutPostRedisplay(); }

#endif // !_GEOMETRY_H_
