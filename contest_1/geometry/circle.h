#pragma once
#include "point.h"
namespace geometry {
  class Circle : public IShape {
   public:
    Point center_;
    int64_t radius_;
    Circle(const Point& p, int64_t r);
    Circle();
    Circle& Move(const Vector& v) override;
    bool ContainsPoint(const Point& p) const override;
    Circle* Clone() const override;
    bool CrossesSegment(const Segment& s) const override;
    std::string ToString() const override;
    bool IsOn(const Point& p) const;
  };
}