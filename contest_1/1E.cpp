#include <iostream>
#include <cmath>
#include <iomanip>

class Point {
 private:
  int64_t x_, y_;

 public:
  Point() {
    x_ = 0.0;
    y_ = 0.0;
  }
  Point(const int64_t& x, const int64_t& y) {
    x_ = x;
    y_ = y;
  }
  int64_t GetX() const {
    return x_;
  }
  int64_t GetY() const {
    return y_;
  }
  double Dist(const Point& p) const {
    return sqrt(pow(x_ - p.GetX(), 2) + pow(y_ - p.GetY(), 2));
  }
};

class Vector {
 private:
  int64_t x_, y_;
  double length_;

 public:
  Vector() {
    x_ = 0.0;
    y_ = 0.0;
    length_ = 0.0;
  };
  Vector(const int64_t& startx, const int64_t& starty, const int64_t& endx, const int64_t& endy) {
    x_ = endx - startx;
    y_ = endy - starty;
    length_ = sqrt(pow(fabs(x_), 2) + pow(fabs(y_), 2));
  };
  Vector(const Point& p1, const Point& p2) {
    x_ = p2.GetX() - p1.GetX();
    y_ = p2.GetY() - p1.GetY();
    length_ = sqrt(pow(fabs(x_), 2) + pow(fabs(y_), 2));
  }
  Vector(const int64_t& x, const int64_t& y) {
    x_ = x;
    y_ = y;
    length_ = sqrt(pow(fabs(x), 2) + pow(fabs(y), 2));
  };
  int64_t GetX() const {
    return x_;
  }
  int64_t GetY() const {
    return y_;
  }
  double Len() const {
    return length_;
  }
  Vector operator+(const Vector& v) const {
    return Vector(x_ + v.GetX(), y_ + v.GetY());
  }
  Vector operator-() const {
    return Vector(-x_, -y_);
  }
  int64_t operator*(const Vector& v) const {
    return x_ * v.GetX() + y_ * v.GetY();
  }
  int64_t operator^(const Vector& v) const {
    return x_ * v.GetY() - y_ * v.GetX();
  }
  bool operator||(const Vector& v) const {
    return (*this ^ v) == 0;
  }
  bool Iscodir(Vector v) {
    return (*this || v) && (this->x_ * v.GetX() >= 0) && (this->y_ * v.GetY() >= 0);
  }
};

Point Plusvect(Point p, Vector v) {
  return Point(p.GetX() + v.GetX(), p.GetY() + v.GetY());
}

class Line {
 private:
  int64_t a_, b_, c_;
  Vector guide_;

 public:
  Line(const int64_t& a, const int64_t& b, const int64_t& c) {
    a_ = a;
    b_ = b;
    c_ = c;
    guide_ = Vector(b, -a);
  }
  Line(const int64_t& x1, const int64_t& y1, const int64_t& x2, const int64_t& y2) {
    a_ = y2 - y1;
    b_ = x1 - x2;
    c_ = -y1 * b_ - x1 * a_;
  }
  Line(const Vector& v, const Point& p) {
    *this = Line(p, Plusvect(p, v));
  }
  Line(const Point& p1, const Point& p2) {
    a_ = p2.GetY() - p1.GetY();
    b_ = p1.GetX() - p2.GetX();
    c_ = -p1.GetY() * b_ - p1.GetX() * a_;
  }
  Line(const Point& p, const Vector& v) {
    *this = Line(p, Point(p.GetX() + v.GetX(), p.GetY() + v.GetY()));
  }
  int64_t GetA() const {
    return a_;
  }
  int64_t GetB() const {
    return b_;
  }
  int64_t GetC() const {
    return c_;
  }
  Vector Guide() const {
    return guide_;
  }
  bool operator||(const Line& l) const {
    return guide_ || l.Guide();
  }
  int64_t Equation(const Point& p) const {
    return a_ * p.GetX() + b_ * p.GetY() + c_;
  }
  int64_t CrossX(const Line& l) const {
    int64_t y;
    if (a_ == 0) {
      y = -c_ / b_;
      return (-l.GetC() - l.GetB() * y) / l.GetA();
    }
    y = (c_ * l.GetA() - a_ * l.GetC()) / (a_ * l.GetB() - l.GetA() * b_);
    return (-c_ - b_ * y) / a_;
  }
  int64_t CrossY(const Line& l) const {
    if (a_ == 0) {
      return -c_ / b_;
    }
    return (c_ * l.GetA() - a_ * l.GetC()) / (a_ * l.GetB() - l.GetA() * b_);
  }
  double Dist(const Line& l) const {
    if (b_ != 0) {
      return fabs((l.GetC() / l.GetB() - c_ / b_) * cos(atan(-a_ / b_)));
    }
    return fabs(l.GetC() / l.GetA() - c_ / a_);
  }
  bool DoesBelong(const Point& p) const {
    return a_ * p.GetX() + b_ * p.GetY() + c_ == 0;
  }
  double Dist(const Point& p) {
    return fabs(a_ * p.GetX() + b_ * p.GetY() + c_) / sqrt(a_ * a_ + b_ * b_);
  }
};

