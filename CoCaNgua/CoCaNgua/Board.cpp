#include "Board.h"

Board::Board(void)
{
}

void Board::drawModel()
{
  Model::drawModel();

  float x, y, z;
  getCenter(x, y, z);

  glPushMatrix();
  // Move Object to coordinate origin
  glTranslatef(-x, -y, -z);
  glPushMatrix();
  glTranslated(mPos.x - mAnchor.x*getWidth(), 
    mPos.y - mAnchor.y*getHeight(),
    mPos.z - mAnchor.z*getLength());

  draw();
  glPopMatrix();
  glPopMatrix();
}

Board::~Board(void)
{
}
