#pragma once
#include <vector>
#include "point.h"
namespace geometry {
  class Polygon : public IShape {

   public:
    std::vector<Point> vertices_;
    explicit Polygon(const std::vector<Point>& vert);
    Polygon();
    Polygon& Move(const Vector& v) override;
    bool ContainsPoint(const Point& point) const override;
    Polygon* Clone() const override;
    bool CrossesSegment(const Segment& s) const override;
    std::string ToString() const override;
  };  
}
