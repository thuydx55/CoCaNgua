//-----------------------------------------------------------------------------
// Copyright (c) 2005-2007 dhpoware. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#if !defined(COLLISION_H)
#define COLLISION_H

#include "mathlib.h"

//-----------------------------------------------------------------------------
// Classes.

class BoundingBox
{
public:
    Vector3 min;
    Vector3 max;

    BoundingBox();
    BoundingBox(const Vector3 &min_, const Vector3 &max_);
    ~BoundingBox();

    Vector3 getCenter() const;
    float getRadius() const;
    float getSize() const;
};

//-----------------------------------------------------------------------------

class BoundingSphere
{
public:
    Vector3 center;
    float radius;

    BoundingSphere();
    BoundingSphere(const Vector3 &center_, float radius_);
    ~BoundingSphere();

    bool hasCollided(const BoundingSphere &other) const;
};

//-----------------------------------------------------------------------------

class BoundingVolume
{
public:
    BoundingBox box;
    BoundingSphere sphere;

    BoundingVolume();
    ~BoundingVolume();
};

//-----------------------------------------------------------------------------

class Plane
{
public:
    Vector3 n;
    float d;

    static float dot(const Plane &p, const Vector3 &pt);

    Plane();
    Plane(float a_, float b_, float c_, float d_);
    Plane(const Vector3 &pt, const Vector3 &normal);
    Plane(const Vector3 &pt1, const Vector3 &pt2, const Vector3 &pt3);
    ~Plane();

    bool operator==(const Plane &rhs) const;
    bool operator!=(const Plane &rhs) const;

    void fromPointNormal(const Vector3 &pt, const Vector3 &normal);
    void fromPoints(const Vector3 &pt1, const Vector3 &pt2, const Vector3 &pt3);
    const Vector3 &normal() const;
    Vector3 &normal();
    void normalize();
    void set(float a_, float b_, float c_, float d_);
};

//-----------------------------------------------------------------------------

class Frustum
{
public:
    enum
    {
        FRUSTUM_PLANE_LEFT   = 0,
        FRUSTUM_PLANE_RIGHT  = 1,
        FRUSTUM_PLANE_BOTTOM = 2,
        FRUSTUM_PLANE_TOP    = 3,
        FRUSTUM_PLANE_NEAR   = 4,
        FRUSTUM_PLANE_FAR    = 5
    };

    Plane planes[6];

    void extractPlanes(const Matrix4 &viewMatrix4, const Matrix4 &projMatrix4);

    bool boxInFrustum(const BoundingBox &box) const;
    bool pointInFrustum(const Vector3 &point) const;
    bool sphereInFrustum(const BoundingSphere &sphere) const;
    bool volumeInFrustum(const BoundingVolume &volume) const;
};

//-----------------------------------------------------------------------------

class Ray
{
public:
    Vector3 origin;
    Vector3 direction;

    Ray();
    Ray(const Vector3 &origin_, const Vector3 &direction_);
    ~Ray();

    bool hasIntersected(const BoundingSphere &sphere) const;
    bool hasIntersected(const BoundingBox &box) const;
    bool hasIntersected(const BoundingVolume &volume) const;
    bool hasIntersected(const Plane &plane) const;
    bool hasIntersected(const Plane &plane, float &t, Vector3 &intersection) const;
};

//-----------------------------------------------------------------------------

#endif