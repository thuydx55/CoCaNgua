#ifndef _CG_ROCK_H_
#define _CG_ROCK_H_

#include "Model.h"

class Rock : public Model
{
  bool                mShadow;
  float               floorShadow[4][4];
public:
  Rock(void);
  Rock(const Rock* other);
  ~Rock(void);

  void shadow(bool value);
  bool isShadow();

  virtual void drawModel();
};  

inline void Rock::shadow(bool value)
{
  mShadow = value;
}

inline bool Rock::isShadow()
{
  return mShadow;
}

#endif // !_CG_ROCK_H_

