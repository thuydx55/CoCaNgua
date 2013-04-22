#include "RadioGroup.h"


RadioGroup::RadioGroup(void)
{
  mSelectedIndex = -1;
}

RadioGroup::RadioGroup( vector<ToggleButton*> pToggle )
{
  mSelectedIndex = 0;
  mToggle = pToggle;
}

RadioGroup* RadioGroup::create(ToggleButton* item, ...)
{
  va_list args;
  va_start(args,item);

  RadioGroup *pRet = RadioGroup::createWithItems(item, args);

  va_end(args);

  return pRet;
}

RadioGroup* RadioGroup::createWithItems( ToggleButton* firstItem, va_list args )
{
  vector<ToggleButton*> vectorToggle;
  if( firstItem )
  {
    vectorToggle.push_back(firstItem);
    ToggleButton* i = va_arg(args, ToggleButton*);
    while(i)
    {
      vectorToggle.push_back(i);
      i = va_arg(args, ToggleButton*);
    }
  }
  RadioGroup* pRet = new RadioGroup(vectorToggle);
  firstItem->setToggleState(TOGGLE_ON);
  return pRet;
}

void RadioGroup::addSubItem( ToggleButton* item )
{

}

void RadioGroup::click(int x, int y)
{
  for (int i = 0; i < mToggle.size(); i++)
  {
    if (mToggle[i]->getToggleState() == TOGGLE_OFF &&
      mToggle[i]->boundingbox().containsPoint(Vector2(x, y)))
    {
      mToggle[i]->click();
      mSelectedIndex = i;
      for (int j = 0; j < mToggle.size(); j++)
      {
        if (i == j)
          continue;
        if (mToggle[j]->getToggleState() != TOGGLE_DISABLE)
          mToggle[j]->setToggleState(TOGGLE_OFF);
      }
    }
  }
}

Rect RadioGroup::boundingBox()
{
  Rect bounding = mToggle[0]->boundingbox();
  for (int i = 1; i < mToggle.size(); i++)
  {
    bounding = bounding + mToggle[i]->boundingbox();
  }
  return bounding;
}


RadioGroup::~RadioGroup(void)
{
}
