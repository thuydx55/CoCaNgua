#include "Camera.h"

const float Camera::Radius = 50;
const Vector3 Camera::origin = Vector3();

Camera::Camera(){
  at = Vector3(0.0,0.0,0.0);
	up = Vector3(0.0,1.0,0.0);
	theta = Math::PI/3;
	phi = Math::PI/3;
	R = 50.0;
  eye = transf_coord();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
    //gluLookAt(eye.x,eye.y,eye.z,at.x,at.y,at.z,up.x,up.y,up.z);

  zeroViewVector = Vector2(0, 1);
};


Camera& Camera::inst()
{
  static Camera Instance;
  return Instance;
}


Camera::~Camera(){};

void Camera::update(float x, float y){
  float new_phi = phi_old - (y-y_old)/50.0;	
  if (new_phi > (Math::PI/2.3))								
    new_phi = Math::PI/2.3 + 0.001;
  else if (new_phi < 0)
    new_phi = 0.001;

  float new_theta = theta_old - (x-x_old)/50.0; 
  if (new_theta > Math::PI)
    new_theta -= Math::TWO_PI;
  else if (new_theta < -Math::PI)
    new_theta += Math::TWO_PI;

  theta = new_theta;
  phi = new_phi;
  //printf("phi: %f  theta: %f  R: %f\n",phi,theta,R);
};

void Camera::save(float x, float y){
  x_old = x;
  y_old = y;
  theta_old = theta;
  phi_old = phi;
}

Vector3 Camera::transf_coord(){
  Vector3 result;
  result.z = at.z + (GLdouble)R*sinf(phi)*cosf(theta);
  result.x = at.x + (GLdouble)R*sinf(phi)*sinf(theta);
  result.y = at.y + (GLdouble)R*cosf(phi);
  return result;
}

void Camera::zoom(float x){
  R += x;
  if (R < 3.0)
      R = 3.0;
  if (R > 75.0)
      R = 75.0;
  eye = transf_coord();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye.x,eye.y,eye.z,at.x,at.y,at.z,up.x,up.y,up.z);
  //printf("at: %f, %f, %f\n", at.x, at.y, at.z);
}

void Camera::pan(float x, float z){
//    at.x = (x_pan - x_old)/50.0;
//    at.z = (z_pan - y_old)/50.0;
//    glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//    gluLookAt(eye.x,eye.y,eye.z,at.x,at.y,at.z,up.x,up.y,up.z);
    //printf("PAN NAO IMPLEMENTADO");
}

void Camera::rotate(float x, float y){
  update(x,y);
  eye = transf_coord();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye.x,eye.y,eye.z,at.x,at.y,at.z,up.x,up.y,up.z);
}

void Camera::rotateTheta( float pTheta )
{
  theta = pTheta;
  if (theta > Math::PI)
    theta -= Math::TWO_PI;
  else if (theta < -Math::PI)
    theta += Math::TWO_PI;

  eye = transf_coord();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye.x,eye.y,eye.z,at.x,at.y,at.z,up.x,up.y,up.z);
}
