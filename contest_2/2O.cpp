#include <iostream>
#include <vector>

enum Colors { WHITE = 0, GRAY = 1, BLACK = 2 };

class Graph {
 private:
  std::vector<std::vector<int>> graph_;
  std::vector<Colors> colors_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;
  std::vector<bool> is_ap_;

 public:
  Graph() = default;
  Graph(const int& n, const int& m) {
    graph_.resize(n + m);
    colors_.resize(n + m, WHITE);
    time_in_.resize(n + m, 0);
    time_up_.resize(n + m, 0);
    is_ap_.resize(n + m, false);
  }
  void DFS(const int& v, int& time, int p = -1) {
    colors_[v] = GRAY;
    time_in_[v] = time_up_[v] = time++;
    int childcount = 0;
    for (const auto& u : graph_[v]) {
      if (colors_[u] == GRAY) {
        time_up_[v] = std::min(time_up_[v], time_in_[u]);
      }
      if (colors_[u] == WHITE) {
        ++childcount;
        DFS(u, time, v);
        time_up_[v] = std::min(time_up_[v], time_up_[u]);
        if (p != -1 && time_in_[v] <= time_up_[u]) {
          is_ap_[v] = true;
        }
      }
    }
    if (p == -1 && childcount > 1) {
      is_ap_[v] = true;
    }
    colors_[v] = BLACK;
  }

  void ArtPoints() {
    int time = 0;
    for (size_t i = 0; i < graph_.size(); ++i) {
      if (colors_[i] == WHITE) {
        DFS(i, time);
      }
    }
  }
  bool IsArt(const int& v) {
    return is_ap_[v];
  }
  void AddEdge(const int& u, const int& v) {
    graph_[u].emplace_back(v);
    graph_[v].emplace_back(u);
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph(n, m);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;
    graph.AddEdge(n + i, --a);
    graph.AddEdge(n + i, --b);
    graph.AddEdge(n + i, --c);
  }
  graph.ArtPoints();
  std::vector<int> articulation_points;
  for (int i = n; i < n + m; ++i) {
    if (graph.IsArt(i)) {
      articulation_points.emplace_back(i - n + 1);
    }
  }
  std::cout << articulation_points.size() << '\n';
  for (const auto& point : articulation_points) {
    std::cout << point << '\n';
  }
}