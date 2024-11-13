#pragma once
#include "point.h"
namespace geometry {
  class Ray : public IShape {
    
   public:
    Point p1_, p2_;
    Ray();
    Ray(const Point& p1, const Point& p2);
    Ray& Move(const Vector& v) override;
    bool ContainsPoint(const Point& p) const override;
    Ray* Clone() const override;
    bool CrossesSegment(const Segment& s) const override;
    std::string ToString() const override;
  };
}

