#include "RadioGroup.h"


RadioGroup::RadioGroup(void)
{
}

RadioGroup::RadioGroup(ToggleButton* pTg1, ToggleButton* pTg2, ToggleButton* pTg3)
{
  mToggle[0] = pTg1;
  mToggle[1] = pTg2;
  mToggle[2] = pTg3;
}

Rect RadioGroup::boundingbox()
{
  Rect bounding;
  for (int i = 0; i < 3; i++)
  {
    bounding = bounding + mToggle[i]->boundingbox();
  }

  return bounding;
}

RadioGroup::~RadioGroup(void)
{
}
