#include <iostream>
#include <queue>
#include <vector>

enum Colors { WHITE, GRAY, BLACK };

class Graph {
 private:
  std::vector<std::vector<int>> graph_;

 public:
  explicit Graph() : graph_(std::vector<std::vector<int>>()) {
  }
  explicit Graph(const std::vector<std::vector<int>>& graph) : graph_(graph) {
  }
  explicit Graph(const int& v) : graph_(std::vector<std::vector<int>>(v)) {
  }
  bool IsBiparite();
  void AddEdge(const int&, const int&);
};

void Graph::AddEdge(const int& first, const int& second) {
  graph_[first].emplace_back(second);
  graph_[second].emplace_back(first);
}

bool Graph::IsBiparite() {
  std::vector<Colors> colors(graph_.size(), WHITE);
  std::queue<int8_t> q;
  for (size_t i = 0; i < graph_.size(); i++) {
    if (colors[i] == WHITE) {
      colors[i] = GRAY;
      q.push(i);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph_[u]) {
          if (colors[v] == WHITE) {
            colors[v] = colors[u] == GRAY ? BLACK : GRAY;
            q.push(v);
          } else {
            if (colors[v] == colors[u]) {
              return false;
            }
          }
        }
      }
    }
  }
  return true;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    std::cin >> a >> b;
    graph.AddEdge(a - 1, b - 1);
  }
  std::cout << (graph.IsBiparite() ? "YES" : "NO");
}
