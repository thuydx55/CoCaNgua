#ifndef _CG_ROCK_H_
#define _CG_ROCK_H_

#include "Model.h"

class Rock : public Model
{
public:
  Rock(void);
  Rock(const Rock* other);
  ~Rock(void);

  virtual void drawModel();
};  
#endif // !_CG_ROCK_H_

