#pragma once
#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <gl/glut.h>

#define GLSYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; glutPostRedisplay(); }

enum PIECE_NAME
{
  RED_1 = 100,
  RED_2,
  RED_3,
  RED_4,

  GREEN_1,
  GREEN_2,
  GREEN_3,
  GREEN_4,

  BLUE_1,
  BLUE_2,
  BLUE_3,
  BLUE_4,

  YELLOW_1,
  YELLOW_2,
  YELLOW_3,
  YELLOW_4
};

enum Turn
{
  RED,
  BLUE,
  GREEN,
  YELLOW
};

enum ModelState
{
  IDLE,
  MOVE,
  JUMP
};

enum JumpState
{
  JUMP_MOVE,
  JUMP_ATTACK
};

#endif // !_GEOMETRY_H_
