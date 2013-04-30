#ifndef _CG_PIECE_H_
#define _CG_PIECE_H_

#include "Model.h"
#include "Constants.h"
#include "Sprite2D.h"

class Piece : public Model
{
  GLSYNTHESIZE(GLfloat, mHighlightThickness, HighLightThickness);
  GLSYNTHESIZE(PieceState, mState, State);
  GLSYNTHESIZE(Vector3, mInitPos, InitPosition);
  GLSYNTHESIZE(Area, mArea, Area);

  Sprite2D* mCircle;

  Turn mType;
  int mIndexFirstPos;

  bool                mHighlight;
  GLfloat             mHighlightColor[4];
  bool                mSelected;
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

  void selected(bool value);
  bool isSelected();

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

  switch (pType)
  {
  case TURN_RED:
    setColorTint(0.8, 0, 0);
    break;
  case TURN_BLUE:
    setColorTint(0, 0, 0.8);
    break;
  case TURN_GREEN:
    setColorTint(0, 0.8, 0); 
    break;
  case TURN_YELLOW:
    setColorTint(0.8, 0.8, 0);
    break;
  default:
    break;
  }
}

inline int Piece::getIndexFirstPos()
{
  return mIndexFirstPos;
}

inline void Piece::shadow(bool value)
{
  mShadow = value;
}

inline bool Piece::isShadow()
{
  return mShadow;
}

inline void Piece::selected(bool value)
{
  mSelected = value;
}
inline bool Piece::isSelected()
{
  return mSelected;
}

inline void Piece::highlight(bool value)
{
  mHighlight = value;
  if (!mHighlight)
  {
    mSelected = false;
  }
}

inline bool Piece::isHighlight()
{
  return mHighlight;
}

inline void Piece::setHighLightColor( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
  mHighlightColor[0] = red;
  mHighlightColor[1] = green;
  mHighlightColor[2] = blue;
  mHighlightColor[3] = alpha;
}

#endif // !_CG_PIECE_H_
