#ifndef _CG_CONSTANTS_H_
#define _CG_CONSTANTS_H_

#include "mathlib.h"

#define DEBUG_BOUNDINGBOX       0
#define DEBUG_CLICKING_RAY      0
#define DEBUG_ORIGIN_AXES       1
#define DEBUG_LIGHT_SOURCE      1
#define DEBUG_SHOW_INFO         1

#define va_start    _crt_va_start
#define va_arg      _crt_va_arg
#define va_end      _crt_va_end

#define DIE_ROLL_NUMBER         3
#define DIE_WAITING_RANGE       15
#define DIE_WAITING_SPEED       3
#define DIE_TIME_ROLLING        3
#define DIE_TIME_USER_VIEW      1

#define PIECE_CIRCLE_SIZE       1.5

#define DIE_VIEW_SIZE           12

#define CAM_AUTO_MOVING_TIME    1.5

#define GLSYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

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

enum PieceState
{
  MODEL_IDLE,
  MODEL_JUMP,
  MODEL_ATTACK
};

enum DieState
{
  DIE_WAITING,
  DIE_ROLLING,
  DIE_STOP
};

enum Area
{
  AREA_OUT,
  AREA_GAME,
  AREA_HOME
};

enum AppScene
{
  APP_GAME,
  APP_MENU,
  APP_OPTION,
  APP_ABOUT,
  APP_SELECT,
  APP_LOADING
};

enum ButtonState
{
  BUTTON_NORMAL,
  BUTTON_HOVER,
  BUTTON_PRESSED,
  BUTTON_DISABLE
};

enum ToggleState
{
	TOGGLE_ON,
	TOGGLE_OFF,
	TOGGLE_DISABLE,
};
#endif // !_CG_CONSTANTS_H_
