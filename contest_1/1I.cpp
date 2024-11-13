#include <iostream>
#include <cmath>
#include <iomanip>
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
  int64_t Dist(const Point& p) const {
    return sqrt(pow(x_ - p.GetX(), 2) + pow(y_ - p.GetY(), 2));
  }
  void SetX(int64_t x) {
    x_ = x;
  }
  void SetY(int64_t y) {
    y_ = y;
  }
};

class Vector {
 private:
  int64_t x_, y_;
  int64_t length_;

 public:
  Vector() {
    x_ = 0.0;
    y_ = 0.0;
    length_ = 0.0;
  };
  Vector(int64_t startx, int64_t starty, int64_t endx, int64_t endy) {
    x_ = endx - startx;
    y_ = endy - starty;
    length_ = sqrt(pow(fabs(x_), 2) + pow(fabs(y_), 2));
  };
  Vector(const Point& p1, const Point& p2) {
    x_ = p2.GetX() - p1.GetX();
    y_ = p2.GetY() - p1.GetY();
    length_ = sqrt(pow(fabs(x_), 2) + pow(fabs(y_), 2));
  }
  Vector(int64_t x, int64_t y) {
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
  int64_t Len() const {
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

bool SameSign(int64_t x, int64_t y) {
  return x * y >= 0;
}

int8_t Sign(int64_t x) {
  if (x == 0) {
    return 0;
  }
  return x / fabs(x);
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

int main() {
  int64_t n, x, y;
  std::cin >> n;
  std::vector<Point> vert;
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> x >> y;
    vert.emplace_back(Point(x, y));
  }
  int64_t area = Polygon(n, vert).Area();
  std::cout << area / 2 << ((area % 2 == 1) ? ".5" : ".0");
}
