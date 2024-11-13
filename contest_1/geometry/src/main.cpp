#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <string>
#include "../IShape.h"
#include "../vector.h"
#include "../point.h"
#include "../line.h"
#include "../ray.h"
#include "../segment.h"
#include "../polygon.h"
#include "../circle.h"

namespace geometry {
  // vector
  Vector::Vector(const int64_t& x, const int64_t& y) : x_(x), y_(y) {}
  Vector::Vector() : x_(0), y_(0) {}
  Vector::Vector(const Point& p1, const Point& p2) {
    x_ = p2.GetX() - p1.GetX();
    y_ = p2.GetY() - p1.GetY();
  }
  Vector Vector::operator+() const {
    return *this;
  }
  Vector Vector::operator-() const {
    return Vector(-x_, -y_);
  }
  Vector Vector::operator+(const Vector& other) const {
    return Vector(x_ + other.x_, y_ + other.y_);
  }
  Vector Vector::operator-(const Vector& other) const {
    return Vector(x_ - other.x_, y_ - other.y_);
  }
  Vector Vector::operator*(const int64_t& scalar) const {
    return Vector(x_ * scalar, y_ * scalar);
  }
  Vector Vector::operator/(const int64_t& scalar) const {
    return Vector(x_ / scalar, y_ / scalar);
  }
  bool Vector::operator==(const Vector& other) const {
    return x_ == other.x_ && y_ == other.y_;
  }
  bool Vector::operator!=(const Vector& other) const {
    return not (*this == other);
  }
  int64_t Vector::operator^(const Vector& v) const {
    return x_ * v.y_ - y_ * v.x_;
  }
  bool Vector::operator||(const Vector& v) const {
    return (*this ^ v) == 0;
  }
  bool Vector::Iscodir(const Vector& v) const {
    return (*this || v) && (this->x_ * v.x_ >= 0) && (this->y_ * v.y_ >= 0);
  }
  int64_t Vector::ScalarProduct(const Vector& v) const {
    return x_ * v.x_ + y_ * v.y_;
  }

  // vector


  // point
  Point::Point() : x_(0), y_(0) {}
  Point::Point(const int64_t& x, const int64_t& y) : x_(x), y_(y) {}
  int64_t Point::GetX() const {
    return x_;
  }
  int64_t Point::GetY() const {
    return y_;
  }
  void Point::SetX(const int64_t& x) {
    x_ = x;
  }
  void Point::SetY(const int64_t& y) {
    y_ = y;
  }
  Vector Point::Point::operator-(const Point& other) const {
    return Vector(other.GetX() - this->x_, other.GetY() - this->y_);
  }
  Point& Point::Move(const Vector& v) {
    *this = Point(x_ - v.x_, y_ - v.y_);
    return *this;
  }
  bool Point::operator==(const Point& other) const {
    return this->x_ == other.x_ && this->y_ == other.y_;
  }
  bool Point::ContainsPoint(const Point& p) const {
    return *this == p;
  }
  Point* Point::Clone() const {
    return new Point(x_, y_);
  }
  bool Point::CrossesSegment(const Segment& s) const {
    if (s.GetP1() == s.GetP2()) {
      return s.GetP1() == *this;
    }
    return s.ContainsPoint(*this);
  }
  std::string Point::ToString() const {
    std::string output;
    output += "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
    return output;
  }
  double Point::Dist(const Point& p) const {
    return sqrt(pow(x_ - p.GetX(), 2) + pow(y_ - p.GetY(), 2));
  }
  // point

  double Line::Dist(const Point& p) const {
    return std::abs(a_ * p.GetX() + b_ * p.GetY() + c_) / sqrt(a_ * a_ + b_ * b_);
  }

