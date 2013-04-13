/* Module      : MainFile.cpp
* Author      : 
* Email       : 
* Course      : Computer Graphics
*
* Description : 
*
*
* Date        : 
*
* History:
* Revision      Date          Changed By
* --------      ----------    ----------
* 01.00         ?????          ???
* First release.
*
*/

/* -- INCLUDE FILES ------------------------------------------------------ */
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#include <iostream>

#include "Model.h"
#include "Light.h"
#include "mathlib.h"
#include "Camera.h"
#include "Game.h"

#define SHOW_GRID 1
#define SHOW_LIGHT_SOURCE 1

using namespace std;

// GLUT CALLBACK functions
void displayCB();
void reshapeCB(int w, int h);
void timerCB(int millisec);
void keyboardCB(unsigned char key, int x, int y);
void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);

void initGL();
int  initGLUT(int argc, char **argv);
bool initSharedMem();

/* -- CONSTANT ----------------------------------------------------------- */
const int   SCREEN_WIDTH    = 800;
const int   SCREEN_HEIGHT   = 600;
const float CAMERA_DISTANCE = 10.0f;
const int   TEXT_WIDTH      = 8;
const int   TEXT_HEIGHT     = 13;
const float DELTA_TIME      = 33;
/* -- DATA STRUCTURES ---------------------------------------------------- */

/* -- GLOBAL VARIABLES --------------------------------------------------- */

int screenWidth;
int screenHeight;
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;


/* -- LOCAL VARIABLES ---------------------------------------------------- */


///////////////////////////////////////////////////////////////////////////////
// initialize global variables
///////////////////////////////////////////////////////////////////////////////
bool initSharedMem()
{
  screenWidth = SCREEN_WIDTH;
  screenHeight = SCREEN_HEIGHT;

  mouseLeftDown = mouseRightDown = mouseMiddleDown = false;
  mouseX = mouseY = 0;
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

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode

  //   glutGameModeString("800x600:16@60");
  //   glutEnterGameMode();

  glutInitWindowSize(screenWidth, screenHeight);  // window size
  glutInitWindowPosition(100, 100);               // window location

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

  Light::inst().setPosition(Game::inst().lightPosition[0], Game::inst().lightPosition[1], 
    Game::inst().lightPosition[2], Game::inst().lightPosition[3]);
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

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  Game::inst().loop();

  glutSwapBuffers();
}

void reshapeCB(int width, int height) {
  screenWidth = width;
  screenHeight = height;
  // set viewport to be the entire window
  glViewport(0, 0, (GLsizei)screenWidth, (GLsizei)screenHeight);

  // set perspective viewing frustum
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, (float)(screenWidth)/screenHeight, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

  // switch to modelview matrix in order to set scene
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(Camera::inst().eye.x, Camera::inst().eye.y, Camera::inst().eye.z,
            Camera::inst().at.x, Camera::inst().at.y, Camera::inst().at.z,
            0, 1, 0 ); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}

void list_hits(GLint hits, GLuint *names)
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

  Game::inst().demoMove(name);

  //if (name == 3)
  //{
  //  dice->highlight(!dice->isHighlight());
  //}
  //if (name == 2)
  //{
  //  red[1]->highlight(!red[1]->isHighlight());
  //}

  printf("\n");
}

void gl_select(int x, int y)
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
  gluPerspective(60.0f, (float)(screenWidth)/screenHeight, 10.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

  /*
  Draw the objects onto the screen
  */
  glMatrixMode(GL_MODELVIEW);

  /*
  draw only the names in the stack, and fill the array
  */
  glutSwapBuffers();
  displayCB();

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

void mousedw(int x, int y, int but)
{
  //printf("Mouse button %d pressed at %d %d\n", but, x, y);
  gl_select(x,screenHeight-y); //Important: gl (0,0) ist bottom left but window coords (0,0) are top left so we have to change this!
}

/*
* Callback function for mouse event
*/
void mouseCB(int button, int state, int x, int y) {

  Camera::inst().save(x, y);

  if(button == GLUT_LEFT_BUTTON)
  {
    if(state == GLUT_DOWN)
    {
      mouseLeftDown = true;
    }
    else if(state == GLUT_UP)
      mouseLeftDown = false;
  }

  else if(button == GLUT_RIGHT_BUTTON)
  {
    if(state == GLUT_DOWN)
    {
      mouseRightDown = true;
    }
    else if(state == GLUT_UP)
      mouseRightDown = false;
  }

  else if(button == GLUT_MIDDLE_BUTTON)
  {
    if(state == GLUT_DOWN)
    {
      mouseMiddleDown = true;
    }
    else if(state == GLUT_UP)
      mouseMiddleDown = false;
  }

  if 	((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
  {
    mousedw(x, y, button);
  }
}

/*
* Callback function for animation motion event
*/
void mouseMotionCB(int x, int y) {

  if(mouseRightDown)
  {
    Camera::inst().rotate(x, y);
  }
  //if(mouseMiddleDown)
  //{
  //  cameraDistance -= (y - mouseY) * 0.2f;
  //  mouseY = y;
  //}
}

void keyboardCB(unsigned char key,int x,int y)
{
  switch(key){
  case 's':
    SOIL_save_screenshot(
      "screenshot.bmp",
      SOIL_SAVE_TYPE_BMP,
      0, 0, screenWidth, screenHeight
      );
    break;

  case 'r':
    //cameraAngleX = cameraAngleY = 0;
    break;
  case 'm':
    Game::inst().demoMove(RED_1);
    break;

  default:
    break;
  }
}

void timerCB(int value) {
  Game::inst().lightAngle+=0.3;

  glutPostRedisplay(); //Redraw scene

  glutTimerFunc(DELTA_TIME, timerCB, 0); //Call update in 5 milliseconds
}


/* ----------------------------------------------------------------------- */
/* Function    : int main( int argc, char** argv )
*
* Description : This is the main function. It sets up the rendering
*               context, and then reacts to user events.
*
* Parameters  : int argc     : Number of command-line arguments.
*               char *argv[] : Array of command-line arguments.
*
* Returns     : int : Return code to pass to the shell.
*/

int main( int argc, char *argv[] )  {
  // init global vars
  initSharedMem();

  // init GLUT and GL
  initGLUT(argc, argv);
  initGL();

  // Initialize some things.
  Game::inst().initModel();

  //glutTimerFunc(DELTA_TIME, timerCB, 0);

  // Now that we have set everything up, loop responding to events.
  glutMainLoop( );
}



/* ----------------------------------------------------------------------- */

