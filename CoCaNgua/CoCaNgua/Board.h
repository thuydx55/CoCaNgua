#ifndef _CG_BOARD_H_
#define _CG_BOARD_H_

#include "Model.h"

class Board : public Model
{
public:
  Board(void);
  ~Board(void);

  virtual void drawModel();
};  

#endif // !_BOARD_H_


