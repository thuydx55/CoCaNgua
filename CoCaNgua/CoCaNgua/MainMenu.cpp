#include "MainMenu.h"


MainMenu::MainMenu(void)
{

}

MainMenu& MainMenu::inst()
{
  static MainMenu instance;
  return instance;
}

void MainMenu::initSprite()
{
  mBackground = new Sprite2D("img/background.png");
  mBackground->setAnchorPoint(Vector2(-0.5, -0.5));

  mStart = new Button("img/Button_Start.png", "img/Button_Start_Hover.png", "img/Button_Start_Hover.png");
  mStart->setPosition(Vector2(478, 242));

  mOption = new Button("img/Button_Option.png", "img/Button_Option_Hover.png", "img/Button_Option_Hover.png");
  mOption->setPosition(Vector2(580, 244));

  mAbout = new Button("img/Button_About.png", "img/Button_About_Hover.png", "img/Button_About_Hover.png");
  mAbout->setPosition(Vector2(675, 249));

  mQuit = new Button("img/Button_Quit.png", "img/Button_Quit_Hover.png", "img/Button_Quit_Hover.png");
  mQuit->setPosition(Vector2(694, 104));
}

void MainMenu::drawScene()
{
  mBackground->drawImg();
  mStart->drawImg();
  mOption->drawImg();
  mAbout->drawImg();
  mQuit->drawImg();
}

void MainMenu::loop()
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

void MainMenu::processMouseBegan(int x, int y )
{
  if (mStart->boundingbox().containsPoint(Vector2(x, y)))
    mStart->setButtonState(BUTTON_PRESSED);
  else
    mStart->setButtonState(BUTTON_NORMAL);
}

void MainMenu::processMouseEnded( int x, int y )
{
  if (mStart->boundingbox().containsPoint(Vector2(x, y)))
    Graphic::inst().setAppScene(APP_GAME);
  else if(mStart->getButtonState() != BUTTON_DISABLE) mStart->setButtonState(BUTTON_NORMAL);
}


void MainMenu::processMousePassiveMotion( int x, int y )
{
  if (mStart->boundingbox().containsPoint(Vector2(x, y)))
    mStart->setButtonState(BUTTON_HOVER);
  else
    mStart->setButtonState(BUTTON_NORMAL);
}

MainMenu::~MainMenu(void)
{
}
