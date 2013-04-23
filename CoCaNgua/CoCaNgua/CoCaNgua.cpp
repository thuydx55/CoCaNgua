
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#include <iostream>

#include "Model.h"
#include "Light.h"
#include "mathlib.h"
#include "Camera.h"
#include "InputManager.h"
#include "Graphic.h"

#include "SelectPlayersScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "LoadingScene.h"


#define SHOW_GRID 1
#define SHOW_LIGHT_SOURCE 1

using namespace std;

void displayCB();
void reshapeCB(int w, int h);
void timerCB(int millisec);
void keyboardCB(unsigned char key, int x, int y);
void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);
void mousePassiveMotionCB(int x, int y);

const int   SCREEN_WIDTH    = 800;
const int   SCREEN_HEIGHT   = 600;
const float CAMERA_DISTANCE = 10.0f;
const int   TEXT_WIDTH      = 8;
const int   TEXT_HEIGHT     = 13;
const float DELTA_TIME      = 33;

///////////////////////////////////////////////////////////////////////////////
// initialize global variables
///////////////////////////////////////////////////////////////////////////////
bool initSharedMem()
{
  Graphic::inst().screenWidth = SCREEN_WIDTH;
  Graphic::inst().screenHeight = SCREEN_HEIGHT;

  //Graphic::inst().setAppScene(APP_GAME);

  return true;
}

///////////////////////////////////////////////////////////////////////////////
// initialize GLUT for windowing
///////////////////////////////////////////////////////////////////////////////
int initGLUT(int argc, char **argv)
{
  // GLUT stuff for windowing
  // initialization openGL window.
  // it is called before any other GLUT routine
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);   // display mode

  //   glutGameModeString("800x600:16@60");
  //   glutEnterGameMode();

  glutInitWindowSize(Graphic::inst().screenWidth, Graphic::inst().screenHeight);  // window size
  glutInitWindowPosition(400, 100);               // window location

  // finally, create a window with openGL context
  // Window will not displayed until glutMainLoop() is called
  // it returns a unique ID
  int handle = glutCreateWindow("Assignment - 08. Co Ca Ngua");     // param is the title of window

  // register GLUT callback functions
  glutDisplayFunc(displayCB);
  glutTimerFunc(DELTA_TIME, timerCB, 0);             // redraw only every given millisec
  glutReshapeFunc(reshapeCB);
  glutKeyboardFunc(keyboardCB);
  glutMouseFunc(mouseCB);
  glutMotionFunc(mouseMotionCB);
  glutPassiveMotionFunc(mousePassiveMotionCB);

  return handle;
}

///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL
// disable unused features
///////////////////////////////////////////////////////////////////////////////
void initGL()
{
  glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

  // enable /disable features
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_CULL_FACE);

  // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
  //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  //glEnable(GL_COLOR_MATERIAL);

  glClearColor(0.3, 0.3, 0.3, 1);                   // background color
  glClearStencil(0);                          // clear stencil buffer
  glClearDepth(1.0f);                         // 0 is near, 1 is far
  glDepthFunc(GL_LEQUAL);

  Light::inst().setPosition(GameScene::inst().lightPosition[0], GameScene::inst().lightPosition[1], 
    GameScene::inst().lightPosition[2], GameScene::inst().lightPosition[3]);
  Light::inst().updateLight();

  float _position[4] = {0, 0, 5, 1};
  float _ambient[4] = {0.2, 0.2, 0.2, 1.0};
  float _diffuse[4] = {0.7, 0.7, 0.7, 1.0};
  float _specular[4] = {1.0, 1.0, 1.0, 1.0};

  glLightfv(GL_LIGHT1, GL_POSITION, _position);
  glLightfv(GL_LIGHT1, GL_AMBIENT,  _ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  _diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, _specular);
}

/* ----------------------------------------------------------------------- */
/* Function    : void myDisplay( void )
*
* Description : This function gets called everytime the window needs to
*               be redrawn.
*
* Parameters  : void
*
* Returns     : void
*/

void displayCB( void )  {

  glStencilMask(0xffffffff);
  glClearStencil(0x4);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  
  switch (Graphic::inst().getAppScene())
  {
  case APP_GAME:
    glEnable(GL_LIGHTING);
    GameScene::inst().loop();
    break;
  case APP_MENU:
    glDisable(GL_LIGHTING);
    MainMenuScene::inst().loop();
    break;
  case APP_OPTION:
    break;
  case APP_SELECT:
	  glDisable(GL_LIGHTING);
	  SelectPlayersScene::inst().loop();
    break;
  case APP_ABOUT:
    break;
  case APP_LOADING:
    glDisable(GL_LIGHTING);
    LoadingScene::inst().loop();
    break;
  default:
    break;
  }

  glutSwapBuffers();
}

void reshapeCB(int width, int height) {
  Graphic::inst().screenWidth = width;
  Graphic::inst().screenHeight = height;
  // set viewport to be the entire window
  glViewport(0, 0, width, height);

  // set perspective viewing frustum
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, (float)Graphic::inst().screenWidth/Graphic::inst().screenHeight, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

  // switch to modelview matrix in order to set scene
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(Camera::inst().eye.x, Camera::inst().eye.y, Camera::inst().eye.z,
            Camera::inst().at.x, Camera::inst().at.y, Camera::inst().at.z,
            0, 1, 0 ); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}

/*
* Callback function for mouse event
*/
void mouseCB(int button, int state, int x, int y) {
  Mouse::inst().processMouse(button, state, x, y);
}

/*
* Callback function for animation motion event
*/
void mouseMotionCB(int x, int y) {

  Mouse::inst().processMouseMotion(x, y);
  //if(mouseMiddleDown)
  //{
  //  cameraDistance -= (y - mouseY) * 0.2f;
  //  mouseY = y;
  //}
}

void mousePassiveMotionCB(int x, int y)
{
  Mouse::inst().processMousePassiveMotion(x, y);
}

void keyboardCB(unsigned char key,int x,int y)
{
  KeyBoard::inst().processKey(key);
}

void timerCB(int value) {
  GameScene::inst().lightAngle+=0.3;

  glutPostRedisplay(); //Redraw scene

  glutTimerFunc(DELTA_TIME, timerCB, 0); //Call update in 5 milliseconds
}

int main( int argc, char *argv[] )  {
  // init global vars
  initSharedMem();

  // init GLUT and GL
  initGLUT(argc, argv);
  initGL();

  LoadingScene::inst().initSprite();

  glutMainLoop( );
}



/* ----------------------------------------------------------------------- */

