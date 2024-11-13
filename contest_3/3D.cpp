#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Edge {
  int start, end, weight;
  Edge() = default;
  explicit Edge(const int& cstart, const int& cend, const int& cweight) : start(cstart), end(cend), weight(cweight){};
};

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

class Graph {
 private:
  std::vector<Edge> edges_;

 public:
  Graph() = default;

  void AddEdge(const Edge& edge) {
    edges_.emplace_back(edge);
  }

  int Kruskal() {
    int mst_weight = 0;
    std::sort(edges_.begin(), edges_.end(), [](const Edge& a, const Edge& b) { return a.weight < b.weight; });
    DSU dsu = DSU(static_cast<int>(edges_.size()));
    for (auto edge : edges_) {
      if (dsu.Find(edge.start) != dsu.Find(edge.end)) {
        dsu.Union(edge.start, edge.end);
        mst_weight += edge.weight;
      }
    }
    return mst_weight;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  int v = 0;
  int u = 0;
  int w = 0;
  std::cin >> n >> m;
  Graph graph = Graph();

  for (int i = 0; i < m; ++i) {
    std::cin >> v >> u >> w;
    graph.AddEdge(Edge(--v, --u, w));
  }
  std::cout << graph.Kruskal();
}
