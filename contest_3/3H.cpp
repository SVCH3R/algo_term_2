#include <iostream>
#include <vector>
#include <queue>

const int kInf = INT32_MAX;

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

  void AddEdge(const int& start, const int& end, const int& weight) {
    edges_.emplace_back(start, end, weight);
  }

  std::vector<std::vector<int>> BellmanFord(const int& s, const int& k) {
    std::vector<std::vector<int>> dist(k + 1, std::vector<int>(verts_num_, INT32_MAX));
    dist[0][s] = 0;
    for (int i = 0; i < k; ++i) {
      for (int j = 0; j < verts_num_ - 1; ++j) {
        for (const auto& edge : edges_) {
          if (dist[i][edge.start] < INT32_MAX) {
            dist[i + 1][edge.end] = std::min(dist[i + 1][edge.end], dist[i][edge.start] + edge.weight);
          }
        }
      }
    }
    return dist;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  int k = 0;
  int s = 0;
  int f = 0;
  std::cin >> n >> m >> k >> s >> f;
  --s;
  --f;
  std::vector<std::vector<int>> minweights(n, std::vector<int>(n, kInf));
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int w = 0;
    std::cin >> u >> v >> w;
    --u;
    --v;
    if (w < minweights[u][v]) {
      minweights[u][v] = w;
    }
  }
  Graph graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (minweights[i][j] < kInf) {
        graph.AddEdge(i, j, minweights[i][j]);
      }
    }
  }
  auto dist = graph.BellmanFord(s, k);
  int mincost = kInf;
  for (int i = 0; i < k + 1; ++i) {
    if (mincost > dist[i][f]) {
      mincost = dist[i][f];
    }
  }
  if (mincost == kInf) {
    std::cout << -1;
  } else {
    std::cout << mincost;
  }
}