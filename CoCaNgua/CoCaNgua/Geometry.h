#ifndef _CG_GEOMETRY_H_
#define _CG_GEOMETRY_H_
#include <algorithm>
class Size
{
public:
  float width, height;
  Size()
  {
    width = height = 0;
  }
  Size(float pWidth, float pHeight)
  {
    width = pWidth;
    height = pHeight;
  }
};

class Rect
{
public:
  Vector2 origin;
  Size size;

  Rect() {};
  Rect(Rect& other);
  Rect(Vector2 pOrigin, Size pSize);
  Rect(float x, float y, float width, float height);
  void setRect(float x, float y, float width, float height);
  bool containsPoint(const Vector2& point) const;
  bool intersectsRect(const Rect& rect) const;

  float getMinX() const; /// return the leftmost x-value of current rect
  float getMidX() const; /// return the midpoint x-value of current rect
  float getMaxX() const; /// return the rightmost x-value of current rect
  float getMinY() const; /// return the bottommost y-value of current rect
  float getMidY() const; /// return the midpoint y-value of current rect
  float getMaxY() const; /// return the topmost y-value of current rect

  friend Rect operator+(const Rect& lhs, const Rect& rhs);
};

inline Rect::Rect(Rect& other)
{
  setRect(other.origin.x, other.origin.y, other.size.width, other.size.height);
}

inline Rect::Rect(Vector2 pOrigin, Size pSize)
{
  setRect(pOrigin.x, pOrigin.y, pSize.width, pSize.height);
}

inline Rect::Rect(float x, float y, float width, float height)
{
  setRect(x, y, width, height);
}

inline void Rect::setRect(float x, float y, float width, float height)
{
  origin.x = x;
  origin.y = y;

  size.width = width;
  size.height = height;
}

inline bool Rect::containsPoint(const Vector2& point) const
{
  bool bRet = false;

  if (point.x >= getMinX() && point.x <= getMaxX()
    && point.y >= getMinY() && point.y <= getMaxY())
  {
    bRet = true;
  }

  return bRet;
}

inline bool Rect::intersectsRect(const Rect& rect) const
{
  return !(     getMaxX() < rect.getMinX() ||
    rect.getMaxX() <      getMinX() ||
    getMaxY() < rect.getMinY() ||
    rect.getMaxY() <      getMinY());
}

inline float Rect::getMaxX() const
{
  return (float)(origin.x + size.width);
}

inline float Rect::getMidX() const
{
  return (float)(origin.x + size.width / 2.0);
}

inline float Rect::getMinX() const
{
  return origin.x;
}

inline float Rect::getMaxY() const
{
  return origin.y + size.height;
}

inline float Rect::getMidY() const
{
  return (float)(origin.y + size.height / 2.0);
}

inline float Rect::getMinY() const
{
  return origin.y;
}

inline Rect operator+(const Rect& lhs, const Rect& rhs)
{
  float minX = min(lhs.getMinX(), rhs.getMinX());
  float minY = min(lhs.getMinY(), rhs.getMinY());
  float maxX = max(lhs.getMaxX(), rhs.getMaxX());
  float maxY = max(lhs.getMaxY(), rhs.getMaxY());

  return Rect(minX, minY, maxX-minX, maxY-minY);
}

#endif