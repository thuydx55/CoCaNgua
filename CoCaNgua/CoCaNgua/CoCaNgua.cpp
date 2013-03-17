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

#include "model_obj.h"
//#include "gl2.h"

using namespace std;

/* -- DATA STRUCTURES ---------------------------------------------------- */
// Our point class.
class GLintPoint  {

};

typedef std::map<std::string, GLuint> ModelTextures;

/* -- GLOBAL VARIABLES --------------------------------------------------- */
ModelOBJ            g_model;
ModelTextures       g_modelTextures;
bool                g_enableTextures = false;

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

void DrawModelUsingFixedFuncPipeline()
{
  const ModelOBJ::Mesh *pMesh = 0;
  const ModelOBJ::Material *pMaterial = 0;
  const ModelOBJ::Vertex *pVertices = 0;
  ModelTextures::const_iterator iter;

  for (int i = 0; i < g_model.getNumberOfMeshes(); ++i)
  {
    pMesh = &g_model.getMesh(i);
    pMaterial = pMesh->pMaterial;
    pVertices = g_model.getVertexBuffer();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pMaterial->ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pMaterial->diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->shininess * 128.0f);

    if (g_enableTextures)
    {
      iter = g_modelTextures.find(pMaterial->colorMapFilename);

      if (iter == g_modelTextures.end())
      {
        glDisable(GL_TEXTURE_2D);
      }
      else
      {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, iter->second);
      }
    }
    else
    {
      glDisable(GL_TEXTURE_2D);
    }

    if (g_model.hasPositions())
    {
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_FLOAT, g_model.getVertexSize(),
        g_model.getVertexBuffer()->position);
    }

    if (g_model.hasTextureCoords())
    {
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, g_model.getVertexSize(),
        g_model.getVertexBuffer()->texCoord);
    }

    if (g_model.hasNormals())
    {
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_FLOAT, g_model.getVertexSize(),
        g_model.getVertexBuffer()->normal);
    }

    glDrawElements(GL_TRIANGLES, pMesh->triangleCount * 3, GL_UNSIGNED_INT,
      g_model.getIndexBuffer() + pMesh->startIndex);

    if (g_model.hasNormals())
      glDisableClientState(GL_NORMAL_ARRAY);

    if (g_model.hasTextureCoords())
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    if (g_model.hasPositions())
      glDisableClientState(GL_VERTEX_ARRAY);
  }
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
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glColor3f( 0.0, 0.0, 0.0 );
  glPointSize( 1.0 );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluOrtho2D( 0.0, 640.0, 0.0, 480.0 );

  g_model.import("Models/a.obj");
  //g_model.normalize();

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

  DrawModelUsingFixedFuncPipeline();

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
  gluLookAt(5, 5, 20,
            0, 1, 0, 
            0, 1, 0);


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

