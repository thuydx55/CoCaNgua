#ifndef _CG_PIECE_H_
#define _CG_PIECE_H_

#include "Model.h"
#include "Knife.h"
#include "Shield.h"
#include "Constants.h"
#include "Sprite2D.h"

class Piece;

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

class Piece : public Model
{
  GLSYNTHESIZE(GLfloat, mHighlightThickness, HighLightThickness);
  GLSYNTHESIZE(PieceState, mState, State);
  GLSYNTHESIZE(Field, mInitPos, InitPosition);
  GLSYNTHESIZE(Area, mArea, Area);

  Sprite2D* mCircle;
  Knife*    mKnife;
  Shield*   mShield;
  bool      mDrawKnife;
  bool      mDrawShield;

  Turn mType;
  int mIndexFirstPos;

  bool                mHighlight;
  GLfloat             mHighlightColor[4];
  bool                mSelected;
  bool                mShadow;
  float               floorShadow[4][4];

  Timer mTimer;

  vector<int>       mJumps;
  float             mHeight;
  vector<float>     mDuration;
  Vector3           mStartPos;
  vector<Field>     mTarget;

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

  void attack(bool value);
  bool isAttacking();
  void defence(bool value);
  bool isDefencing();

  void jumpTo(const vector<Field> &pTarget, MoveState pMoveState);
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

inline void Piece::attack(bool value)
{
  mDrawKnife = value;
}

inline bool Piece::isAttacking()
{
  return mDrawKnife;
}

inline void Piece::defence(bool value)
{
  mDrawShield = value;
}

inline bool Piece::isDefencing()
{
  return mDrawShield;
}

#endif // !_CG_PIECE_H_
