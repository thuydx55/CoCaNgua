#ifndef _CG_SKY_H_
#define _CG_SKY_H_

#include "Model.h"

class Sky : public Model
{
public:
  Sky(void);
  ~Sky(void);

  virtual void drawModel();
};  

#endif // !_CG_SKY_H_
