#pragma once
#include "IShape.h"
#include "point.h"
namespace geometry {
  class Line : public IShape {
   public:
    int64_t a_, b_, c_;
    Point p1_, p2_;
    Line(const Point& p1, const Point& p2);
    Line();
    Line& Move(const Vector& v) override;
    int64_t GetA() const;
    int64_t GetB() const;
    int64_t GetC() const;
    double Dist(const Point& p) const;
    bool ContainsPoint(const Point& p) const override;
    Line* Clone() const override;
    int64_t Equation(const Point& p) const;
    bool CrossesSegment(const Segment& s) const override;
    std::string ToString() const override;
  };
}

