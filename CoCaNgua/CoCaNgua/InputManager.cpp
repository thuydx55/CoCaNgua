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
    GameScene::inst().rollDice(key-48);
    break;
  case 'm':
    GameScene::inst().rollDice(rand() % 6 +1);
    break;
  case 'p':
    cout << Light::inst().getPosition()[0] << ' ' << Light::inst().getPosition()[1] << ' ' << Light::inst().getPosition()[2] << ' ' << Light::inst().getPosition()[3] << endl;
    break;
  case 'd':
    GameScene::inst().mDieIsDrawn = !GameScene::inst().mDieIsDrawn;
    if (GameScene::inst().mDieIsDrawn)
      Light::inst().setDiffuseOffset(0.5);
    else
      Light::inst().setDiffuseOffset(0);
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
      if (!GameScene::inst().processMouseBegan(x, y))
      {
        mousedw(x, y, button);
      }
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
  }
}

void Mouse::processMousePassiveMotion( int x, int y )
{
  switch (Graphic::inst().getAppScene())
  {
  case APP_MENU:
    MainMenuScene::inst().processMousePassiveMotion(x, Graphic::inst().screenHeight-y);
  default:
    break;
  }
}

Mouse::~Mouse( void )
{

}

void Mouse::list_hits(GLint hits, GLuint *names)
{
  int i;

  /*
  For each hit in the buffer are allocated 4 bytes:
  1. Number of hits selected (always one,
  beacuse when we draw each object
  we use glLoadName, so we replace the
  prevous name in the stack)
  2. Min Z
  3. Max Z
  4. Name of the hit (glLoadName)
  */

  //printf("%d hits:\n", hits);

  GLubyte max= 0;
  int name = -1;

  for (i = 0; i < hits; i++) {
    //printf(	"Number: %d\n"
    //  "Min Z: %d\n"
    //  "Max Z: %d\n"
    //  "Name on stack: %d\n",
    //  (GLubyte)names[i * 4],
    //  (GLubyte)names[i * 4 + 1],
    //  (GLubyte)names[i * 4 + 2],
    //  (GLubyte)names[i * 4 + 3]
    //);

    if ((GLubyte)names[i*4+1] + (GLubyte)names[i*4+2] >= max) {
      max = (GLubyte)names[i*4+1] + (GLubyte)names[i*4+2];
      name = (int)names[i*4+3];
    }
  }

  GameScene::inst().movePiece(name);
}

void Mouse::gl_select(int x, int y)
{
  GLuint buff[64] = {0};
  GLint hits, view[4];

  /*
  This choose the buffer where store the values for the selection data
  */
  glSelectBuffer(64, buff);

  /*
  This retrieve info about the viewport
  */
  glGetIntegerv(GL_VIEWPORT, view);

  /*
  Switching in selecton mode
  */
  glRenderMode(GL_SELECT);

  /*
  Clearing the name's stack
  This stack contains all the info about the objects
  */
  glInitNames();

  /*
  Now fill the stack with one element (or glLoadName will generate an error)
  */
  glPushName(0);

  /*
  Now modify the vieving volume, restricting selection area around the cursor
  */
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  /*
  restrict the draw to an area around the cursor
  */
  gluPickMatrix(x, y, 1.0, 1.0, view);
  gluPerspective(60.0f, (float)Graphic::inst().screenWidth/Graphic::inst().screenHeight, 10.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

  /*
  Draw the objects onto the screen
  */
  glMatrixMode(GL_MODELVIEW);

  /*
  draw only the names in the stack, and fill the array
  */
  glutSwapBuffers();
  GameScene::inst().loop();

  /*
  Do you remeber? We do pushMatrix in PROJECTION mode
  */
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  /*
  get number of objects drawed in that area
  and return to render mode
  */
  hits = glRenderMode(GL_RENDER);

  /*
  Print a list of the objects
  */
  list_hits(hits, buff);

  /*
  uncomment this to show the whole buffer
  * /
  gl_selall(hits, buff);
  */

  glMatrixMode(GL_MODELVIEW);
}

void Mouse::mousedw(int x, int y, int but)
{
  //printf("Mouse button %d pressed at %d %d\n", but, x, y);
  gl_select(x, Graphic::inst().screenHeight-y); //Important: gl (0,0) ist bottom left but window coords (0,0) are top left so we have to change this!
}
