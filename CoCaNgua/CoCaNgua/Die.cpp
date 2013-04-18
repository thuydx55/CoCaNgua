#include "Die.h"

int counter = 0;

double round(double r) {
  return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

Die::Die(void)
{
  mIsRolling = false;
  phi = theta = 0;
  mState = DIE_WAITING;

  float _position[4] = {0, 0, 5, 1};
  float _ambient[4] = {0.2, 0.2, 0.2, 1.0};
  float _diffuse[4] = {0.7, 0.7, 0.7, 1.0};
  float _specular[4] = {1.0, 1.0, 1.0, 1.0};

  glLightfv(GL_LIGHT1, GL_POSITION, _position);
  glLightfv(GL_LIGHT1, GL_AMBIENT,  _ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  _diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, _specular);
}

void Die::drawModel()
{
  Model::drawModel();

  glDisable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  float x, y, z;
  getCenter(x, y, z);

  glPushMatrix();
  {
    // Move Object to coordinate origin
    glTranslatef(-x, -y, -z);
    glPushMatrix();
    {
      glTranslated(mPos.x - mAnchor.x*getWidth(), 
        mPos.y - mAnchor.y*getHeight(),
        mPos.z - mAnchor.z*getLength());

      float m[16];

      glPushMatrix();
      {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(theta, 0, 1, 0);
        glGetFloatv(GL_MODELVIEW_MATRIX , m);
      }
      glPopMatrix();

      Matrix4 matrix(m);
      Vector3 beforeTransformed(0, 0, 1);
      Vector3 afterTransformed = beforeTransformed*matrix;

      Vector3 crossVector = Vector3::cross(Vector3(0, 1, 0), afterTransformed);

//       cout << afterTransformed.toString();
//       cout << crossVector.toString();

      glRotatef(theta, 0, 1, 0);
      glRotatef(phi, crossVector.x, crossVector.y, crossVector.z);

      draw();
      glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 10);
      glEnd();
    }
    glPopMatrix();
  }
  glPopMatrix();

  glDisable(GL_LIGHT1);
  glEnable(GL_LIGHT0);
}

void Die::update()
{
  double tEnlapse = mTimer.elapsed();

  if (mState == DIE_WAITING)
  {
    phi = DIE_WAITING_RANGE*cosf(Math::degreesToRadians(counter));
    theta = DIE_WAITING_RANGE*sinf(Math::degreesToRadians(counter));

    counter += DIE_WAITING_SPEED;
    if (counter >= 360) counter -= 360;
  }
  else if (mState == DIE_ROLLING)
  {
    phi = phiOld+(phiTarget-phiOld)/(tEnlapse/DIE_TIME_ROLLING);
    theta = thetaOld+(thetaTarget-thetaOld)/(tEnlapse/DIE_TIME_ROLLING);

    if (tEnlapse > DIE_TIME_ROLLING)
    {
      mState = DIE_STOP;
      phi = phiTarget;
      theta = thetaTarget;
    }
  }
}

int Die::rollDie()
{
  mState = DIE_ROLLING;

  srand(time(0));
  float randPhi = rand()%(2*DIE_ROLL_NUMBER*180) - DIE_ROLL_NUMBER*180;
  float randTheta = rand()%(2*DIE_ROLL_NUMBER*180) - DIE_ROLL_NUMBER*180;

  int roundPhi = round(randPhi/90);
  int roundTheta = round(randTheta/90);

  phiTarget = roundPhi*90;
  thetaTarget = roundTheta*90;

  phiOld = phi;
  thetaOld = theta;

  int face = 6;
  roundPhi %= 4;
  roundTheta %= 4;

  roundPhi = roundPhi < 0 ? roundPhi + 4 : roundPhi;
  roundTheta = roundTheta < 0 ? roundTheta + 4 : roundTheta;

  switch (roundTheta)
  {
  case 0:
    face = 6;
    break;
  case 1:
    face = 2;
    break;
  case 2:
    face = 1;
    break;
  case 3:
    face = 5;
    break;
  }

  switch (roundPhi)
  {
  case 0:
    break;
  case 1:
    face = roundTheta%2 ? 3 : 4;
    break;
  case 2:
    face = 7-face;
    break;
  case 3:
    face = roundTheta%2 ? 4 : 3;
    break;
  }
  mTimer.start();

  cout << "FACE: " << face << endl;
  cout << "Random Phi " << randPhi << " Random Theta: " << randTheta << endl;
  cout << "Round Phi " << roundPhi << " Round Theta: " << roundTheta << endl;
  cout << "Target Phi " << phiTarget << " Target Theta: " << thetaTarget << endl;
  cout << endl;

  return face;
}

//int Die::rollDie()
//{
//  mState = DIE_ROLLING;
//
//  srand(time(0));
//  int face = rand()%6 + 1;
//
//  return face;
//
//  switch (face)
//  {
//
//  default:
//    break;
//  }
//}

Die::~Die(void)
{
}
