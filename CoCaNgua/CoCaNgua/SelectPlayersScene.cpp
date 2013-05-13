#include "SelectPlayersScene.h"

#include "GameScene.h"

SelectPlayersScene::SelectPlayersScene(void)
{

}

SelectPlayersScene& SelectPlayersScene::inst()
{
  static SelectPlayersScene instance;
  return instance;
}

void SelectPlayersScene::initSprite()
{
  mBackground = Sprite2D::create("img/select_piece/background.png");
  mBackground->setAnchorPoint(Vector2(-0.5, -0.5));
  
  mBtnStart = Button::create("img/select_piece/btnStart.png", "img/select_piece/btnStartHover.png");
  mBtnStart->setPosition(Vector2(686, 52.5));

  mBtnBack = Button::create("img/select_piece/btnBack.png", "img/select_piece/btnBackHover.png");
  mBtnBack->setPosition(Vector2(72.5, 542.5));

  char buffer[100];
  for (int i = 0; i < 4; i++)
  {
    sprintf_s(buffer, "img/select_piece/piece%d.png", i);
    mPiece[i] = Sprite2D::create(buffer);
  }

  Sprite2D* human[3];
  Sprite2D* computer[3];
  Sprite2D* disable[3];

  human[0]    = Sprite2D::create("img/select_piece/HumanON.png");
  human[1]    = Sprite2D::create("img/select_piece/HumanOFF.png");
  human[2]    = Sprite2D::create("img/select_piece/HumanDISABLE.png");

  computer[0] = Sprite2D::create("img/select_piece/ComputerON.png");
  computer[1] = Sprite2D::create("img/select_piece/ComputerOFF.png");
  computer[2] = Sprite2D::create("img/select_piece/ComputerDISABLE.png");

  disable[0]  = Sprite2D::create("img/select_piece/DisableON.png");
  disable[1]  = Sprite2D::create("img/select_piece/DisableOFF.png");
  disable[2]  = Sprite2D::create("img/select_piece/DisableDISABLE.png");

  for (int i = 0; i < 4; i++)
  {
    mFrame[i] = new Sprite2D("img/select_piece/frame.png");

    mHuman[i] = new ToggleButton(human[0], human[1], human[2]);
    mHuman[i]->setAnchorPoint(Vector2(-0.5, 0));

    mComputer[i] = new ToggleButton(computer[0], computer[1], computer[2]);
    mComputer[i]->setAnchorPoint(Vector2(-0.5, 0));
    mComputer[i]->setDisable(true);

    mDisable[i] = new ToggleButton(disable[0], disable[1], disable[2]);
    mDisable[i]->setAnchorPoint(Vector2(-0.5, 0));

    mPlayer[i] = RadioGroup::create(mHuman[i], mComputer[i], mDisable[i], NULL); 
  }

  mFrame[0]   ->setPosition(Vector2(239, 405));
  mHuman[0]   ->setPosition(Vector2(227, 457));
  mComputer[0]->setPosition(Vector2(227, 399));
  mDisable[0] ->setPosition(Vector2(227, 348));

  mFrame[1]   ->setPosition(Vector2(562, 405));
  mHuman[1]   ->setPosition(Vector2(550, 457));
  mComputer[1]->setPosition(Vector2(550, 399));
  mDisable[1] ->setPosition(Vector2(550, 348));

  mFrame[2]   ->setPosition(Vector2(239, 205));
  mHuman[2]   ->setPosition(Vector2(227, 257));
  mComputer[2]->setPosition(Vector2(227, 199));
  mDisable[2] ->setPosition(Vector2(227, 148));

  mFrame[3]   ->setPosition(Vector2(562, 205));
  mHuman[3]   ->setPosition(Vector2(550, 257));
  mComputer[3]->setPosition(Vector2(550, 199));
  mDisable[3] ->setPosition(Vector2(550, 148));

  mPiece[0]->setPosition(Vector2(156.5, 400));
  mPiece[1]->setPosition(Vector2(480.5, 400));
  mPiece[2]->setPosition(Vector2(156.5, 200));
  mPiece[3]->setPosition(Vector2(480.5, 200));
}

void SelectPlayersScene::drawScene()
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
    mPiece[i]->drawImg();
  }

  //Rect bound = mPlayer[0]->boundingbox();
  //glBegin(GL_LINE_LOOP);
  //glVertex3f(bound.getMinX(), bound.getMinY(), 1);
  //glVertex3f(bound.getMinX(), bound.getMaxY(), 1);
  //glVertex3f(bound.getMaxX(), bound.getMaxY(), 1);
  //glVertex3f(bound.getMaxX(), bound.getMinY(), 1);
  //glEnd();
}

void SelectPlayersScene::loop()
{
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

void SelectPlayersScene::processMouseBegan(int x, int y )
{
  // Start Button
  for (int i = 0; i < 4; i++)
  {
    if (mPlayer[i]->boundingBox().containsPoint(Vector2(x, y)))
    {
      mPlayer[i]->click(x, y);
    } 
  }
}

void SelectPlayersScene::processMouseEnded( int x, int y )
{
  if (mBtnStart->boundingbox().containsPoint(Vector2(x, y)))
  {
    Graphic::inst().setAppScene(APP_GAME);
    for (int i = 0; i < 4; i++)
    {
      if (mPlayer[i]->getSelectedIndex() == 2)    // Disable
        GameScene::inst().setDisablePiece(i);
    }
  } 
  if (mBtnBack->boundingbox().containsPoint(Vector2(x, y)))
  {
    Graphic::inst().setAppScene(APP_MENU);
  } 
}

void SelectPlayersScene::processMousePassiveMotion( int x, int y )
{
  if (mBtnStart->getButtonState() != BUTTON_DISABLE)
  {
    if (mBtnStart->boundingbox().containsPoint(Vector2(x, y)))
      mBtnStart->setButtonState(BUTTON_HOVER);
    else
      mBtnStart->setButtonState(BUTTON_NORMAL); 
  }
  if (mBtnBack->getButtonState() != BUTTON_DISABLE)
  {
    if (mBtnBack->boundingbox().containsPoint(Vector2(x, y)))
      mBtnBack->setButtonState(BUTTON_HOVER);
    else
      mBtnBack->setButtonState(BUTTON_NORMAL); 
  }
}

SelectPlayersScene::~SelectPlayersScene(void)
{
  delete mBackground;
  delete mBtnStart;
  delete mBtnBack;

  for (int i = 0; i < 4; i++)
  {
    delete mFrame[i];
    delete mHuman[i];
    delete mDisable[i];
    delete mComputer[i];
  }
}
