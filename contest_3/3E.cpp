#include <iostream>
#include <vector>
#include <queue>

struct Edge {
  int64_t start, end, weight;
  Edge() = default;
  explicit Edge(const int64_t& cstart, const int64_t& cend, const int64_t& cweight)
      : start(cstart), end(cend), weight(cweight){};
};

class DSU {
 private:
  std::vector<int64_t> parent_;
  std::vector<int64_t> rank_;
  int64_t setcount_;

 public:
  std::vector<int64_t> weights;
  DSU() = default;
  explicit DSU(const int64_t& n) {
    for (int64_t i = 0; i < n; ++i) {
      parent_.emplace_back(i);
    }
    weights.resize(n, 0);
    rank_.resize(n, 0);
    setcount_ = n;
  };

  int64_t Find(const int64_t& x) {
    if (parent_[x] == x) {
      return x;
    }
    parent_[x] = Find(parent_[x]);
    return parent_[x];
  }

  void Union(int64_t x, int64_t y) {
    int64_t x_parent = Find(x);
    int64_t y_parent = Find(y);

    if (x_parent != y_parent) {
      --setcount_;
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

  int64_t SetCount() {
    return setcount_;
  }
};

class Graph {
 private:
  std::vector<Edge> edges_;
  int64_t size_;

 public:
  Graph() = default;
  explicit Graph(const int64_t& n) : size_(n){};

  void AddEdge(const Edge& edge) {
    edges_.emplace_back(edge);
  }

  int64_t Boruvka() {
    DSU dsu(size_);
    int64_t mst_weight = 0;
    while (dsu.SetCount() > 1) {
      std::vector<Edge> min_edges(size_);

      for (const Edge& edge : edges_) {
        int64_t comp_u = dsu.Find(edge.start);
        int64_t comp_v = dsu.Find(edge.end);

        if (comp_u != comp_v) {
          if (edge.weight < min_edges[comp_u].weight || min_edges[comp_u].weight == 0) {
            min_edges[comp_u] = edge;
          }
          if (edge.weight < min_edges[comp_v].weight || min_edges[comp_v].weight == 0) {
            min_edges[comp_v] = edge;
          }
        }
      }
      for (const Edge& min_edge : min_edges) {
        if (min_edge.weight != 0) {
          int64_t comp_u = dsu.Find(min_edge.start);
          int64_t comp_v = dsu.Find(min_edge.end);

          if (comp_u != comp_v) {
            dsu.Union(comp_u, comp_v);
            mst_weight += min_edge.weight;
          }
        }
      }
    }
    return mst_weight;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  int64_t v = 0;
  int64_t u = 0;
  int64_t w = 0;
  std::cin >> n >> m;
  Graph graph = Graph(n);

  for (int64_t i = 0; i < m; ++i) {
    std::cin >> v >> u >> w;
    graph.AddEdge(Edge(--v, --u, w));
  }
  std::cout << graph.Boruvka();
}
