#ifndef _CG_GAME_H
#define _CG_GAME_H

#include <string>

#include "Scene.h"
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

class GameScene : public Scene
{
  void* font;

  // Model
  Board*              mBoard;
  Piece*              mPieces[16]; // 0:3 RED, 4:7 BLUE, 8:11 GREEN, 12:16 YELLOW
  Piece*              tmp;
  
  // Disable some players
  bool mEnablePiece[4];

  // Array of Position in board
  Vector3 mStartPos[16];
  Field mFields[40];
  Field mHome[16];
  int mConnerIndex[12];

  // Predict Position and MoveState after roll die
  Vector3 mPredictPosition[4];
  MoveState mPredictMoveState[4];
  bool mIsGoHome[4];

  int mDieNumber;
  int mTries;
  bool mDieIsThrown;
  bool mustBeStart;
  bool mFullHome;
  bool mPieceIsMoving;

  Turn mWinner;

  // Click
  Matrix4 modelViewMatx;
  Ray mViewRay;

  void drawSence();
  void drawDie();
  Piece* getModelByName(int name);
  int getModelPositionIndex(Vector3 pPos, Field pArray[], int pSize);
  bool checkAllModelIdle();
  void nextTurn();

  void identifyModelClicked(int mouse_x, int mouse_y);

public:
  Die*                mDice;

  GLfloat lightPosition[4];
  float lightAngle, lightHeight;

  bool mDieIsDrawn;
  Turn mPlayerTurn;

  GameScene(void);
  ~GameScene(void);

  static GameScene& inst();

  void initBoard();
  void initDie();
  void initPiece();
  void initAllPieces();

  Piece** getPiecesArray();

  void resetBoard();
  void loop();
  void movePiece(int name);
  void rollDice(int number);

  void setDisablePiece(int index);

  void processMouseBegan(int x, int y);
  void processMouseEnded(int x, int y);
  void processMousePassiveMotion(int x, int y);

  virtual void update();
};

inline Piece** GameScene::getPiecesArray()
{
  return mPieces;
}

#endif // !_GAME_H

