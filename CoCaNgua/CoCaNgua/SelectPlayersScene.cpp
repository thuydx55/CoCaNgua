#include "SelectPlayersScene.h"
#include <iostream>
using namespace std;

AboutScene::AboutScene(void)
{

}

AboutScene& AboutScene::inst()
{
  static AboutScene instance;
  return instance;
}

void AboutScene::initSprite()
{
  mBackground = Sprite2D::create("img/select_piece/background.png");
  mBackground->setAnchorPoint(Vector2(-0.5, -0.5));
  
  mBtnStart = Sprite2D::create("img/select_piece/StartBtn.png");
  mBtnStart->setAnchorPoint(Vector2(0.5, -0.5));
  mBtnStart->setPosition(Vector2(0, 0));

  mBtnBack = Sprite2D::create("img/select_piece/BackBtn.png");
  mBtnBack->setAnchorPoint(Vector2(-0.5, -0.5));
  mBtnStart->setPosition(Vector2(800, 0));

  Sprite2D* humanON     = Sprite2D::create("img/select_piece/HumanON.png");
  Sprite2D* humanOFF    = Sprite2D::create("img/select_piece/HumanOFF.png");

  Sprite2D* computerON  = Sprite2D::create("img/select_piece/ComputerON.png");
  Sprite2D* computerOFF = Sprite2D::create("img/select_piece/ComputerOFF.png");

  Sprite2D* disableOFF  = Sprite2D::create("img/select_piece/DisableOFF.png");
  Sprite2D* disableON   = Sprite2D::create("img/select_piece/DisableON.png");

  for (int i = 0; i < 4; i++)
  {
    mFrame[i] = new Sprite2D("img/select_piece/frame.png");
    mFrame[i]->setPosition(Vector2(230, 433));

    mHuman[i] = new ToggleButton(humanON, humanOFF, humanOFF);
    mHuman[i]->setPosition(Vector2(205, 477));
    mHuman[i]->setAnchorPoint(Vector2(-0.5, 0));

    mComputer[i] = new ToggleButton(computerON, computerOFF, computerOFF);
    mComputer[i]->setPosition(Vector2(205, 426));
    mComputer[i]->setAnchorPoint(Vector2(-0.5, 0));
    mComputer[i]->setDisable(true);

    mDisable[i] = new ToggleButton(disableON, disableOFF, disableOFF);
    mDisable[i]->setPosition(Vector2(205, 375));
    mDisable[i]->setAnchorPoint(Vector2(-0.5, 0));

    mPlayer[i] = RadioGroup::create(mHuman[i], mComputer[i], mDisable[i], NULL); 
  }

  mFrame[1]->setPosition(Vector2(575, 433));
  mHuman[1]   ->setPosition(Vector2(550, 477));
  mComputer[1]->setPosition(Vector2(550, 426));
  mDisable[1] ->setPosition(Vector2(550, 375));

  mFrame[2]->setPosition(Vector2(230, 184));
  mHuman[2]   ->setPosition(Vector2(205, 227));
  mComputer[2]->setPosition(Vector2(205, 176));
  mDisable[2] ->setPosition(Vector2(205, 125));

  mFrame[3]->setPosition(Vector2(575, 184));
  mHuman[3]   ->setPosition(Vector2(550, 227));
  mComputer[3]->setPosition(Vector2(550, 176));
  mDisable[3] ->setPosition(Vector2(550, 125));
}

void AboutScene::drawScene()
{
  mBackground->drawImg();
  mBtnStart->drawImg();
  mBtnBack->drawImg();

  for (int i = 0; i < 4; i++)
  {
    mFrame[i]->drawImg();
    mHuman[i]->drawImg();
    mComputer[i]->drawImg();
    mDisable[i]->drawImg(); 
  }

  //Rect bound = mPlayer[0]->boundingbox();
  //glBegin(GL_LINE_LOOP);
  //glVertex3f(bound.getMinX(), bound.getMinY(), 1);
  //glVertex3f(bound.getMinX(), bound.getMaxY(), 1);
  //glVertex3f(bound.getMaxX(), bound.getMaxY(), 1);
  //glVertex3f(bound.getMaxX(), bound.getMinY(), 1);
  //glEnd();
}

void AboutScene::loop()
{
  //cout<<"about scene loop"<<endl;
	glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  {
    glLoadIdentity();
    glOrtho(0, Graphic::inst().screenWidth,
      0, Graphic::inst().screenHeight,
      -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    {
      glLoadIdentity();
      glDisable(GL_CULL_FACE);

      glClear(GL_DEPTH_BUFFER_BIT);

      drawScene();
    }
    glPopMatrix();

    // Making sure we can render 3d again
    glMatrixMode(GL_PROJECTION);
  }

  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void AboutScene::processMouseBegan(int x, int y )
{
  // Start Button
  for (int i = 0; i < 4; i++)
  {
    if (mPlayer[i]->boundingBox().containsPoint(Vector2(x, y)))
    {
      mPlayer[i]->click(x, y);
    } 
  }
  if (mBtnStart->boundingBox().containsPoint(Vector2(x, y)))
  {
    Graphic::inst().setAppScene(APP_GAME);
  } 
  if (mBtnBack->boundingBox().containsPoint(Vector2(x, y)))
  {
    Graphic::inst().setAppScene(APP_MENU);
  } 
}

void AboutScene::processMouseEnded( int x, int y )
{
  
}


void AboutScene::processMousePassiveMotion( int x, int y )
{}

AboutScene::~AboutScene(void)
{
}
