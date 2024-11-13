#pragma once
#include "point.h"
namespace geometry {
  class Segment : public IShape {
    
   public:
    Point p1_, p2_;
    Segment();
    Segment(const Point& p1, const Point& p2);
    Segment(const Segment& s) = default;
    Segment& operator=(const Segment& s) = default;
    Segment(Segment&& seg) = default;
    Segment& operator=(Segment&& seg) = default;
    Point GetP1() const;
    Point GetP2() const;
    void SetP1(const Point& p);
    void SetP2(const Point& p);
    double Dist(const Point& p) const;
    Segment& Move(const Vector& v) override;
    bool ContainsPoint(const Point& p) const override;
    Segment* Clone() const override;
    bool CrossesSegment(const Segment& s) const override;
    std::string ToString() const override;
  };
}
