#include <iostream>
#include <vector>
#include <algorithm>

enum Colors { WHITE = 0, GRAY = 1, BLACK = 2 };

struct Edge {
  Edge() = default;
  Edge(const int& cstart, const int& cend) {
    start = cstart;
    end = cend;
  }
  int start;
  int end;
};

class Graph {
 private:
  std::vector<std::vector<Edge>> edges_;
  std::vector<Colors> colors_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;
  std::vector<int> bridges_;

 public:
  explicit Graph(const int& n) {
    edges_.resize(n);
    time_in_.resize(n, 0);
    time_up_.resize(n, 0);
    colors_.resize(n, WHITE);
  }

  void AddEdge(const int& i, const Edge& edge) {
    edges_[i].emplace_back(edge);
  }

  bool IsMultiple(const int& v, const int& u) {
    int count = 0;
    for (const auto& i : edges_[v]) {
      if (i.start == u) {
        count++;
      }
    }
    return count != 1;
  }

  void DFS(const int& v, int& time, int p = -1) {
    colors_[v] = GRAY;
    time_in_[v] = time++;
    time_up_[v] = time;
    for (const auto& u : edges_[v]) {
      if (p != u.start) {
        if (colors_[u.start] == GRAY) {
          time_up_[v] = std::min(time_up_[v], time_in_[u.start]);
        }
        if (colors_[u.start] == WHITE) {
          DFS(u.start, time, v);
          time_up_[v] = std::min(time_up_[v], time_up_[u.start]);
          if (time_in_[v] < time_up_[u.start]) {
            if (!IsMultiple(v, u.start)) {
              bridges_.emplace_back(u.end);
            }
          }
        }
      }
    }
    colors_[v] = BLACK;
  }

  std::vector<int> FindBridges() {
    int time = 0;
    for (size_t i = 0; i < edges_.size(); ++i) {
      if (colors_[i] == WHITE) {
        DFS(i, time);
      }
    }
    return bridges_;
  }
};

int main() {
  int n, m, u, v;
  std::cin >> n >> m;
  Graph graph = Graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;
    graph.AddEdge(--u, Edge(--v, i + 1));
    graph.AddEdge(v, Edge(u, i + 1));
  }
  std::vector<int> bridges = graph.FindBridges();
  std::sort(bridges.begin(), bridges.end());
  std::cout << bridges.size() << '\n';
  for (const auto& bridge : bridges) {
    std::cout << bridge << '\n';
  }
}