#include <iostream>
#include <vector>
#include <algorithm>

enum Colors { WHITE = 0, GRAY = 1, BLACK = 2 };

class Graph {
 private:
  std::vector<std::vector<int>> graph_;
  std::vector<std::vector<int>> transposed_;
  std::vector<Colors> colors_;
  std::vector<int> topsorted_;
  std::vector<int> comps_;

 public:
  Graph() = default;

  explicit Graph(const int& n) {
    graph_.resize(n);
    transposed_.resize(n);
    colors_.resize(n, WHITE);
    comps_.resize(n, -1);
  }

  void AddEdge(const int& first, const int& second) {
    graph_[first].emplace_back(second);
    transposed_[second].emplace_back(first);
  }

  void TopSortDFS(const int& v) {
    colors_[v] = GRAY;
    for (auto u : graph_[v]) {
      if (colors_[u] == WHITE) {
        TopSortDFS(u);
      }
    }
    colors_[v] = BLACK;
    topsorted_.emplace_back(v);
  }

  std::vector<int> TopSort() {
    for (size_t i = 0; i < graph_.size(); ++i) {
      if (colors_[i] == WHITE) {
        TopSortDFS(i);
      }
    }
    colors_.clear();
    colors_.resize(graph_.size(), WHITE);
    std::reverse(topsorted_.begin(), topsorted_.end());
    return topsorted_;
  }

  void DFS(const int& v, int& count) {
    colors_[v] = GRAY;
    comps_[v] = count;
    for (const auto& u : transposed_[v]) {
      if (colors_[u] == WHITE) {
        DFS(u, count);
      }
    }
    colors_[v] = BLACK;
  }

  int CountComps(const std::vector<int>& order) {
    int count = 0;
    for (const auto& v : order) {
      if (colors_[v] == WHITE) {
        DFS(v, count);
        ++count;
      }
    }
    return count;
  }

  std::vector<int> GetComps() {
    return comps_;
  }
};

int main() {
  int n, m, u, v;
  std::cin >> n >> m;
  Graph graph = Graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;
    graph.AddEdge(--u, --v);
  }

  std::vector<int> order = graph.TopSort();
  std::cout << graph.CountComps(order) << '\n';
  for (const auto& comp : graph.GetComps()) {
    std::cout << comp + 1 << " ";
  }
}
