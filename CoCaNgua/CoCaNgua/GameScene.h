#ifndef _CG_GAME_SCENE_H_
#define _CG_GAME_SCENE_H_

#include <string>

#include "Scene.h"
#include "Piece.h"
#include "Die.h"
#include "Board.h"
#include "Rock.h"
#include "Sky.h"
#include "Light.h"
#include "Graphic.h"
#include "Constants.h"
#include "Camera.h"

class GameScene : public Scene
{
  void* font;

  // Model
  Board*              mBoard;
  Piece*              mPieces[16]; // 0:3 RED, 4:7 BLUE, 8:11 GREEN, 12:16 YELLOW
  Piece*              tmpPiece;
  Die*                mDice;
  Rock*               mFieldRock[40];
  Rock*               mHomeRock[16];
  Rock*               mStartRock[16];
  Rock*               mCenterPillar;
  Rock*               mApple;
  Sky*                mSky;
  
  // Disable some players
  bool mEnablePiece[4];

  // Array of Position in board
  Field mStartPos[16];
  Field mFields[40];
  Field mHome[16];
  int mConnerIndex[12];

  // Predict Position and MoveState after roll die
  Field* mPredictPosition[4];
  MoveState mPredictMoveState[4];
  bool mIsGoHome[4];

  int mDieNumber;
  int mTries;
  bool mDieIsThrown;
  bool mustBeStart;
  bool mFullHome;
  MoveState mPieceMovingState;

  Turn mWinner;
  Ray mViewRay;

  float mUserViewAngle;

  void drawSence();
  void drawDie();
  int getModelPositionIndex(Vector3 pPos, Field pArray[], int pSize);
  bool checkAllModelIdle();
  void nextTurn();

  int identifyModelClicked(int mouse_x, int mouse_y);
  float calcUserViewAngle(Vector3 pV);

public:
  GLfloat lightPosition[4];
  float lightAngle, lightHeight;

  bool mDieIsDrawn;
  Turn mPlayerTurn;
  bool mAutoCam;

  GameScene(void);
  ~GameScene(void);

  static GameScene& inst();

  void initBoard();
  void initDie();
  void initPiece();
  void initAllPieces();
  void initRock();

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