  //segment
  Segment::Segment() : p1_(Point()), p2_(Point()) {}
  Segment::Segment(const Point& p1, const Point& p2) : p1_(p1), p2_(p2) {}
  Point Segment::GetP1() const {
    return p1_;
  }
  Point Segment::GetP2() const {
    return p2_;
  }
  void Segment::SetP1(const Point& p) {
    p1_ = p;
  }
  void Segment::SetP2(const Point& p) {
    p2_ = p;
  }
  Segment& Segment::Move(const Vector& v) {
    *this = Segment(p1_.Move(v), p2_.Move(v));
    return *this;
  }
  bool Segment::ContainsPoint(const Point& p) const {
    if (p1_ == p2_) {
      return p == p1_;
    }
    return Ray(p1_, p2_).ContainsPoint(p) && Ray(p2_, p1_).ContainsPoint(p);
  }
  Segment* Segment::Clone() const {
    return new Segment(p1_, p2_);
  }
  std::string Segment::ToString() const {
    std::string output;
    output += "Segment(" + p1_.ToString() + ", " + p2_.ToString() + ")";
    return output;
  }
  bool Segment::CrossesSegment(const Segment& s) const {
    Vector ab = Vector(p1_, p2_);
    Vector ac = Vector(p1_, s.GetP1());
    Vector ad = Vector(p1_, s.GetP2());

    Vector cd = Vector(s.GetP1(), s.GetP2());
    Vector ca = -ac;
    Vector cb = Vector(s.GetP1(), p2_);
    if ((ab ^ ac) == 0 && (ab ^ ad) == 0 && (cd ^ ca) == 0 && (cd ^ cb) == 0) {
      return s.ContainsPoint(p1_) || s.ContainsPoint(p2_) || this->ContainsPoint(s.GetP1()) || this->ContainsPoint(s.GetP2());
    }
    Line guideline1 = Line(p1_, p2_);
    Line guideline2 = Line(s.GetP1(), s.GetP2());
    return (guideline1.Equation(s.GetP1()) * guideline1.Equation(s.GetP2()) <= 0 &&
            guideline2.Equation(p1_) * guideline2.Equation(p2_) <= 0);
  }

  double Segment::Dist(const Point& p) const {
    if (Vector(p1_, p).ScalarProduct(Vector(p1_, p2_)) >= 0 && Vector(p2_, p).ScalarProduct(Vector(p2_, p1_)) >= 0) {
      Line guideline = Line(p1_, p2_);
      return guideline.Dist(p);
    }
    if (Vector(p1_, p).ScalarProduct(Vector(p1_, p2_)) >= 0 && Vector(p2_, p).ScalarProduct(Vector(p2_, p1_)) <= 0) {
      return p2_.Dist(p);
    }
    return p1_.Dist(p);
  }

  // segment

  // line
  Line::Line(const Point& p1, const Point& p2) {
    p1_ = p1;
    p2_ = p2;
    a_ = p2.GetY() - p1.GetY();
    b_ = p1.GetX() - p2.GetX();
    c_ = -p1.GetY() * b_ - p1.GetX() * a_;
  }
  Line::Line() {
    *this = Line(Point(), Point());
  }
  Line& Line::Move(const Vector& v) {
    *this = Line(p1_.Move(v), p2_.Move(v));
    return *this;
  }
  int64_t Line::GetA() const {
    return a_;
  }
  int64_t Line::GetB() const {
    return b_;
  }
  int64_t Line::GetC() const {
    return c_;
  }
  bool Line::ContainsPoint(const Point& p) const {
    return Ray(p1_, p2_).ContainsPoint(p) || Ray(p2_, p1_).ContainsPoint(p);
  }
  Line* Line::Clone() const {
    return new Line(p1_, p2_);
  }
  int64_t Line::Equation(const Point& p) const {
    return a_ * p.GetX() + b_ * p.GetY() + c_;
  }
  bool Line::CrossesSegment(const Segment& s) const {
    return Equation(s.GetP1()) * Equation(s.GetP2()) <= 0;
  }
  std::string Line::ToString() const {
    std::string output;
    output += "Line(" + std::to_string(a_) + ", " + std::to_string(b_) + ", " + std::to_string(c_) + ")";
    return output;
  }
  // line

