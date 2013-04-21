#ifndef _CG_CAMERA_H_INCLUDED
#define _CG_CAMERA_H_INCLUDED

#include <cmath>
#include "mathlib.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Camera {

public:
    Vector3 eye;
    Vector3 at;
    Vector3 up;
    float theta;
    float phi;
    float R;
    bool is_panning;
    bool is_rotating;
    float x_old;
    float y_old;
    float theta_old;
    float phi_old;

    Camera();
    ~Camera();

    static Camera& inst();

    void update(float x, float y);
    void save(float x, float y);
    void zoom(float x);
    void pan(float x, float y);
    void rotate(float x, float y);

private:
    Vector3 transf_coord();
};

#endif // CAMERA_H_INCLUDED
