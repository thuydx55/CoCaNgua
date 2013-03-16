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

using namespace std;

/* -- DATA STRUCTURES ---------------------------------------------------- */
// Our point class.
class GLintPoint  {

};

/* -- GLOBAL VARIABLES --------------------------------------------------- */


// Saved camera position
int oldX, oldY;

// Initialize camera's spin position
float spinX = 0, spinY = 0;

// Initialize camera's zoom position
float zoom = 0;

/* -- LOCAL VARIABLES ---------------------------------------------------- */


/* ----------------------------------------------------------------------- */
/* Function    : void drawDot( GLint x, GLint y )
 *
 * Description : Draw a point at location (x, y) in the window.
 *
 * Parameters  : GLint x : X coordinate of point to draw.
 *               GLint y : X coordinate of point to draw.
 *
 * Returns     : void
 */

void drawDot( GLint x, GLint y )  {

}

/* ----------------------------------------------------------------------- */
/* Function    : void myInit( void )
 *
 * Description : Initialize OpenGL and the window where things will be
 *               drawn.
 *
 * Parameters  : void
 *
 * Returns     : void
 */

void myInit( void )  {
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glColor3f( 0.0, 0.0, 0.0 );
  glPointSize( 1.0 );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluOrtho2D( 0.0, 640.0, 0.0, 480.0 );
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

void myDisplay( void )  {
  int i;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Save current matrix state
  glPushMatrix();
  glRotatef(spinY, 1, 0, 0);
  glRotatef(spinX, 0, 1, 0);
  glTranslatef(0, 0, -zoom);

  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(10, 0, 0);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 10, 0);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 10);
  glEnd();

  // Draw ground plane
  glBegin(GL_QUADS);
    //glColor3ub(0, 128, 255);
    glVertex3f(-2, 0, -2);
    glVertex3f(-2, 0, 2);
    glVertex3f(2, 0, 2);
    glVertex3f(2, 0, -2);
  glEnd();

  glPopMatrix();
  glutSwapBuffers();

  glFlush();
}

void reshapeFunc(int width, int height) {
  float black[] = {0, 0, 0, 0};

  // Set viewport
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (float)width/height, 1, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 1, 3, 0, 1, 0, 0, 1, 0);


  //// Set display stuffs
  //glPointSize(pointSize);
  //glEnable(GL_POINT_SMOOTH);
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glEnable(GL_COLOR_MATERIAL);
  //glEnable(GL_DEPTH_TEST);
  //glEnable(GL_LIGHT0);

}

/*
 * Callback function for mouse event
 */
void mouseFunc(int button, int state, int x, int y) {
	oldX = x;
	oldY = y;
	glutPostRedisplay();
}

/*
 * Callback function for animation motion event
 */
void motionFunc(int x, int y) {
	spinX = x - oldX;
	spinY = y - oldY;
	glutPostRedisplay();
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
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 600);
  glutInit(&argc, argv);
  // Create the window.
  glutCreateWindow( "Assignment - 08. Co Ca Ngua" );
  // Set the callback funcion to call when we need to draw something.
  glutDisplayFunc( myDisplay );
  glutReshapeFunc(reshapeFunc);
  glutMotionFunc(motionFunc);
  glutMouseFunc(mouseFunc);
  // Initialize some things.
  myInit( );

  // Now that we have set everything up, loop responding to events.
  glutMainLoop( );
}

/* ----------------------------------------------------------------------- */

