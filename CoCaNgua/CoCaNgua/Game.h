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

struct Field
{
  Vector3 position;
  Model* piece;

  Field()
  {
    position = Vector3();
    piece = NULL;
  }

  Field(Vector3 pPos)
  {
    position = pPos;
    piece = NULL;
  }

  Field(Vector3 pPos, Model* pPiece)
  {
    position = pPos;
    piece = pPiece;
  }
};

class Game
{
  void *font;

  Model*              mBoard;
  Model*              mPieces[16]; // 0:3 RED, 4:7 BLUE, 8:11 GREEN, 12:16 YELLOW
  Model*              mDice;

  Vector3 mStartPos[16];
  Field mFields[40];
  Field mHome[16];
  int connerIndex[12];

  Vector3 mPredictPosition[4];
  MoveState mPredictMoveState[4];

  int mDiceNumber;
  bool mDiceIsThrown;

  void draw();
  Model* getModelByName(int name);
  int getModelPositionIndex(Vector3 pPos, Field pArray[], int pSize);
  bool checkAllModelIdle();
  void nextTurn();

public:
  GLfloat lightPosition[4];
  float lightAngle, lightHeight;

  Turn playerTurn;

  Game(void);
  ~Game(void);

  void initModel();
  static Game& inst();

  Model** getFigureArray();

  void resetBoard();
  void loop();
  void demoMove(int name);
  void throwDice(int number);
};

inline Model** Game::getFigureArray()
{
  return mPieces;
}

#endif // !_GAME_H

