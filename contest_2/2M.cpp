#include <iostream>
#include <vector>
#include <set>

enum Colors { WHITE = 0, GRAY = 1, BLACK = 2 };

class Graph {
 private:
  std::vector<std::vector<int>> graph_;
  std::vector<Colors> colors_;
  std::set<int> artpoints_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;

 public:
  Graph() = default;
  explicit Graph(const int& n) {
    graph_.resize(n);
    time_in_.resize(n, 0);
    time_up_.resize(n, 0);
    colors_.resize(n, WHITE);
  }

  void AddEdge(const int& u, const int& v) {
    graph_[u].emplace_back(v);
    graph_[v].emplace_back(u);
  }

  void DFS(const int& v, int& time, int p) {
    colors_[v] = GRAY;
    time_in_[v] = time_up_[v] = time++;
    int childcount = 0;
    for (const auto& u : graph_[v]) {
      if (colors_[u] == GRAY) {
        time_up_[v] = std::min(time_up_[v], time_in_[u]);
      }
      if (colors_[u] == WHITE) {
        DFS(u, time, v);
        ++childcount;
        time_up_[v] = std::min(time_up_[v], time_up_[u]);
        if (p != -1 && time_in_[v] <= time_up_[u]) {
          artpoints_.insert(v);
        }
      }
    }
    if (p == -1 && childcount > 1) {
      artpoints_.insert(v);
    }
    colors_[v] = BLACK;
  }

  std::set<int> ArtPoints() {
    int time = 0;
    for (size_t i = 0; i < graph_.size(); ++i) {
      if (colors_[i] == WHITE) {
        DFS(i, time, -1);
      }
    }
    return artpoints_;
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
  std::set<int> artpoints = graph.ArtPoints();
  std::cout << artpoints.size() << '\n';
  for (const auto& points : artpoints) {
    std::cout << points + 1 << '\n';
  }
}