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

#define SHOW_GRID 0
#define SHOW_LIGHT_SOURCE 1

#define M_PI 3.141592654

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
void initLights();

void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
void drawString(const char *str, int x, int y, float color[4], void *font);
void drawString3D(const char *str, float pos[3], float color[4], void *font);

/* -- CONSTANT ----------------------------------------------------------- */
const int   SCREEN_WIDTH    = 800;
const int   SCREEN_HEIGHT   = 600;
const float CAMERA_DISTANCE = 10.0f;
const int   TEXT_WIDTH      = 8;
const int   TEXT_HEIGHT     = 13;
const float DELTA_TIME      = 33;

/* -- DATA STRUCTURES ---------------------------------------------------- */

enum army
{
  ARMY_RED,
  ARMY_BLUE,
  ARMY_GREEN,
  ARMY_YELLOW,
  ARMY_NONE
};

struct BoardPoint
{
  float x, y;
  army startPoint;

  BoardPoint() : x(0), y(0), startPoint(ARMY_NONE) {}; 
  BoardPoint(float _x, float _y, army _s) : x(_x), y(_y), startPoint(_s) {};
};


/* -- GLOBAL VARIABLES --------------------------------------------------- */

GLPoint3f           eyePoint(5.0, 20.0, 30.0);
GLPoint3f           lookAtPoint(0.0, 1.0, 0.0);

static GLfloat lightPosition[4] = {50, 50, 50, 1};

GLdouble X1, Y1, Z1;
GLdouble X2, Y2, Z2;

Model*              mBoard;
Model               *red[4], *blue[4], *green[4], *yellow[4];
Model*              dice;

static float lightAngle = 0.0, lightHeight = 20;

void *font = GLUT_BITMAP_8_BY_13;
int screenWidth;
int screenHeight;
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance;

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

  cameraAngleX = cameraAngleY = 0.0f;
  cameraDistance = CAMERA_DISTANCE;

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
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  glClearColor(0.3, 0.3, 0.3, 1);                   // background color
  glClearStencil(0);                          // clear stencil buffer
  glClearDepth(1.0f);                         // 0 is near, 1 is far
  glDepthFunc(GL_LEQUAL);

  Light::inst().setPosition(lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
}

void initModel( void )  {

  mBoard = new Model();
  red[0] = new Model();
  dice   = new Model();

  mBoard->loadModel("Models/board.obj");
  mBoard->setAnchorPoint(glp3f(0, 0.5, 0));

  dice->loadModel("Models/dice.obj");
  dice->setAnchorPoint(glp3f(0, -0.5, 0));

  red[0]->loadModel("Models/knight.obj");
  red[0]->setAnchorPoint(glp3f(0, -0.5, 0));
  
  for (int i = 0; i < 4; i++)
  {
    red[i] = new Model(red[0]);
    red[i]->setColorTint(1, 0, 0);    // RED

    green[i] = new Model(red[0]);
    green[i]->setColorTint(0, 1, 0);    // GREEN

    blue[i] = new Model(red[0]);
    blue[i]->setColorTint(0, 0, 1);    // BLUE

    yellow[i] = new Model(red[0]);
    yellow[i]->setColorTint(1, 1, 0);    // YELLOW
  }
}

///////////////////////////////////////////////////////////////////////////////
// set the projection matrix as perspective
///////////////////////////////////////////////////////////////////////////////
void toPerspective()
{
  // set viewport to be the entire window
  glViewport(0, 0, (GLsizei)screenWidth, (GLsizei)screenHeight);

  // set perspective viewing frustum
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, (float)(screenWidth)/screenHeight, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

  // switch to modelview matrix in order to set scene
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}

///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////
void drawString(const char *str, int x, int y, float color[4], void *font)
{
  glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
  glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
  glDisable(GL_TEXTURE_2D);

  glColor4fv(color);          // set text color
  glRasterPos2i(x, y);        // place text position

  // loop all characters in the string
  while(*str)
  {
    glutBitmapCharacter(font, *str);
    ++str;
  }

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glPopAttrib();
}



