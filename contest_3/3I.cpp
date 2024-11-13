#include <iostream>
#include <vector>
#include <queue>

const int kInf = 2009000999;

struct WeightAndVert {
  int weight;
  int vert;
  WeightAndVert() = default;
  explicit WeightAndVert(const int& cweight, const int& cvert) {
    weight = cweight;
    vert = cvert;
  }
};

struct Edge {
  int start, end, weight;
  Edge() = default;
  explicit Edge(const int& cstart, const int& cend, const int& cweight) : start(cstart), end(cend), weight(cweight){};
};

class Graph {
 private:
  std::vector<std::vector<Edge>> edges_;
  int verts_num_;

 public:
  Graph() = default;
  explicit Graph(const int& n) : edges_(std::vector<std::vector<Edge>>(n)), verts_num_(n){};

  void AddEdge(const Edge& edge) {
    edges_[edge.start].emplace_back(edge);
    edges_[edge.end].emplace_back(edge.end, edge.start, edge.weight);
  }

  std::vector<int> Dijkstra(int start) {
    std::vector<int> dist(verts_num_, kInf);
    dist[start] = 0;

    auto cmp = [](const WeightAndVert& left, const WeightAndVert& right) { return left.weight > right.weight; };

    std::priority_queue<WeightAndVert, std::vector<WeightAndVert>, decltype(cmp)> heap(cmp);
    heap.emplace(0, start);

    while (!heap.empty()) {
      int v = heap.top().vert;
      int cur_dist = heap.top().weight;
      heap.pop();

      if (cur_dist > dist[v]) {
        continue;
      }

      for (auto edge : edges_[v]) {
        if (dist[v] + edge.weight < dist[edge.end]) {
          dist[edge.end] = dist[v] + edge.weight;
          heap.emplace(dist[edge.end], edge.end);
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
  int k = 0;
  std::vector<std::vector<int>> ans;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    std::cin >> n >> m;
    Graph graph = Graph(n);

    for (int i = 0; i < m; ++i) {
      std::cin >> v >> u >> w;
      graph.AddEdge(Edge(v, u, w));
    }
    std::cin >> n;
    ans.emplace_back(graph.Dijkstra(n));
  }

  for (auto i : ans) {
    for (auto j : i) {
      std::cout << j << ' ';
    }
    std::cout << '\n';
  }
}
