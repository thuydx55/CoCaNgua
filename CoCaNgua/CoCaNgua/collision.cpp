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

#include "collision.h"

//-----------------------------------------------------------------------------
// BoundingBox.

BoundingBox::BoundingBox()
{
    min.set(0.0f, 0.0f, 0.0f);
    max.set(0.0f, 0.0f, 0.0f);
}

BoundingBox::BoundingBox(const Vector3 &min_, const Vector3 &max_)
{
    min = min_;
    max = max_;
}

BoundingBox::~BoundingBox()
{
}

Vector3 BoundingBox::getCenter() const
{
    return (min + max) * 0.5f;
}

float BoundingBox::getRadius() const
{
    return getSize() * 0.5f;
}

float BoundingBox::getSize() const
{
    return (max - min).magnitude();
}

//-----------------------------------------------------------------------------
// BoundingSphere.

BoundingSphere::BoundingSphere()
{
    center.set(0.0f, 0.0f, 0.0f);
    radius = 0.0f;
}

BoundingSphere::BoundingSphere(const Vector3 &center_, float radius_)
{
    center = center_;
    radius = radius_;
}

BoundingSphere::~BoundingSphere()
{
}

bool BoundingSphere::hasCollided(const BoundingSphere &other) const
{
    Vector3 disp(other.center - center);
    float lengthSq = (disp.x * disp.x) + (disp.y * disp.y) + (disp.z * disp.z);
    float radiiSq = (other.radius + radius) * (other.radius + radius);

    return (lengthSq < radiiSq) ? true : false;
}

//-----------------------------------------------------------------------------
// BoundingVolume.

BoundingVolume::BoundingVolume()
{
}

BoundingVolume::~BoundingVolume()
{
}

//-----------------------------------------------------------------------------
// Plane.
//
// The plane equation is: ax + by + cz + d = 0.
// The plane's normal (a, b, c) in stored in a Vector3 so that functionality
// from the Vector3 class can be used.

Plane::Plane()
{
}

Plane::Plane(float a_, float b_, float c_, float d_) : n(a_, b_, c_), d(d_)
{
}

Plane::Plane(const Vector3 &pt, const Vector3 &normal)
{
    fromPointNormal(pt, normal);
}

Plane::Plane(const Vector3 &pt1, const Vector3 &pt2, const Vector3 &pt3)
{
    fromPoints(pt1, pt2, pt3);
}

Plane::~Plane()
{
}

float Plane::dot(const Plane &p, const Vector3 &pt)
{
    // Returns:
    //  > 0 if the point 'pt' lies in front of the plane 'p'
    //  < 0 if the point 'pt' lies behind the plane 'p'
    //    0 if the point 'pt' lies on the plane 'p'
    //
    // The signed distance from the point 'pt' to the plane 'p' is returned.

    return Vector3::dot(p.n, pt) + p.d;
}

bool Plane::operator==(const Plane &rhs) const
{
    return (n == rhs.n) && Math::closeEnough(d, rhs.d);
}

bool Plane::operator!=(const Plane &rhs) const
{
    return !(*this == rhs);
}

void Plane::fromPointNormal(const Vector3 &pt, const Vector3 &normal)
{
    set(normal.x, normal.y, normal.z, -Vector3::dot(normal, pt));
    normalize();
}

void Plane::fromPoints(const Vector3 &pt1, const Vector3 &pt2, const Vector3 &pt3)
{
    n = Vector3::cross(pt2 - pt1, pt3 - pt1);
    d = -Vector3::dot(n, pt1);
    normalize();
}

const Vector3 &Plane::normal() const
{
    return n;
}

Vector3 &Plane::normal()
{
    return n;
}

void Plane::normalize()
{
    float length = 1.0f / n.magnitude();
    n *= length;
    d *= length;
}

void Plane::set(float a_, float b_, float c_, float d_)
{
    n.set(a_, b_, c_);
    d = d_;
}

//-----------------------------------------------------------------------------
// Frustum.

