#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
  int components_;

 public:
  DSU() = default;
  explicit DSU(const int& n) {
    for (int i = 0; i < n; ++i) {
      parent_.emplace_back(i);
    }
    rank_.resize(n, 0);
    components_ = n;
  };

  int Find(const int& x) {
    if (parent_[x] == x) {
      return x;
    }
    parent_[x] = Find(parent_[x]);
    return parent_[x];
  }

  void Union(int x, int y) {
    int x_parent = Find(x);
    int y_parent = Find(y);

    if (x_parent != y_parent) {
      --components_;
      if (rank_[x_parent] > rank_[y_parent]) {
        parent_[y_parent] = x_parent;
        rank_[x_parent] += rank_[y_parent];
      } else {
        parent_[x_parent] = y_parent;
        rank_[y_parent] += rank_[x_parent];
      }
    }
  }
  bool Linked() {
    return components_ == 1;
  }
};

int main() {
  int n = 0;
  int m = 0;
  int u = 0;
  int v = 0;
  std::cin >> n >> m;
  DSU dsu = DSU(n);
  int count = 0;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;
    if (!dsu.Linked()) {
      dsu.Union(u, v);
      ++count;
    }
  }
  std::cout << count;
}