  // ray
    Ray::Ray() {
    p1_ = Point(0, 0);
    p2_ = Point(0, 0);
  }
  Ray::Ray(const Point& p1, const Point& p2) {
    p1_ = p1;
    p2_ = p2;
  }
  Ray& Ray::Move(const Vector& v) {
    p1_.Move(v);
    p2_.Move(v);
    return *this;
  }
  bool Ray::ContainsPoint(const Point& p) const {
    Vector newvect = Vector(p1_, p);
    return newvect.Iscodir(Vector(p1_, p2_));
  }
  Ray* Ray::Clone() const {
    return new Ray(p1_, p2_);
  }
  bool Ray::CrossesSegment(const Segment& s) const {
    //Vector vec_ab{seg.end.x - seg.start.x, seg.end.y - seg.start.y};
    Vector ab = Vector(s.GetP1(), s.GetP2());
    Vector oa = Vector(p1_, s.GetP1());
    Vector ob = Vector(p1_, s.GetP2());
    Vector dir = Vector(p1_, p2_);
    if ((dir ^ oa) * (dir ^ ob) <= 0) {
      return ((-oa) ^ ab) * (dir ^ ab) < 0 || ContainsPoint(s.GetP1()) || ContainsPoint(s.GetP2());
    }
    return false;
  }
  std::string Ray::ToString() const {
    std::string output;
    output += "Ray(" + p1_.ToString() + ", " + "Vector(" + std::to_string(Vector(p1_, p2_).x_) + ", " + std::to_string(Vector(p1_, p2_).y_) + "))";
  return output;
  }
  // ray

  // polygon
    Polygon::Polygon(const std::vector<Point>& vert) {
    vertices_ = vert;
  }
  Polygon::Polygon() {
    vertices_ = {};
  }
  Polygon& Polygon::Move(const Vector& v) {
    size_t size = vertices_.size();
    for (size_t i = 0; i < size; ++i) {
      vertices_[i].Move(v);
    }
    return *this;
  }
  bool Polygon::ContainsPoint(const Point& point) const {
    size_t size = vertices_.size();
    bool result = false;
    for (size_t i = 0; i < size; ++i) {
      Point p1 = vertices_[i];
      Point p2 = vertices_[(i + 1) % size];
      if (Segment(p1, p2).ContainsPoint(point)) {
        return true;
      }
      if ((p1.GetY() > point.GetY()) != (p2.GetY() > point.GetY())) {
        int64_t cross = (p2.GetX() - p1.GetX()) * (point.GetY() - p1.GetY()) / (p2.GetY() - p1.GetY()) + p1.GetX();
        if (point.GetX() < cross) {
          result = !result;
        }
      }
    }
    return result;
  }
  Polygon* Polygon::Clone() const {
    return new Polygon(vertices_);
  }
  bool Polygon::CrossesSegment(const Segment& s) const {
    size_t size = vertices_.size();
    for (size_t i = 0; i < size; ++i) {
      if (Segment(vertices_[i % size], vertices_[(i + 1) % size]).CrossesSegment(s)) {
        return true;
      }
    }
    return false;
  }
  std::string Polygon::ToString() const {
    std::string output = "Polygon(";
    size_t size = vertices_.size();
    for (size_t i = 0; i < size; ++i) {
      output += vertices_[i].ToString() + ", ";
    }
    output.pop_back();
    output.pop_back();
    output.push_back(')');
    return output;
  }
  // polygon

  // circle
    Circle::Circle(const Point& p, int64_t r) : center_(p), radius_(r) {}
  Circle::Circle() : center_(Point()), radius_(0) {}
  Circle& Circle::Move(const Vector& v) {
    center_.Move(v);
    return *this;
  }
  bool Circle::IsOn(const Point& p) const {
    return (p.GetX() - center_.GetX()) * (p.GetX() - center_.GetX()) + (p.GetY() - center_.GetY()) * (p.GetY() - center_.GetY()) == radius_ * radius_;
  }
  bool Circle::ContainsPoint(const Point& p) const {
    return (p.GetX() - center_.GetX()) * (p.GetX() - center_.GetX()) + (p.GetY() - center_.GetY()) * (p.GetY() - center_.GetY()) <= radius_ * radius_;
  }
  Circle* Circle::Clone() const {
    return new Circle(center_, radius_);
  }
  bool Circle::CrossesSegment(const Segment& s) const {
    Point p1 = s.GetP1();
    Point p2 = s.GetP2();
    return IsOn(p1) || IsOn(p2) || (ContainsPoint(p1) && !ContainsPoint(p2)) || (ContainsPoint(p2) && !ContainsPoint(p1)) || (!ContainsPoint(p2) && !ContainsPoint(p1) && s.Dist(center_) <= radius_);
  }

  std::string Circle::ToString() const {
    std::string output = "Circle(";
    output += center_.ToString() + ", " + std::to_string(radius_) + ")";
    return output;
  }
  // circle
}