void Frustum::extractPlanes(const Matrix4 &viewMatrix, const Matrix4 &projMatrix)
{
    // Extracts the view frustum clipping planes from the combined
    // view-projection matrix in world space. The extracted planes will
    // have their normals pointing towards the inside of the view frustum.
    //
    // References:
    //  Gil Gribb, Klaus Hartmann, "Fast Extraction of Viewing Frustum
    //  Planes from the World-View-Projection Matrix,"
    //  http://www2.ravensoft.com/users/ggribb/plane%20extraction.pdf

    Matrix4 m(viewMatrix * projMatrix);
    Plane *pPlane = 0;

    // Left clipping plane.
    pPlane = &planes[FRUSTUM_PLANE_LEFT];
    pPlane->set(
        m[0][3] + m[0][0],
        m[1][3] + m[1][0],
        m[2][3] + m[2][0],
        m[3][3] + m[3][0]);
    pPlane->normalize();

    // Right clipping plane.
    pPlane = &planes[FRUSTUM_PLANE_RIGHT];
    pPlane->set(
        m[0][3] - m[0][0],
        m[1][3] - m[1][0],
        m[2][3] - m[2][0],
        m[3][3] - m[3][0]);
    pPlane->normalize();

    // Top clipping plane.
    pPlane = &planes[FRUSTUM_PLANE_TOP];
    pPlane->set(
        m[0][3] - m[0][1],
        m[1][3] - m[1][1],
        m[2][3] - m[2][1],
        m[3][3] - m[3][1]);
    pPlane->normalize();

    // Bottom clipping plane.
    pPlane = &planes[FRUSTUM_PLANE_BOTTOM];
    pPlane->set(
        m[0][3] + m[0][1],
        m[1][3] + m[1][1],
        m[2][3] + m[2][1],
        m[3][3] + m[3][1]);
    pPlane->normalize();

    // Near clipping plane.
    pPlane = &planes[FRUSTUM_PLANE_NEAR];
    pPlane->set(m[0][2], m[1][2], m[2][2], m[3][2]);
    pPlane->normalize();

    // Far clipping plane.
    pPlane = &planes[FRUSTUM_PLANE_FAR];
    pPlane->set(
        m[0][3] - m[0][2],
        m[1][3] - m[1][2],
        m[2][3] - m[2][2],
        m[3][3] - m[3][2]);
    pPlane->normalize();
}

bool Frustum::boxInFrustum(const BoundingBox &box) const
{
    Vector3 c((box.min + box.max) * 0.5f);
    float sizex = box.max.x - box.min.x;
    float sizey = box.max.y - box.min.y;
    float sizez = box.max.z - box.min.z;

    Vector3 corners[8] =
    {
        Vector3((c.x - sizex * 0.5f), (c.y - sizey * 0.5f), (c.z - sizez * 0.5f)),
        Vector3((c.x + sizex * 0.5f), (c.y - sizey * 0.5f), (c.z - sizez * 0.5f)),
        Vector3((c.x - sizex * 0.5f), (c.y + sizey * 0.5f), (c.z - sizez * 0.5f)),
        Vector3((c.x + sizex * 0.5f), (c.y + sizey * 0.5f), (c.z - sizez * 0.5f)),
        Vector3((c.x - sizex * 0.5f), (c.y - sizey * 0.5f), (c.z + sizez * 0.5f)),
        Vector3((c.x + sizex * 0.5f), (c.y - sizey * 0.5f), (c.z + sizez * 0.5f)),
        Vector3((c.x - sizex * 0.5f), (c.y + sizey * 0.5f), (c.z + sizez * 0.5f)),
        Vector3((c.x + sizex * 0.5f), (c.y + sizey * 0.5f), (c.z + sizez * 0.5f))
    };

    for (int i = 0; i < 6; ++i)
    {
        if (Plane::dot(planes[i], corners[0]) > 0.0f)
            continue;

        if (Plane::dot(planes[i], corners[1]) > 0.0f)
            continue;

        if (Plane::dot(planes[i], corners[2]) > 0.0f)
            continue;

        if (Plane::dot(planes[i], corners[3]) > 0.0f)
            continue;

        if (Plane::dot(planes[i], corners[4]) > 0.0f)
            continue;

        if (Plane::dot(planes[i], corners[5]) > 0.0f)
            continue;

        if (Plane::dot(planes[i], corners[6]) > 0.0f)
            continue;

        if (Plane::dot(planes[i], corners[7]) > 0.0f)
            continue;

        return false;
    }

    return true;
}

