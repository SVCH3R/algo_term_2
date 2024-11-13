#include <iostream>
#include <cmath>
#include <iomanip>



class Vector {
 private:
  int x_, y_;
  double length_;

 public:
  Vector(int startx, int starty, int endx, int endy) {
    this->x_ = endx - startx;
    this->y_ = endy - starty;
    this->length_ = sqrt(pow(abs(endx - startx), 2) + pow(abs(endy - starty), 2));
  };
  Vector(int x, int y) {
    this->x_ = x;
    this->y_ = y;
    this->length_ = sqrt(pow(abs(x), 2) + pow(abs(y), 2));
  };
  double GetX() {
    return this->x_;
  }
  double GetY() {
    return this->y_;
  }
  double Len() {
    return this->length_;
  }
  Vector operator+(Vector v) {
    return Vector(this->x_ + v.GetX(), this->y_ + v.GetY());
  }
  double operator*(Vector v) {
    return this->x_ * v.GetX() + this->y_ * v.GetY();
  }
  double operator^(Vector v) {
    return this->x_ * v.GetY() - this->y_ * v.GetX();
  }
};

double Square(Vector v1, Vector v2) {
  return 0.5 * abs(v1 ^ v2);
}

int main() {
  int startx_1, startx_2, endx_1, endx_2, starty_1, starty_2, endy_1, endy_2;
  std::cin >> startx_1;
  std::cin >> starty_1;
  std::cin >> endx_1;
  std::cin >> endy_1;
  std::cin >> startx_2;
  std::cin >> starty_2;
  std::cin >> endx_2;
  std::cin >> endy_2;
  Vector v1 = Vector(startx_1, starty_1, endx_1, endy_1);
  Vector v2 = Vector(startx_2, starty_2, endx_2, endy_2);
  Vector vsum = v1 + v2;
  std::cout << std::fixed << std::setprecision(6) << v1.Len() << ' ' << v2.Len() << '\n';
  std::cout << std::fixed << std::setprecision(6) << vsum.GetX() << ' ' << vsum.GetY() << '\n';
  std::cout << std::fixed << std::setprecision(6) << v1 * v2 << ' ' << (v1 ^ v2) << '\n';
  std::cout << std::fixed << std::setprecision(6) << Square(v1, v2);
}
