#pragma once

#ifndef _GAME_H
#define _GAME_H

#include <string>

#include "Model.h"
#include "Light.h"
#include "Graphic.h"

#define SHOW_GRID 1
#define SHOW_LIGHT_SOURCE 1

enum PIECE_NAME
{
  RED_1 = 100,
  RED_2,
  RED_3,
  RED_4,

  BLUE_1,
  BLUE_2,
  BLUE_3,
  BLUE_4,

  GREEN_1,
  GREEN_2,
  GREEN_3,
  GREEN_4,

  YELLOW_1,
  YELLOW_2,
  YELLOW_3,
  YELLOW_4
};


class Game
{
  void *font;

  Model*              mBoard;
  Model               *red[4], *blue[4], *green[4], *yellow[4];
  Model*              dice;

  Vector3 redStartPos[4], blueStartPos[4], yellowStartPos[4], greenStartPos[4];

  void draw();

public:
  GLfloat lightPosition[4];
  float lightAngle, lightHeight;

  Game(void);
  ~Game(void);

  void initModel();
  static Game& inst();

  void resetBoard();

  void loop();
};

#endif // !_GAME_H

