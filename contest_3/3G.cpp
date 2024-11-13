#include <iostream>
#include <vector>
#include <queue>

const int kInf = 30000;

struct Edge {
  int start, end, weight;
  Edge() = default;
  explicit Edge(const int& cstart, const int& cend, const int& cweight) : start(cstart), end(cend), weight(cweight){};
};

class Graph {
 private:
  std::vector<Edge> edges_;
  int verts_num_;

 public:
  Graph() = default;
  explicit Graph(const int& n) : verts_num_(n){};

  void AddEdge(const Edge& edge) {
    edges_.emplace_back(edge);
  }

  std::vector<int> BellmanFord(const int& s) {
    std::vector<int> dist(verts_num_, kInf);
    dist[s] = 0;
    for (int i = 0; i < verts_num_ - 1; ++i) {
      for (auto edge : edges_) {
        if (dist[edge.start] != kInf && dist[edge.start] + edge.weight < dist[edge.end]) {
          dist[edge.end] = dist[edge.start] + edge.weight;
        }
      }
    }
    return dist;
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
  Graph graph = Graph(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> v >> u >> w;
    graph.AddEdge(Edge(--v, --u, w));
  }
  for (auto i : graph.BellmanFord(0)) {
    std::cout << i << ' ';
  }
}
