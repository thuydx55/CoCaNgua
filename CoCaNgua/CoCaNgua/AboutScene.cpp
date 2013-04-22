#include "AboutScene.h"
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
  mBackground = new Sprite2D("img/background.png");
  mBackground->setAnchorPoint(Vector2(-0.5, -0.5));

  mStart = new ToggleButton("img/ToggleON.png", "img/ToggleOFF.png", "img/ToggleOFF.png");
  mStart->setPosition(Vector2(478, 242));

  mOption = new ToggleButton("img/ToggleON.png", "img/ToggleOFF.png", "img/ToggleOFF.png");
  mOption->setPosition(Vector2(580, 244));

  mAbout = new ToggleButton("img/ToggleON.png", "img/ToggleOFF.png", "img/ToggleOFF.png");
  mAbout->setPosition(Vector2(675, 249));

  mQuit = new ToggleButton("img/ToggleON.png", "img/ToggleOFF.png", "img/ToggleOFF.png");
  mQuit->setPosition(Vector2(694, 104));
}

void AboutScene::drawScene()
{
  mBackground->drawImg();
  mStart->drawImg();
  mOption->drawImg();
  mAbout->drawImg();
  mQuit->drawImg();
}

void AboutScene::loop()
{
  cout<<"about scene loop"<<endl;
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
  if (mStart->boundingbox().containsPoint(Vector2(x, y)))
  {
    mStart->click();
  }


  // Option Button
  if (mOption->boundingbox().containsPoint(Vector2(x, y)))
  {
    mOption->click();
  }

  // About Button
  if (mAbout->boundingbox().containsPoint(Vector2(x, y)))
  {
    mAbout->click();
  }

  // Quit Button
  if (mQuit->boundingbox().containsPoint(Vector2(x, y)))
  {
    mQuit->click();
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
