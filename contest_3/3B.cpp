#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int> parent_;
  std::vector<int> rank_;

 public:
  std::vector<int> weights;
  DSU() = default;
  explicit DSU(const int& n) {
    for (int i = 0; i < n; ++i) {
      parent_.emplace_back(i);
    }
    weights.resize(n, 0);
    rank_.resize(n, 0);
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
      if (rank_[x_parent] > rank_[y_parent]) {
        weights[x_parent] += weights[y_parent];
        parent_[y_parent] = x_parent;
        rank_[x_parent] += rank_[y_parent];
      } else {
        weights[y_parent] += weights[x_parent];
        parent_[x_parent] = y_parent;
        rank_[y_parent] += rank_[x_parent];
      }
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  int u = 0;
  int v = 0;
  int w = 0;
  int cmd = 0;
  std::cin >> n >> m;
  DSU dsu = DSU(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> cmd;
    if (cmd == 1) {
      std::cin >> u >> v >> w;
      dsu.Union(--u, --v);
      dsu.weights[dsu.Find(u)] += w;
    }
    if (cmd == 2) {
      std::cin >> u;
      std::cout << dsu.weights[dsu.Find(--u)] << '\n';
    }
  }
}