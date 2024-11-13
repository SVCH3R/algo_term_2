#pragma once
#include <string>
namespace geometry {
  class Point;
  class Vector {
   public:
    int64_t x_;
    int64_t y_;
    Vector(const int64_t& x, const int64_t& y);
    Vector();
    Vector(const Point& p1, const Point& p2);
    Vector operator+() const;
    Vector operator-() const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(const int64_t& scalar) const;
    Vector operator/(const int64_t& scalar) const;
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    int64_t operator^(const Vector& v) const;
    bool operator||(const Vector& v) const;
    bool Iscodir(const Vector& v) const;
    int64_t ScalarProduct(const Vector& v) const;
  };
}