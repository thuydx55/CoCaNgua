#ifndef _CG_RADIO_GROUP_H_
#define _CG_RADIO_GROUP_H_

#include "ToggleButton.h"

class RadioGroup
{
  ToggleButton* mToggle[3];
public:
  RadioGroup(void);
  RadioGroup(ToggleButton* pTg1, ToggleButton* pTg2, ToggleButton* pTg3);
  ~RadioGroup(void);

  Rect boundingbox();
};

#endif // !_CG_RADIO_GROUP_H_