bool Frustum::pointInFrustum(const Vector3 &point) const
{
    for (int i = 0; i < 6; ++i)
    {
        if (Plane::dot(planes[i], point) <= 0.0f)
            return false;
    }

    return true;
}

bool Frustum::sphereInFrustum(const BoundingSphere &sphere) const
{
    for (int i = 0; i < 6; ++i)
    {
        if (Plane::dot(planes[i], sphere.center) <= -sphere.radius)
            return false;
    }

    return true;
}

bool Frustum::volumeInFrustum(const BoundingVolume &volume) const
{
    if (sphereInFrustum(volume.sphere))
    {
        if (boxInFrustum(volume.box))
            return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
// Ray.

Ray::Ray()
{
}

Ray::Ray(const Vector3 &origin_, const Vector3 &direction_)
{
    origin = origin_;
    direction = direction_;
}

Ray::~Ray()
{
}

bool Ray::hasIntersected(const BoundingSphere &sphere) const
{
    Vector3 w(sphere.center - origin);
    float wsq = Vector3::dot(w, w);
    float proj = Vector3::dot(w, direction);
    float rsq = sphere.radius * sphere.radius;

    // Early out: if sphere is behind the ray then there's no intersection.
    if (proj < 0.0f && wsq > rsq)
        return false;

    float vsq = Vector3::dot(direction, direction);

    // Test length of difference vs. radius.
    return vsq * wsq - proj * proj <= vsq * rsq;
}

bool Ray::hasIntersected(const BoundingBox &box) const
{
    // References:
    //  Jeffrey Mahovsky and Brian Wyvill, "Fast Ray-Axis Aligned Bounding Box
    //  Overlap Tests with Plücker Coordinates", Journal of Graphics Tools,
    //  9(1):35-46.

    if (direction.x < 0.0f)
	{
		if (direction.y < 0.0f)
		{
			if (direction.z < 0.0f)
			{
				// case MMM: side(R,HD) < 0 or side(R,FB) > 0 or side(R,EF) > 0 or side(R,DC) < 0 or side(R,CB) < 0 or side(R,HE) > 0 to miss

				if ((origin.x < box.min.x) || (origin.y < box.min.y) || (origin.z < box.min.z))
					return false;

				float xa = box.min.x - origin.x;
				float ya = box.min.y - origin.y;
				float za = box.min.z - origin.z;
				float xb = box.max.x - origin.x;
				float yb = box.max.y - origin.y;
				float zb = box.max.z - origin.z;

				if ((direction.x * ya - direction.y * xb < 0)
				        || (direction.x * yb - direction.y * xa > 0)
				        || (direction.x * zb - direction.z * xa > 0)
				        || (direction.x * za - direction.z * xb < 0)
				        || (direction.y * za - direction.z * yb < 0)
				        || (direction.y * zb - direction.z * ya > 0))
					return false;

				return true;
			}
			else
			{
				// case MMP: side(R,HD) < 0 or side(R,FB) > 0 or side(R,HG) > 0 or side(R,AB) < 0 or side(R,DA) < 0 or side(R,GF) > 0 to miss

				if ((origin.x < box.min.x) || (origin.y < box.min.y) || (origin.z > box.max.z))
					return false;

				float xa = box.min.x - origin.x;
				float ya = box.min.y - origin.y;
				float za = box.min.z - origin.z;
				float xb = box.max.x - origin.x;
				float yb = box.max.y - origin.y;
				float zb = box.max.z - origin.z;

				if ((direction.x * ya - direction.y * xb < 0.0f)
				        || (direction.x * yb - direction.y * xa > 0.0f)
				        || (direction.x * zb - direction.z * xb > 0.0f)
				        || (direction.x * za - direction.z * xa < 0.0f)
				        || (direction.y * za - direction.z * ya < 0.0f)
				        || (direction.y * zb - direction.z * yb > 0.0f))
					return false;

				return true;
			}
		}
		else
		{
			if (direction.z < 0.0f)
			{
				// case MPM: side(R,EA) < 0 or side(R,GC) > 0 or side(R,EF) > 0 or side(R,DC) < 0 or side(R,GF) < 0 or side(R,DA) > 0 to miss

				if ((origin.x < box.min.x) || (origin.y > box.max.y) || (origin.z < box.min.z))
					return false;

				float xa = box.min.x - origin.x;
				float ya = box.min.y - origin.y;
				float za = box.min.z - origin.z;
				float xb = box.max.x - origin.x;
				float yb = box.max.y - origin.y;
				float zb = box.max.z - origin.z;

				if ((direction.x * ya - direction.y * xa < 0.0f)
				        || (direction.x * yb - direction.y * xb > 0.0f)
				        || (direction.x * zb - direction.z * xa > 0.0f)
				        || (direction.x * za - direction.z * xb < 0.0f)
				        || (direction.y * zb - direction.z * yb < 0.0f)
				        || (direction.y * za - direction.z * ya > 0.0f))
					return false;

				return true;
			}
			else
			{
				// case MPP: side(R,EA) < 0 or side(R,GC) > 0 or side(R,HG) > 0 or side(R,AB) < 0 or side(R,HE) < 0 or side(R,CB) > 0 to miss

				if ((origin.x < box.min.x) || (origin.y > box.max.y) || (origin.z > box.max.z))
					return false;

				float xa = box.min.x - origin.x;
				float ya = box.min.y - origin.y;
				float za = box.min.z - origin.z;
				float xb = box.max.x - origin.x;
				float yb = box.max.y - origin.y;
				float zb = box.max.z - origin.z;

				if ((direction.x * ya - direction.y * xa < 0.0f)
				        || (direction.x * yb - direction.y * xb > 0.0f)
				        || (direction.x * zb - direction.z * xb > 0.0f)
				        || (direction.x * za - direction.z * xa < 0.0f)
				        || (direction.y * zb - direction.z * ya < 0.0f)
				        || (direction.y * za - direction.z * yb > 0.0f))
					return false;

				return true;
			}
		}
	}
	else
	{
		if (direction.y < 0.0f)
		{
			if (direction.z < 0.0f)
			{
				// case PMM: side(R,GC) < 0 or side(R,EA) > 0 or side(R,AB) > 0 or side(R,HG) < 0 or side(R,CB) < 0 or side(R,HE) > 0 to miss

				if ((origin.x > box.max.x) || (origin.y < box.min.y) || (origin.z < box.min.z))
					return false;

				float xa = box.min.x - origin.x;
				float ya = box.min.y - origin.y;
				float za = box.min.z - origin.z;
				float xb = box.max.x - origin.x;
				float yb = box.max.y - origin.y;
				float zb = box.max.z - origin.z;

				if ((direction.x * yb - direction.y * xb < 0.0f)
				        || (direction.x * ya - direction.y * xa > 0.0f)
				        || (direction.x * za - direction.z * xa > 0.0f)
				        || (direction.x * zb - direction.z * xb < 0.0f)
				        || (direction.y * za - direction.z * yb < 0.0f)
				        || (direction.y * zb - direction.z * ya > 0.0f))
					return false;

				return true;
			}
			else
			{
				// case PMP: side(R,GC) < 0 or side(R,EA) > 0 or side(R,DC) > 0 or side(R,EF) < 0 or side(R,DA) < 0 or side(R,GF) > 0 to miss

				if ((origin.x > box.max.x) || (origin.y < box.min.y) || (origin.z > box.max.z))
					return false;

				float xa = box.min.x - origin.x;
				float ya = box.min.y - origin.y;
				float za = box.min.z - origin.z;
				float xb = box.max.x - origin.x;
				float yb = box.max.y - origin.y;
				float zb = box.max.z - origin.z;

				if ((direction.x * yb - direction.y * xb < 0.0f)
				        || (direction.x * ya - direction.y * xa > 0.0f)
				        || (direction.x * za - direction.z * xb > 0.0f)
				        || (direction.x * zb - direction.z * xa < 0.0f)
				        || (direction.y * za - direction.z * ya < 0.0f)
				        || (direction.y * zb - direction.z * yb > 0.0f))
					return false;

                return true;
			}
		}
		else
		{
			if (direction.z < 0.0f)
			{
				// case PPM: side(R,FB) < 0 or side(R,HD) > 0 or side(R,AB) > 0 or side(R,HG) < 0 or side(R,GF) < 0 or side(R,DA) > 0 to miss

				if ((origin.x > box.max.x) || (origin.y > box.max.y) || (origin.z < box.min.z))
					return false;

				float xa = box.min.x - origin.x;
				float ya = box.min.y - origin.y;
				float za = box.min.z - origin.z;
				float xb = box.max.x - origin.x;
				float yb = box.max.y - origin.y;
				float zb = box.max.z - origin.z;

				if ((direction.x * yb - direction.y * xa < 0.0f)
				        || (direction.x * ya - direction.y * xb > 0.0f)
				        || (direction.x * za - direction.z * xa > 0.0f)
				        || (direction.x * zb - direction.z * xb < 0.0f)
				        || (direction.y * zb - direction.z * yb < 0.0f)
				        || (direction.y * za - direction.z * ya > 0.0f))
					return false;

				return true;
			}
			else
			{
				// case PPP: side(R,FB) < 0 or side(R,HD) > 0 or side(R,DC) > 0 or side(R,EF) < 0 or side(R,HE) < 0 or side(R,CB) > 0 to miss

				if ((origin.x > box.max.x) || (origin.y > box.max.y) || (origin.z > box.max.z))
					return false;

				float xa = box.min.x - origin.x;
				float ya = box.min.y - origin.y;
				float za = box.min.z - origin.z;
				float xb = box.max.x - origin.x;
				float yb = box.max.y - origin.y;
				float zb = box.max.z - origin.z;

				if ((direction.x * yb - direction.y * xa < 0.0f)
				        || (direction.x * ya - direction.y * xb > 0.0f)
				        || (direction.x * za - direction.z * xb > 0.0f)
				        || (direction.x * zb - direction.z * xa < 0.0f)
				        || (direction.y * zb - direction.z * ya < 0.0f)
				        || (direction.y * za - direction.z * yb > 0.0f))
					return false;

				return true;
			}
		}
	}

	return false;
}

bool Ray::hasIntersected(const BoundingVolume &volume) const
{
    if (hasIntersected(volume.sphere))
    {
        if (hasIntersected(volume.box))
            return true;
    }

    return false;
}

bool Ray::hasIntersected(const Plane &plane) const
{
    float t;
    Vector3 intersection;

    return hasIntersected(plane, t, intersection);
}

bool Ray::hasIntersected(const Plane &plane, float &t, Vector3 &intersection) const
{
    float denominator = Vector3::dot(direction, plane.n);

    // Early out: if ray is parallel to the plane then no intersection.
    if (Math::closeEnough(fabs(denominator), 0.0f))
    {
        float rayOriginToPlane = Plane::dot(plane, origin);

        // The ray lies in the plane if the ray origin is in the plane.
        // In such a case there's an infinite number of intersection points.
        if (Math::closeEnough(rayOriginToPlane, 0.0f))
        {
            t = 0.0f;
            return true;
        }
        else
        {
            return false;
        }
    }
    
    // Ray isn't parallel to plane. That means there's an intersection.
    t = -Plane::dot(plane, origin) / denominator;
    
    // Late out: rays and line segments are only defined for 't' >= 0.
    if (t < 0.0f)
        return false;
    
    intersection = origin + (direction * t);
    return true;
}