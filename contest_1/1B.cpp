#include <iostream>
#include <cmath>
#include <iomanip>

class Vector {
 private:
  double x_, y_;
  double length_;

 public:
  Vector() {
    x_ = 0.0;
    y_ = 0.0;
    length_ = 0.0;
  };
  Vector(const int& startx, const int& starty, const int& endx, const int& endy) {
    x_ = endx - startx;
    y_ = endy - starty;
    length_ = sqrt(pow(fabs(endx - startx), 2) + pow(fabs(endy - starty), 2));
  };
  Vector(const int& x, const int& y) {
    x_ = x;
    y_ = y;
    length_ = sqrt(pow(x, 2) + pow(y, 2));
  };
  double GetX() const {
    return x_;
  }
  double GetY() const {
    return y_;
  }
  double Len() const {
    return length_;
  }
  Vector operator+(const Vector& v) {
    return Vector(x_ + v.GetX(), y_ + v.GetY());
  }
  double operator*(const Vector& v) {
    return x_ * v.GetX() + y_ * v.GetY();
  }
  double operator^(const Vector& v) {
    return x_ * v.GetY() - y_ * v.GetX();
  }
  bool operator||(const Vector& v) {
    return (*this ^ v) == 0;
  }
};

class Line {
 private:
  double parameter_a_, parameter_b_, parameter_c_;
  Vector guide_;

 public:
  Line(const int& a, const int& b, const int& c) {
    parameter_a_ = a;
    parameter_b_ = b;
    parameter_c_ = c;
    guide_ = Vector(b, -a);
  }
  double GetA() const {
    return parameter_a_;
  }
  double GetB() const {
    return parameter_b_;
  }
  double GetC() const {
    return parameter_c_;
  }
  Vector Guide() const {
    return guide_;
  }
  bool operator||(const Line& l) const {
    return (this->Guide() || l.Guide());
  }
  double CrossX(const Line& line) const {
    double y;
    if (parameter_a_ == 0) {
      y = -parameter_c_ / parameter_b_;
      return (-line.GetC() - line.GetB() * y) / line.GetA();
    }
    y = (parameter_c_ * line.GetA() - parameter_a_ * line.GetC()) /
        (parameter_a_ * line.GetB() - line.GetA() * parameter_b_);
    return (-parameter_c_ - parameter_b_ * y) / parameter_a_;
  }
  double CrossY(const Line& line) const {
    if (parameter_a_ == 0) {
      return -parameter_c_ / parameter_b_;
    }
    return (parameter_c_ * line.GetA() - parameter_a_ * line.GetC()) /
           (parameter_a_ * line.GetB() - line.GetA() * parameter_b_);
  }
  double Dist(const Line& line) const {
    if (parameter_b_ != 0) {
      return fabs((line.GetC() / line.GetB() - parameter_c_ / parameter_b_) * cos(atan(-parameter_a_ / parameter_b_)));
    }
    return fabs(line.GetC() / line.GetA() - parameter_c_ / parameter_a_);
  }
};

std::ostream& operator<<(std::ostream& out, const Vector& v) {
  out << v.GetX();
  out << ' ';
  out << v.GetY();
  return out;
}

int main() {
  int a1, b1, c1, a2, b2, c2;
  std::cin >> a1 >> b1 >> c1;
  std::cin >> a2 >> b2 >> c2;

  Line line1 = Line(a1, b1, c1);
  Line line2 = Line(a2, b2, c2);
  std::cout << std::fixed << std::setprecision(6) << line1.Guide() << '\n' << line2.Guide() << '\n';
  if (line1 || line2) {
    std::cout << std::fixed << std::setprecision(6) << line1.Dist(line2);
  } else {
    std::cout << std::fixed << std::setprecision(6) << line1.CrossX(line2) << ' ' << line1.CrossY(line2);
  }
}