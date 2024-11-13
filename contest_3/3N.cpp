#include <iostream>
#include <vector>

const int kInf = INT32_MAX;

struct Edge {
  int end;
  int flow;
  int capacity;
  Edge() = default;
  Edge(const int& cend, const int& cap) : end(cend), flow(0), capacity(cap) {
  }
};

class Graph {
 private:
  int vert_num_;
  std::vector<bool> used_;
  std::vector<Edge> edges_;
  std::vector<std::vector<int>> graph_;

 public:
  Graph() = default;
  explicit Graph(const int& n) {
    vert_num_ = n;
    used_.resize(n);
    graph_.resize(n);
  }

  void AddEdge(const int& u, const int& v, const int& c) {
    edges_.emplace_back(v, c);
    edges_.emplace_back(u, 0);
    graph_[u].emplace_back(edges_.size() - 2);
    graph_[v].emplace_back(edges_.size() - 1);
  }

  int DFS(const int& v, int min_delta) {
    if (used_[v]) {
      return 0;
    }
    if (v == vert_num_ - 1) {
      return min_delta;
    }
    used_[v] = true;
    for (const auto& i : graph_[v]) {
      if (!used_[edges_[i].end] && edges_[i].flow < edges_[i].capacity) {
        int delta = DFS(edges_[i].end, std::min(min_delta, edges_[i].capacity - edges_[i].flow));
        if (delta > 0) {
          edges_[i].flow += delta;
          if (i % 2 == 0) {
            edges_[i + 1].flow -= delta;
          } else {
            edges_[i - 1].flow -= delta;
          }
          return delta;
        }
      }
    }
    return 0;
  }

  int FordFulkerson() {
    int delta = kInf;
    while (delta > 0) {
      delta = DFS(0, kInf);
      used_.clear();
      used_.resize(vert_num_);
    }

    int max_flow = 0;
    for (const auto& i : graph_[0]) {
      max_flow += edges_[i].flow;
    }
    return max_flow;
  }
};

int main() {
  int n = 0;
  int m = 0;
  int u = 0;
  int v = 0;
  int capacity = 0;

  std::cin >> n >> m;
  Graph graph(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v >> capacity;
    graph.AddEdge(--u, --v, capacity);
  }

  std::cout << graph.FordFulkerson();
}