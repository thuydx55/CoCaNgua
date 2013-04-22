#include "MainMenuScene.h"


MainMenuScene::MainMenuScene(void)
{

}

MainMenuScene& MainMenuScene::inst()
{
  static MainMenuScene instance;
  return instance;
}

void MainMenuScene::initSprite()
{
  mBackground = new Sprite2D("img/main_menu/background.png");
  mBackground->setAnchorPoint(Vector2(-0.5, -0.5));

  mStart = new Button("img/main_menu/Button_Start.png", 
                      "img/main_menu/Button_Start_Hover.png",
                      "img/main_menu/Button_Start_Hover.png");
  mStart->setPosition(Vector2(478, 242));

  mOption = new Button("img/main_menu/Button_Option.png", 
                       "img/main_menu/Button_Option_Hover.png",
                       "img/main_menu/Button_Option_Hover.png");
  mOption->setPosition(Vector2(580, 244));

  mAbout = new Button("img/main_menu/Button_About.png", 
                      "img/main_menu/Button_About_Hover.png",
                      "img/main_menu/Button_About_Hover.png");
  mAbout->setPosition(Vector2(675, 249));

  mQuit = new Button("img/main_menu/Button_Quit.png", 
                     "img/main_menu/Button_Quit_Hover.png", 
                     "img/main_menu/Button_Quit_Hover.png");
  mQuit->setPosition(Vector2(694, 104));
}

void MainMenuScene::drawScene()
{
  mBackground->drawImg();
  mStart->drawImg();
  mOption->drawImg();
  mAbout->drawImg();
  mQuit->drawImg();
}

void MainMenuScene::loop()
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

void MainMenuScene::processMouseBegan(int x, int y )
{
  // Start Button
  if (mStart->getButtonState() != BUTTON_DISABLE)
  {
    if (mStart->boundingbox().containsPoint(Vector2(x, y)))
      mStart->setButtonState(BUTTON_PRESSED);
    else
      mStart->setButtonState(BUTTON_NORMAL); 
  }

  // Option Button
  if (mOption->getButtonState() != BUTTON_DISABLE)
  {
    if (mOption->boundingbox().containsPoint(Vector2(x, y)))
      mOption->setButtonState(BUTTON_PRESSED);
    else
      mOption->setButtonState(BUTTON_NORMAL); 
  }

  // About Button
  if (mAbout->getButtonState() != BUTTON_DISABLE)
  {
    if (mAbout->boundingbox().containsPoint(Vector2(x, y)))
      mAbout->setButtonState(BUTTON_PRESSED);
    else
      mAbout->setButtonState(BUTTON_NORMAL); 
  }

  // Quit Button
  if (mQuit->getButtonState() != BUTTON_DISABLE)
  {
    if (mQuit->boundingbox().containsPoint(Vector2(x, y)))
      mQuit->setButtonState(BUTTON_PRESSED);
    else
      mQuit->setButtonState(BUTTON_NORMAL); 
  }
}

void MainMenuScene::processMouseEnded( int x, int y )
{
  // Start Button
  if (mStart->getButtonState() != BUTTON_DISABLE)
  {
    if (mStart->boundingbox().containsPoint(Vector2(x, y)))
      Graphic::inst().setAppScene(APP_SELECT);
    else 
      mStart->setButtonState(BUTTON_NORMAL); 
  }

  // Option Button
  if (mOption->getButtonState() != BUTTON_DISABLE)
  {
    if (mOption->boundingbox().containsPoint(Vector2(x, y)))
      Graphic::inst().setAppScene(APP_OPTION);
    else  
      mOption->setButtonState(BUTTON_NORMAL); 
  }

  // About Button
  if (mAbout->getButtonState() != BUTTON_DISABLE)
  {
    if (mAbout->boundingbox().containsPoint(Vector2(x, y)))
      Graphic::inst().setAppScene(APP_ABOUT);
    else 
      mAbout->setButtonState(BUTTON_NORMAL); 
  }

  // Quit Button
  if (mQuit->getButtonState() != BUTTON_DISABLE)
  {
    if (mQuit->boundingbox().containsPoint(Vector2(x, y)))
      exit(0);
    else  
      mQuit->setButtonState(BUTTON_NORMAL); 
  }
}


void MainMenuScene::processMousePassiveMotion( int x, int y )
{
  // Start Button
  if (mStart->getButtonState() != BUTTON_DISABLE)
  {
    if (mStart->boundingbox().containsPoint(Vector2(x, y)))
      mStart->setButtonState(BUTTON_HOVER);
    else
      mStart->setButtonState(BUTTON_NORMAL); 
  }

  // Option Button
  if (mOption->getButtonState() != BUTTON_DISABLE)
  {
    if (mOption->boundingbox().containsPoint(Vector2(x, y)))
      mOption->setButtonState(BUTTON_HOVER);
    else
      mOption->setButtonState(BUTTON_NORMAL); 
  }

  // About Button
  if (mAbout->getButtonState() != BUTTON_DISABLE)
  {
    if (mAbout->boundingbox().containsPoint(Vector2(x, y)))
      mAbout->setButtonState(BUTTON_HOVER);
    else
      mAbout->setButtonState(BUTTON_NORMAL); 
  }

  // Quit Button
  if (mQuit->getButtonState() != BUTTON_DISABLE)
  {
    if (mQuit->boundingbox().containsPoint(Vector2(x, y)))
      mQuit->setButtonState(BUTTON_HOVER);
    else
      mQuit->setButtonState(BUTTON_NORMAL); 
  }
}

MainMenuScene::~MainMenuScene(void)
{
}
