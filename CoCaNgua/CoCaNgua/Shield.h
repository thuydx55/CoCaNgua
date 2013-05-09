#ifndef _CG_SHIELD_H_
#define _CG_SHIELD_H_

#include "Model.h"
class Shield : public Model
{
public:
  Shield(void);
  ~Shield(void);

  virtual void drawModel();
};

#endif