std::ostream& operator<<(std::ostream& out, const Vector& v) {
  out << v.GetX();
  out << ' ';
  out << v.GetY();
  return out;
}
class Beam {
 private:
  Vector guide_;
  Point point_;

 public:
  Beam() {
    guide_ = Vector(0, 0);
    point_ = Point(0.0, 0.0);
  };
  Beam(const Point& p1, const Point& p2) {
    guide_ = Vector(p1, p2);
    point_ = p1;
  }
  Beam(const int64_t& x1, const int64_t& y1, const int64_t& x2, const int64_t& y2) {
    *this = Beam(Point(x1, y1), Point(x2, y2));
  }
  Beam(const Vector& v, const Point& p) {
    *this = Beam(p, Plusvect(p, v));
  }
  bool DoesBelong(const Point& p) const {
    Vector newvect = Vector(point_, p);
    return newvect.Iscodir(guide_);
  }
  double Dist(const Point& p) const {
    if (Vector(point_, p) * guide_ >= 0) {
      Line guideline = Line(point_, guide_);
      return guideline.Dist(p);
    }
    return point_.Dist(p);
  }
};

class Segment {
 private:
  Point p1_, p2_;
  double length_;

 public:
  Segment() {
    p1_ = Point(0, 0);
    p2_ = Point(0, 0);
    length_ = 0;
  }
  Segment(const Point& p1, const Point& p2) {
    p1_ = p1;
    p2_ = p2;
    length_ = sqrt(pow(p1.GetX() - p2.GetX(), 2) + pow(p1.GetY() - p2.GetY(), 2));
  }
  Segment(const int64_t& x1, const int64_t& y1, const int64_t& x2, const int64_t& y2) {
    *this = Segment(Point(x1, y1), Point(x2, y2));
  }
  Point GetP1() const {
    return p1_;
  }
  Point GetP2() const {
    return p2_;
  }
  bool DoesBelong(const Point& p) const {
    Beam beam1 = Beam(p1_, p2_);
    Beam beam2 = Beam(p2_, p1_);
    return beam1.DoesBelong(p) && beam2.DoesBelong(p);
  }
  double Dist(const Point& p) const {
    if (Vector(p1_, p) * Vector(p1_, p2_) >= 0 && Vector(p2_, p) * Vector(p2_, p1_) >= 0) {
      Line guideline = Line(p1_, p2_);
      return guideline.Dist(p);
    }
    if (Vector(p1_, p) * Vector(p1_, p2_) >= 0 && Vector(p2_, p) * Vector(p2_, p1_) <= 0) {
      return p2_.Dist(p);
    }
    return p1_.Dist(p);
  }

  bool Crosses(const Segment& s) const {
    Vector ab = Vector(p1_, p2_);
    Vector ac = Vector(p1_, s.GetP1());
    Vector ad = Vector(p1_, s.GetP2());

    Vector cd = Vector(s.GetP1(), s.GetP2());
    Vector ca = -ac;
    Vector cb = Vector(s.GetP1(), p2_);
    if ((ab ^ ac) == 0 && (ab ^ ad) == 0 && (cd ^ ca) == 0 && (cd ^ cb) == 0) {
      return s.DoesBelong(p1_) || s.DoesBelong(p2_) || this->DoesBelong(s.GetP1()) || this->DoesBelong(s.GetP2());
    }
    Line guideline1 = Line(p1_, p2_);
    Line guideline2 = Line(s.GetP1(), s.GetP2());
    return (guideline1.Equation(s.GetP1()) * guideline1.Equation(s.GetP2()) <= 0 &&
            guideline2.Equation(p1_) * guideline2.Equation(p2_) <= 0);
  }
};

int main() {
  int64_t x1, x2, x3, x4, y1, y2, y3, y4;
  std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
  Segment s1 = Segment(x1, y1, x2, y2);
  Segment s2 = Segment(x3, y3, x4, y4);
  if (s1.Crosses(s2)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}
