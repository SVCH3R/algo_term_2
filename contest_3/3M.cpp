#include <iostream>
#include <vector>
#include <queue>

class Graph {
  std::vector<std::vector<int>> weights_;
  int vert_num_;

 public:
  Graph() = default;
  explicit Graph(const int& n) {
    vert_num_ = n;
    weights_.resize(n, std::vector<int>(n));
  }

  void AddEdge(const int& i, const int& j, const int& w) {
    weights_[i][j] = w;
  }
  std::vector<std::vector<int>> FloydWarshall() {
    for (int k = 0; k < vert_num_; ++k) {
      for (int x = 0; x < vert_num_; ++x) {
        for (int y = 0; y < vert_num_; ++y) {
          weights_[x][y] = std::min(weights_[x][y], weights_[x][k] + weights_[k][y]);
        }
      }
    }
    return weights_;
  }
};

int main() {
  int n = 0;
  int w = 0;
  std::cin >> n;
  Graph graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> w;
      graph.AddEdge(i, j, w);
    }
  }
  std::vector<std::vector<int>> ans = graph.FloydWarshall();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << ans[i][j] << ' ';
    }
    std::cout << '\n';
  }
}