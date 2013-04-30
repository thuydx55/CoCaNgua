#ifndef _CG_GAME_SCENE_H_
#define _CG_GAME_SCENE_H_

#include <string>

#include "Scene.h"
#include "Piece.h"
#include "Die.h"
#include "Board.h"
#include "Rock.h"
#include "Light.h"
#include "Graphic.h"
#include "Constants.h"
#include "Camera.h"

struct Field
{
  Vector3 position;
  Piece* piece;
  float direction; // 0, 90, 180, -90 

  Field()
  {
    position = Vector3();
    piece = NULL;
    direction = 0;
  }

  Field(Vector3 pPos)
  {
    position = pPos;
    piece = NULL;
    direction = 0;
  }

  Field(Vector3 pPos, Piece* pPiece)
  {
    position = pPos;
    piece = pPiece;
    direction = 0;
  }

  Field(Vector3 pPos, float pD)
  {
    position = pPos;
    piece = NULL;
    direction = pD;
  }
};

class GameScene : public Scene
{
  void* font;

  // Model
  Board*              mBoard;
  Piece*              mPieces[16]; // 0:3 RED, 4:7 BLUE, 8:11 GREEN, 12:16 YELLOW
  Piece*              tmp;
  Rock*               mFieldModel[40];
  
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
  Ray viewRay;

  void drawSence();
  void drawDie();
  int getModelPositionIndex(Vector3 pPos, Field pArray[], int pSize);
  bool checkAllModelIdle();
  void nextTurn();

  int identifyModelClicked(int mouse_x, int mouse_y);

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
  void initRoad();

  Piece** getPiecesArray();

  void resetBoard();
  void loop();
  void movePiece(int index);
  void predictNextMove(int number);

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

#endif // !_CG_GAME_SCENE_H_

