#pragma once

#ifndef _PIECE_H_
#define _PIECE_H_

#include "Model.h"
#include "Constants.h"

class Piece : public Model
{
  GLSYNTHESIZE(GLfloat, mHighlightThickness, HighLightThickness);
  GLSYNTHESIZE(ModelState, mState, State);
  GLSYNTHESIZE(Vector3, mInitPos, InitPosition);
  GLSYNTHESIZE(Area, mArea, Area);

  Turn mType;
  int mIndexFirstPos;

  bool                mHighlight;
  GLfloat             mHighlightColor[4];

  bool				  mShadow;
  float floorShadow[4][4];

  Timer mTimer;

  vector<int>       mJumps;
  float             mHeight;
  vector<float>     mDuration;
  Vector3           mStartPos;
  vector<Vector3>   mTarget;

  void shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4]);

public:
  Piece(void);
  Piece(const Piece* other);
  ~Piece(void);

  void drawModel();

  void highlight(bool value);
  void setHighLightColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

  bool isHighlight();

  void shadow(bool value);
  bool isShadow();

  Turn getType();
  void setType(Turn pType);
  int getIndexFirstPos();

  void jumpTo(vector<Vector3> pTarget, MoveState pMoveState);
  void update();
};  

inline Turn Piece::getType()
{
  return mType;
}

inline void Piece::setType(Turn pType)
{
  mType = pType;
  mIndexFirstPos = mType*10;
}

inline int Piece::getIndexFirstPos()
{
  return mIndexFirstPos;
}

#endif // !_PIECE_H_
