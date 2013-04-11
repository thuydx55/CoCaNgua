#pragma once

#ifndef _GAME_H
#define _GAME_H

#include "Model.h"
#include "Light.h"
#include "Graphic.h"

#define SHOW_GRID 1
#define SHOW_LIGHT_SOURCE 1



class Game
{
  void *font;
  

  Model*              mBoard;
  Model               *red[4], *blue[4], *green[4], *yellow[4];
  Model*              dice;

  void draw();

public:
  GLfloat lightPosition[4];
  float lightAngle, lightHeight;

  Game(void);
  ~Game(void);

  void initModel();
  static Game& inst();

  void loop();

  void demoMove();
};

#endif // !_GAME_H

