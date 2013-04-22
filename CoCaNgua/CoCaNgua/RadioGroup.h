#ifndef _CG_RADIO_GROUP_H_
#define _CG_RADIO_GROUP_H_

#include <vector>

#include "ToggleButton.h"
#include "Constants.h"

using namespace std;

class RadioGroup
{
  vector<ToggleButton*> mToggle;
  GLSYNTHESIZE(int, mSelectedIndex, SelectedIndex);
public:
  RadioGroup(void);
  RadioGroup(vector<ToggleButton*> pToggle);
  ~RadioGroup(void);

  static RadioGroup* create(ToggleButton* item, ...);
  static RadioGroup* createWithItems(ToggleButton* firstItem, va_list args);

  void addSubItem(ToggleButton* item);

  void click(int x, int y);

  Rect boundingbox();
};

#endif // !_CG_RADIO_GROUP_H_