///////////////////////////////////////////////////////////////////////////////
// draw a string in 3D space
///////////////////////////////////////////////////////////////////////////////
void drawString3D(const char *str, float pos[3], float color[4], void *font)
{
  glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
  glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
  glDisable(GL_TEXTURE_2D);

  glColor4fv(color);          // set text color
  glRasterPos3fv(pos);        // place text position

  // loop all characters in the string
  while(*str)
  {
    glutBitmapCharacter(font, *str);
    ++str;
  }

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glPopAttrib();
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
  
  // Save current matrix state
  glPushMatrix();
  glTranslatef(0, 0, -cameraDistance);
  glRotatef(cameraAngleX, 1, 0, 0);   // pitch
  glRotatef(cameraAngleY, 0, 1, 0);   // heading

  glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex3f(X1, Y1, Z1);
    glVertex3f(X2, Y2, Z2);
    //glVertex3f(eyePoint.x, eyePoint.y, eyePoint.z);
  glEnd();


#if SHOW_GRID
  glBegin(GL_LINES);
  glColor3f(0, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(10, 0, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 10, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 10);
  glEnd();

  glBegin(GL_LINES);
  glColor3f(.1, .1, .1);
  for (int i = -100; i < 100; i+=2)
  {
    glVertex3f(100, 0, i);
    glVertex3f(-100, 0, i);

    glVertex3f(i, 0, 100);
    glVertex3f(i, 0, -100);
  }
  glEnd();
#endif

  glDisable(GL_COLOR_MATERIAL);

  mBoard->drawModel();
  red[1]->drawModel();
  dice->drawModel();

  glEnable(GL_COLOR_MATERIAL);

  glEnable(GL_BLEND);
  glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glDisable(GL_BLEND);
  

  float pos[3] = {0.0f, 5.0f, 0};
  float color[4] = {1,1,1,1};
  drawString3D("Chess board", pos, color, font);

#if SHOW_LIGHT_SOURCE
  lightPosition[0] = 15*cos(lightAngle);
  lightPosition[1] = lightHeight;
  lightPosition[2] = 15*sin(lightAngle);

  Light::inst().setPosition(lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
  Light::inst().drawLightSource(lightAngle, lightHeight);
#endif // SHOW_LIGHT_SOURCE

  glPopMatrix();
  
  red[1]->setPosition(glp3f(4, 0, 4));
  //dice->setPosition(glp3f(-4, 4, 4));
  //red[0].setAngle(180);

  glutSwapBuffers();
}

void reshapeCB(int width, int height) {
  screenWidth = width;
  screenHeight = height;
  toPerspective();
  setCamera(eyePoint.x, eyePoint.y, eyePoint.z, lookAtPoint.x, lookAtPoint.y, lookAtPoint.z);
}

/*
 * Callback function for mouse event
 */
void mouseCB(int button, int state, int x, int y) {

  mouseX = x;
  mouseY = y;

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

  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];
  GLfloat winX, winY, winZ;
  GLdouble _x, _y, _z;


  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  glGetIntegerv(GL_VIEWPORT, viewport);

  winX = (GLfloat)mouseX;
  winY = (GLfloat)viewport[3] - (GLfloat)mouseY;
  glReadPixels(mouseX, GLint(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

  //gluUnProject(winX, winY, winZ, modelview, projection, viewport, &_x, &_y, &_z);
  gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &X1, &Y1, &Z1);
  gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &X2, &Y2, &Z2);

  //Find X and Z when Y is 0
  float zeropoint, zeroperc;
  double posXt, posYt, posZt;
  posXt = X1 - X2;
  posYt = Y1 - Y2;
  posZt = Z1 - Z2;

  //Check the Y's pass through the plane on 0
//   if (Y1 < 0.0 && Y2 < 0.0 &#0124; &#0124; Y1 > 0.0 && Y2 > 0.0)
//     return;

  //Now we'll nudge out stuff up and find out the zero point
  zeropoint = 0.0f - (float)Y1;

  //Find the percentage that this point is between them
  zeroperc = (zeropoint / (float)posYt);

  float posX = (float)X1 + (float)(posXt * zeroperc);	
  float posY = (float)Y1 + (float)(posYt * zeroperc);	
  float posZ = (float)Z1 + (float)(posZt * zeroperc);

  cout << posX << ' ' << posY << ' ' << posZ << ' ' << endl;
  //cout << X1 << ' ' << Y1 << ' ' << Z1 << ' ' << endl;
  //cout << X2 << ' ' << Y2 << ' ' << Z2 << ' ' << endl << endl;
  //cout << winX << ' ' << winY << ' ' << winZ << endl << endl;
}

/*
 * Callback function for animation motion event
 */
void mouseMotionCB(int x, int y) {

  if(mouseRightDown)
  {
    cameraAngleY += (x - mouseX);
    cameraAngleX += (y - mouseY);
    mouseX = x;
    mouseY = y;

    //if (cameraAngleX < -eyePoint.y)
    //{
    //  cameraAngleX = -eyePoint.y;
    //}

    //if (cameraAngleX > 60)
    //{
    //  cameraAngleX = 60;
    //}
  }
  if(mouseMiddleDown)
  {
    cameraDistance -= (y - mouseY) * 0.2f;
    mouseY = y;
  }
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
    cameraAngleX = cameraAngleY = 0;
    break;
  default:
    break;
  }
}

void timerCB(int value) {
  lightAngle+=0.3;
  
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
  initModel( );

  //glutTimerFunc(DELTA_TIME, timerCB, 0);

  // Now that we have set everything up, loop responding to events.
  glutMainLoop( );
}



/* ----------------------------------------------------------------------- */

