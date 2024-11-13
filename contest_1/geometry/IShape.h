#pragma once
#include "vector.h"
#include <string>
namespace geometry {
  class Segment;
  class Point;
  class IShape
  {
   public:
    virtual ~IShape() = default;
    virtual IShape& Move(const Vector& v) = 0;
    virtual bool ContainsPoint(const Point& p) const = 0;
    virtual bool CrossesSegment(const Segment& s) const = 0;
    virtual IShape* Clone() const = 0;
    virtual std::string ToString() const = 0;
  };
}
