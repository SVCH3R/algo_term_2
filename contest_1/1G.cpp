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
  bool Iscodir(const Vector& v) const {
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

struct Polygon {
  int64_t size_;
  std::vector<Point> vertices_;

  Polygon(const int64_t& n, const std::vector<Point>& vert) {
    size_ = n;
    vertices_ = vert;
  }
  Polygon() {
    size_ = 0;
    vertices_ = {};
  }
  std::vector<Point> GetVect() const {
    return vertices_;
  }
  size_t GetSize() const {
    return size_;
  }
  bool IsConvex() {
    Vector l0 = Vector(vertices_[0], vertices_[1]);
    Vector l1 = Vector(vertices_[1], vertices_[2]);
    int8_t sign = Sign(l0 ^ l1);
    for (int64_t i = 1; i < size_ - 2; ++i) {
      l0 = Vector(vertices_[i], vertices_[i + 1]);
      l1 = Vector(vertices_[i + 1], vertices_[i + 2]);
      if (not SameSign(sign, l0 ^ l1)) {
        return false;
      }
      if ((l0 ^ l1) != 0) {
        sign = Sign(l0 ^ l1);
      }
    }
    l0 = Vector(vertices_[size_ - 1], vertices_[0]);
    l1 = Vector(vertices_[0], vertices_[1]);
    return SameSign(sign, l0 ^ l1);
  }
  ~Polygon() = default;
};
// а мне больше классы нравятся...
// Average Structure Fan
// /(//*******/**********************,,,*,,,,,**,*,************////////////////////
// ////*////***************************,********,**,,**,***************************
// ********************,*,,,,,,,*((#&&@@@@@@@@@@@@&&&%/*,,,,***********************
// ****************,,,,,,,,,,*/%&@@@@@@@@@@@@@@@@@@@@@@@&(**********///*///////////
// **********************,,*%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&%/********************//
// ********************,**%@@@@@@@@@@@@&&@@@@@@@@@@@@@@@@@@@&*,,,,,,***************
// ******,**,,,,,,,,,,,,(@&&&@&&&&&%&&&%%%%&&@&@@@@@@@&&&&&&&&*,,,,,***************
// ****,*,,,,,,,,,,,,,,(&&%%&&%%%&&%%&&&%%%%&&&&&&&&&&%%%%%#%&%********************
// ***************,,,,,(%%%%%%%%&&%&#/#&%#%####%%%%%%#(/((((#%%********************
// ***************,,,,,*%%%%%%%#(//*,,,,,,,,..,,,,,,,,***//(#%%,,,,,,,*,***********
// **,,,,,,,,,,,,,,,,,,.*%%%%###(***,,,,,,,.......,,,,,,/#((#%&*,,,,,,,,***********
// ,,,,,,,,,,,,,,,,,,,,.,/&%%##(/********///((((/*,,**/((#(###&/**,,,,,,,**,*******
// *********,,,,,,,,,,.,..,%%##(//**//******///****,,/(///((((%#,,,,,,,,,**********
// ***********,,,,,,*,,,,,//(((((/*******/((////******/(/////(#%,,,,,,,,,**********
// ****,*,,,,,,,,,,,,,,,,,//***(((//**,,,,,,*****,*****(////((#%,,,,,,*,***********
// ****,**,,,,,,*,,,,,*/#&%/**,**((///*,,,,,,,,,,,******(///((%#,,,,,,,,,**********
// ***,,,,,,,,,,,,,,*%&&&&&&(/**,,/(/********,,,***/*////*//(#&/,,,,,,,,***********
// *******,,,,,,,,(&&&&&&&&&&&%(/*/(///******,,,,,,****/((((#&#,,,,,,,,,***********
// ******,*,,,*(&&&&&&&&&@@@@@@@@%(/((/////**,,,***//((####(%&&&&*,***///*/********
// *******,/%&&&&&&&&@@@@@@@@@@@@&(//(((/////*****(####((((%&&&&&&&**/(((((////////
// *******#&&&&&&&&@@@@@@@@&&&@@@%((//(((////*****(##((##(#&&@&&&&&&/,*************
// ******#&&&&@@@@@@@@@@@&&&@&@@@%((////(((///////*/(#((##%&@@@@&&&@&&&&#**********
// *****/&&&@@@@&&@@@@&&@@@@&%&&@%(((//*///((//////((((//#&&@@@@@&&@@@@&@@@&%(*****
// ******%&@@@@@&&@@@@@@@&&%&&&@@&(///////////(((//////#&&&&@&@@&&&&@@@@@@@@@@@@%//
// *******%@&@@@@&@@@@@@&&%%&&@@@@%/////////////////((#&&&&@@&&%&&&&&&&&&&&@@@@@@@&
// *******/%&&&&&&@@&&@&%&&%&&&&@&&#**//////////////(/(&&@@@@@@@@&&&&&&&&&&&&&@@@&&
// *****(&&@&&&&&&&&&&&&&&&&&&&&&@@&%..,*////////*//,.,&&@@@@@@@@@&&&&&&&&&&&&&&&&&
// ///#&&&&@&&&&&&&&&&&&&&&&&&&&&@@&&&.     .,,..     ,%&&&@&&&@@@&&&&&&&&&&&&&&&&&
// /(&&&&&&&&&&&&&&%%&&&&&&&&&&&&&@&&&&/ ..      .....#&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// /&&&&&&&&&&&&&&%%%%%&&&&&&&&&@@@@&&@@&(.........../&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&%%%%%%%&&&&@&&&@@&&&@@&&&(........,%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&%%&&&&&&&&&&&&&&&&&&&&&&&@&&&&&&&&&&(......(&&&&&&&&&&&&&&&&&&&&&&&&&@@&@@
// @&&&&&&&%%&&%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&(....%&&&&&&&&&&&&&&&&&&&&&&&&@@@@&&
// @&&&&&&&&&&%&&%%%%%%%%%%%&&%%%%%%%%%%&&&&&&&&(..,&&&&&&&&&&&&&&&&&&&&&&&&@@@&&&@
// &&&&&&&%%%&&&&%%%%%%%%%%%&&%%%%%%%%&&&&&&&&&&&(.,&&&&&&&&&&&&&&&&&&&&&&&&@@@&&@@
// &&&&&&&&&&%&&&&&&&%%%%%&%&&&&&&&&&&&&&&&&&&&&@&(&&&&&&&&&&@@@&&&&&&&&&&&&@@@&&&&

// Average Class Enjoyer
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##########
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&&@@&&&@@&&%%%%%%%%%%%%%%%##########
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@@@@@@@&&&&&&&&&&&&&@&%%%%%%%%%############
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&@@@@@@@@@@@@&&&&&&&&&@&@&@&&&%%%##############
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&%%%&%&&%%%%%%%%##%%%&&&&&&&&&&&%###############
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&####%%%%%%%%%%######%%&&@@&&&&&&@%##############
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#(##%%%%&&&&&%%%%#####%%%&&&&&&&&&&&##############
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%&(##%%##%&&&&&&&&%%#######%%&&&&&@@&&%#############
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%((#%%&&&&@@@@&&&%%%&%%######%&&&&&@@@&#############
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&&@&#&%%&@@@@@@&@@&%%#######&&&&&&#%%#############
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%#%@@@@#%##%@@@@&&&&&%%%%######%%%#(###&#############
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%@%&@%%%###%&&&&&&%%##########&&%##&&&%#############
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%#%&%%%###%%%&@&&&&&&%%%######%&&##(#%@%#############
// %%%%%%%%%%%%%%%%%%%%%%%%%%%#/(###&%%&&%%&&&@@&%%%%&%%%%%&&%&%###################
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%(/%&%%#&&@@@@@@@@@@@%%@&&&&&%%%&&%##################
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%#%&&#%&&&&&&%&&@@@&&&@@@&&&&%%%%&##################
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&@@#*#%%%&&&&&@@&&&@@@&&&&%%%%&%#################
// %%%%%%%%%%%%%%%%%%%%%%%%%%%#%%&&&(/#%&&&&&@@@@@@&@@@@&&&&&%%&&%#################
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&%%&@@&@@@@@@@&&@@@@&&&&&&&&%##################
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#%&&%&&@@@@@@@@@&&@@@@@@@@&%#####################
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##%&&&&@@@@@@&&&&&@@@@@&%#########################
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#%%&&@@@@@&&&&&@@@@%%%%%########(################
// %%%%%%%%%%%%%%%%#%%%%%%%%%%%%%%#%%&&@@@@@@@@@@@&%%%##%%%#######(#(##%%##########
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%((#%&&&&%%%#############(####%%%%%%%%%##
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%####(//(#&&&%%%##%%%########(####%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%######(///#%&&%%%##%%%##########(#####%&&&&&&&
// %%%%%%%%%%%%%%%%%%%%%%%%%%#%%%%%#########/((((%&&%%%%%%%%#############%%%%&&&&&&
// %%%%%%%%%%%%%%%%%%%%%%%%%%#%%%%########((//(#(#%&&%%%&%%%#############%%%&&&&@@&
// %%%%%%%%%%%%%%%%%%%%%%%%#%%%#%####((((((#//(###%%&&&&&%%###%%%%%%%%%%%%%%&&&&&&&
// %%%%%%%%%%%%%%%%%%%%%##%##%%#%#(((####%%#//(((#%&&&&&%&%#%%&&&&&&&&&&&&&&&&%%%%%
// %%%%%%%%%%%%%%%%#%######%###(((###%#%%%#(////(/%&&&&%(%&&&&%%%#%%%%%%%%%&%&&%%%%
// %%%%%%%%%%%%%%%%%%#################%%%%%%%%%#(((%&&%(#%##%%%%&&&&&&&&&&&&&&&%%%%
// %%%%%%%%%%%%%%%######%%%%%%&%%#(((######%%%%%%%%#%%######%%%%&&&&%&&%%%%%%%%%%%%
// %%%%%%%%%##((#########%%%%%&%####%######%%%&&&%%%%###%%%%%&&&&&%%%%%%%%%%%%%&&&&
// %%%%%#/(((((((#####%%%%%%%###%#%%%%%%%%%%%&&&&&&&%#(#%%%%%&%%%%%%%%%%%%%%%%&&&&&
// %%#//(((((((#####%%%%%%######%%%%%%%%%%%%%%&&&&&%#(##%%%%%%%%%%%%%%%%%%%%%%%%&&&

int main() {
  int64_t n, x, y;
  std::cin >> n;
  std::vector<Point> vert;
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> x >> y;
    vert.emplace_back(Point(x, y));
  }
  Polygon polygon = Polygon(n, vert);
  std::cout << (polygon.IsConvex() ? "YES" : "NO");
}