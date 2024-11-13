#pragma once
#include "IShape.h"
namespace geometry {
  class Point : public IShape {
   public:
    int64_t x_, y_;
    bool operator==(const Point& other) const;
    Point();
    Point(const Point&) = default;
    Point(const int64_t& x, const int64_t& y);
    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) = default;
    int64_t GetX() const;
    int64_t GetY() const;
    void SetX(const int64_t& x);
    void SetY(const int64_t& y);
    double Dist(const Point& p) const;
    Vector operator-(const Point& other) const;
    Point& Move(const Vector& v) override;
    bool ContainsPoint(const Point& p) const override;
    Point* Clone() const override;
    bool CrossesSegment(const Segment& s) const override;
    std::string ToString() const override;
  };
}