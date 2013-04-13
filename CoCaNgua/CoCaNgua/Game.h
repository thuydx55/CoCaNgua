#pragma once

#ifndef _GAME_H
#define _GAME_H

#include <string>

#include "Model.h"
#include "Light.h"
#include "Graphic.h"
#include "Geometry.h"

#define SHOW_GRID 1
#define SHOW_LIGHT_SOURCE 1

class Game
{
  void *font;

  Model*              mBoard;
  Model               *red[4], *blue[4], *green[4], *yellow[4];
  Model*              dice;

  Vector3 redStartPos[4], blueStartPos[4], yellowStartPos[4], greenStartPos[4];
  Vector3 road[40];
  Vector3 redStable[4], blueStable[4], yellowStable[4], greenStable[4];
  int connerIndex[12];

  void draw();
  Model* getModelByName(int name);
  int getModelPositionIndex(Vector3 pPos);
  bool checkAllModelIdle();
  int nextPosition(int pIndexCurPos, int pDiceNumber, Model* pModel);

public:
  GLfloat lightPosition[4];
  float lightAngle, lightHeight;

  Turn playerTurn;

  Game(void);
  ~Game(void);

  void initModel();
  static Game& inst();

  Model** getRedFigure();
  Model** getBlueFigure();
  Model** getGreenFigure();
  Model** getYellowFigure();

  void resetBoard();
  void loop();
  void demoMove(int name);
};

inline Model** Game::getRedFigure()
{
  return red;
}

inline Model** Game::getBlueFigure()
{
  return blue;
}

inline Model** Game::getGreenFigure()
{
  return green;
}

inline Model** Game::getYellowFigure()
{
  return yellow;
}

#endif // !_GAME_H

