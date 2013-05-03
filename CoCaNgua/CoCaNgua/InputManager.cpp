#include "InputManager.h"


KeyBoard::KeyBoard(void)
{
  fullscreen = false;
}

KeyBoard& KeyBoard::inst()
{
  static KeyBoard instance;
  return instance;
}

void KeyBoard::processKey( unsigned char key )
{
  switch(key){
  case '~':
    fullscreen = !fullscreen;
    if (fullscreen) {
      old_x = glutGet(GLUT_WINDOW_X);
      old_y = glutGet(GLUT_WINDOW_Y);
      old_width = glutGet(GLUT_WINDOW_WIDTH);
      old_height = glutGet(GLUT_WINDOW_HEIGHT);
      glutFullScreen();
    } else {
      glutReshapeWindow(old_width, old_height);
      glutPositionWindow(old_x, old_y);
    }
    break;
  case 's':
    SOIL_save_screenshot(
      "screenshot.bmp",
      SOIL_SAVE_TYPE_BMP,
      0, 0, Graphic::inst().screenWidth, Graphic::inst().screenHeight
      );
    break;
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
    GameScene::inst().predictNextMove(key-48);
    break;
  case 'm':
    GameScene::inst().predictNextMove(rand() % 6 +1);
    break;
  case 'p':
    cout << Light::inst().getPosition()[0] << ' ' << Light::inst().getPosition()[1] << ' ' << Light::inst().getPosition()[2] << ' ' << Light::inst().getPosition()[3] << endl;
    break;
  case 'd':
    GameScene::inst().mDieIsDrawn = !GameScene::inst().mDieIsDrawn;
    break;

  case 'r':
    GameScene::inst().mDice->rollDie();
    break;
  case 't':
    GameScene::inst().mDice->setState(DIE_WAITING);

  default:
    break;
  }
}

KeyBoard::~KeyBoard(void)
{
}

Mouse::Mouse( void )
{
  mouseLeftDown = mouseRightDown = mouseMiddleDown = false;
  mouseX = mouseY = 0;
}

Mouse& Mouse::inst()
{
  static Mouse instance;
  return instance;
}

void Mouse::processMouse( int button, int state, int x, int y )
{
  if (Graphic::inst().getAppScene() == APP_GAME)
  {
    Camera::inst().save(x, y);

    if(button == GLUT_LEFT_BUTTON)
    {
      if(state == GLUT_DOWN)
        mouseLeftDown = true;
      else if(state == GLUT_UP)
        mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
      if(state == GLUT_DOWN)
        mouseRightDown = true;
      else if(state == GLUT_UP)
        mouseRightDown = false;
    }

    else if(button == GLUT_MIDDLE_BUTTON)
    {
      if(state == GLUT_DOWN)
        mouseMiddleDown = true;
      else if(state == GLUT_UP)
        mouseMiddleDown = false;
    }

    if 	((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
      GameScene::inst().processMouseBegan(x, Graphic::inst().screenHeight-y);
    } 
  }
  else if (Graphic::inst().getAppScene() == APP_MENU)
  {
    if(button == GLUT_LEFT_BUTTON)
    {
      if(state == GLUT_DOWN)
        MainMenuScene::inst().processMouseBegan(x, Graphic::inst().screenHeight-y);
      else if(state == GLUT_UP)
        MainMenuScene::inst().processMouseEnded(x, Graphic::inst().screenHeight-y);
    }
  }
  else if (Graphic::inst().getAppScene() == APP_SELECT)
  {
    if(button == GLUT_LEFT_BUTTON)
    {
      if(state == GLUT_DOWN)
		    SelectPlayersScene::inst().processMouseBegan(x, Graphic::inst().screenHeight-y);
      else if(state == GLUT_UP)
        SelectPlayersScene::inst().processMouseEnded(x, Graphic::inst().screenHeight-y);
    }
  }
}

void Mouse::processMouseMotion( int x, int y )
{
  if(mouseRightDown)
  {
    Camera::inst().rotate(x, y);
    GameScene::inst().mAutoCam = false;
  }
}

void Mouse::processMousePassiveMotion( int x, int y )
{
  switch (Graphic::inst().getAppScene())
  {
  case APP_MENU:
    MainMenuScene::inst().processMousePassiveMotion(x, Graphic::inst().screenHeight-y);
    break;
  case APP_GAME:
    GameScene::inst().processMousePassiveMotion(x, Graphic::inst().screenHeight-y);
    break;
  default:
    break;
  }
}

Mouse::~Mouse( void )
{

}
