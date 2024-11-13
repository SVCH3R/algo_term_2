#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>

class Point {
 private:
  int64_t x_, y_;

 public:
  Point() {
    x_ = 0.0;
    y_ = 0.0;
  }
  Point(int64_t x, int64_t y) {
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
    return std::sqrt(std::pow(x_ - p.GetX(), 2) + std::pow(y_ - p.GetY(), 2));
  }
  bool operator==(const Point& p) const {
    return (p.GetX() == x_ && p.GetY() == y_);
  }
  bool operator!=(const Point& p) const {
    return not(*this == p);
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
  Vector(int64_t startx, int64_t starty, int64_t endx, int64_t endy) {
    x_ = endx - startx;
    y_ = endy - starty;
    length_ = std::sqrt(std::pow(std::abs(x_), 2) + std::pow(std::abs(y_), 2));
  };
  Vector(const Point& p1, const Point& p2) {
    x_ = p2.GetX() - p1.GetX();
    y_ = p2.GetY() - p1.GetY();
    length_ = std::sqrt(x_ * x_ + y_ * y_);
  }
  Vector(int64_t x, int64_t y) {
    x_ = x;
    y_ = y;
    length_ = std::sqrt(x * x + y * y);
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

std::ostream& operator<<(std::ostream& out, const Vector& v) {
  out << v.GetX();
  out << ' ';
  out << v.GetY();
  return out;
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
  out << p.GetX();
  out << ' ';
  out << p.GetY();
  return out;
}

bool SameSign(int64_t x, int64_t y) {
  return x * y >= 0;
}

int8_t Sign(int64_t x) {
  if (x == 0) {
    return 0;
  }
  if (x > 0) {
    return 1;
  }
  return -1;
}

class Polygon {
 private:
  int64_t number_;
  std::vector<Point> vertices_;

 public:
  Polygon(const int64_t& n, const std::vector<Point>& vert) {
    number_ = n;
    vertices_ = vert;
  }
  Polygon() {
    number_ = 0;
    vertices_ = {};
  }
  int64_t Size() const {
    return number_;
  }
  std::vector<Point> GetVector() const {
    return vertices_;
  }
  bool IsConvex() {
    Vector l0 = Vector(vertices_[0], vertices_[1]);
    Vector l1 = Vector(vertices_[1], vertices_[2]);
    int8_t sign = Sign(l0 ^ l1);
    for (int64_t i = 1; i < number_ - 2; ++i) {
      l0 = Vector(vertices_[i], vertices_[i + 1]);
      l1 = Vector(vertices_[i + 1], vertices_[i + 2]);
      if (not SameSign(sign, l0 ^ l1)) {
        return false;
      }
      if ((l0 ^ l1) != 0) {
        sign = Sign(l0 ^ l1);
      }
    }
    l0 = Vector(vertices_[number_ - 1], vertices_[0]);
    l1 = Vector(vertices_[0], vertices_[1]);
    return SameSign(sign, l0 ^ l1);
  }
  int64_t Area() {
    Point begin = vertices_[0];
    int64_t area = 0;
    for (int64_t i = 0; i < number_; ++i) {
      area += Vector(begin, vertices_[i % number_]) ^ Vector(vertices_[i % number_], vertices_[(i + 1) % number_]);
    }
    if (area < 0) {
      return -area;
    }
    return area;
  }
  ~Polygon() = default;
};

int8_t TurnSign(Point a, Point b, Point c) {
  int64_t v = a.GetX() * (b.GetY() - c.GetY()) + b.GetX() * (c.GetY() - a.GetY()) + c.GetX() * (a.GetY() - b.GetY());
  if (v < 0) {
    return -1;
  }
  if (v > 0) {
    return 1;
  }
  return 0;
}

bool Compare(const Point& a, const Point& b, const Point& c) {
  Vector v1(c, a);
  Vector v2(c, b);
  if ((v1 ^ v2) != 0) {
    return (v1 ^ v2) > 0;
  }
  return v1.GetX() * v1.GetX() + v1.GetY() * v1.GetY() < v2.GetX() * v2.GetX() + v2.GetY() * v2.GetY();
}

Polygon ConvexHull(std::vector<Point> points) {
  size_t size = points.size();
  Point left_point = points[0];
  for (size_t i = 1; i < size; ++i) {
    if (left_point.GetX() > points[i].GetX()) {
      left_point = points[i];
    }
    if (left_point.GetX() == points[i].GetX() && left_point.GetY() > points[i].GetY()) {
      left_point = points[i];
    }
  }
  std::vector<Point> add_vect;
  std::vector<Point> hull;
  for (size_t i = 0; i < points.size(); ++i) {
    if (points[i] != left_point) {
      add_vect.emplace_back(points[i]);
    }
  }
  add_vect.emplace_back(left_point);

  Point center = left_point;
  while (not add_vect.empty()) {
    size_t idx = 0;
    for (size_t i = 1; i < add_vect.size(); ++i) {
      if (Compare(add_vect[idx], add_vect[i], center)) {
        idx = i;
      }
    }
    hull.emplace_back(add_vect[idx]);
    center = add_vect[idx];
    add_vect.erase(add_vect.begin() + idx);
    if (center == left_point) {
      break;
    }
  }
  return Polygon(hull.size(), hull);
}

int main() {
  int64_t n, x, y;
  std::cin >> n;
  std::vector<Point> vert{};
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> x >> y;
    vert.emplace_back(Point(x, y));
  }
  Polygon convexhull = ConvexHull(vert);
  vert = convexhull.GetVector();
  std::cout << vert.size() << '\n';
  std::cout << vert.back() << '\n';
  for (size_t i = 0; i < vert.size() - 1; ++i) {
    std::cout << vert[i] << '\n';
  }
  int64_t area = convexhull.Area();
  std::cout << area / 2 << ((area % 2 == 1) ? ".5" : ".0");
}
