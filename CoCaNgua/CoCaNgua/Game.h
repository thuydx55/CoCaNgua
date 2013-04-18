#pragma once

#ifndef _GAME_H
#define _GAME_H

#include <string>

#include "Piece.h"
#include "Die.h"
#include "Board.h"
#include "Light.h"
#include "Graphic.h"
#include "Constants.h"

#define SHOW_GRID 1
#define SHOW_LIGHT_SOURCE 1

struct Field
{
  Vector3 position;
  Piece* piece;

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

  Field(Vector3 pPos, Piece* pPiece)
  {
    position = pPos;
    piece = pPiece;
  }
};

class Game
{
  void *font;

  Board*              mBoard;
  Piece*              mPieces[16]; // 0:3 RED, 4:7 BLUE, 8:11 GREEN, 12:16 YELLOW
  Die*                mDice;

  Vector3 mStartPos[16];
  Field mFields[40];
  Field mHome[16];
  int mConnerIndex[12];

  Vector3 mPredictPosition[4];
  MoveState mPredictMoveState[4];

  int mDieNumber;
  bool mDieIsThrown;
  bool mustBeStart;

  void drawSence();
  Piece* getModelByName(int name);
  int getModelPositionIndex(Vector3 pPos, Field pArray[], int pSize);
  bool checkAllModelIdle();
  void nextTurn();

public:
  GLfloat lightPosition[4];
  float lightAngle, lightHeight;

  float mScreenWidth, mScreenHeight;
  bool mIsDrawDie;

  Turn playerTurn;

  Game(void);
  ~Game(void);

  void initModel();
  static Game& inst();

  Piece** getPiecesArray();

  void resetBoard();
  void loop();
  void Move(int name);
  void throwDice(int number);
};

inline Piece** Game::getPiecesArray()
{
  return mPieces;
}

#endif // !_GAME_H

