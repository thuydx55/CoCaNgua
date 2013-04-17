#pragma once
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <gl/glut.h>
#include "mathlib.h"

#define GLSYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; glutPostRedisplay(); }

enum PieceName
{
  PIECE_RED_1 = 100,
  PIECE_RED_2,
  PIECE_RED_3,
  PIECE_RED_4,

  PIECE_BLUE_1,
  PIECE_BLUE_2,
  PIECE_BLUE_3,
  PIECE_BLUE_4,

  PIECE_GREEN_1,
  PIECE_GREEN_2,
  PIECE_GREEN_3,
  PIECE_GREEN_4,  

  PIECE_YELLOW_1,
  PIECE_YELLOW_2,
  PIECE_YELLOW_3,
  PIECE_YELLOW_4
};

enum Turn
{
  TURN_RED = 0,
  TURN_BLUE,
  TURN_GREEN,
  TURN_YELLOW
};

enum MoveState
{
  MOVE_START,
  MOVE_NORMAL,
  MOVE_ATTACK,
  MOVE_START_ATTACK,
  MOVE_HOME_INSIDE,
  MOVE_HOME_OUTSIDE,
  MOVE_ILLEGAL
};

enum ModelState
{
  MODEL_IDLE,
  MODEL_MOVE,
  MODEL_JUMP
};

#endif // !_CONSTANTS_H_
