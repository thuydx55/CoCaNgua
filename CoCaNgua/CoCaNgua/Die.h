#pragma once
#ifndef _DIE_H_
#define _DIE_H_

#include "Model.h"

class Die : public Model
{
public:
  Die(void);
  ~Die(void);

  virtual void drawModel();
};  

#endif // !_DIE_H_
