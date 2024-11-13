#include <iostream>
#include <vector>
#include <queue>

struct Edge {
  int end, weight;
  Edge(const int& cend, const int& cweight) : end(cend), weight(cweight){};
};

struct WeightAndVert {
  int weight;
  int vert;
  WeightAndVert() = default;
  explicit WeightAndVert(const int& cweight, const int& cvert) {
    weight = cweight;
    vert = cvert;
  }
};

class Graph {
 private:
  std::vector<std::vector<Edge>> graph_;

 public:
  Graph() = default;
  explicit Graph(const int& n) : graph_(std::vector<std::vector<Edge>>(n)){};

  void AddEdge(const int& v, const Edge& edge) {
    graph_[v].emplace_back(edge);
    graph_[edge.end].emplace_back(v, edge.weight);
  }

  int Prim() {
    auto cmp = [](const WeightAndVert& left, const WeightAndVert& right) { return left.weight > right.weight; };

    std::priority_queue<WeightAndVert, std::vector<WeightAndVert>, decltype(cmp)> heap(cmp);
    std::vector<bool> visited(graph_.size() + 1, false);
    heap.emplace(0, 1);
    int mstweight = 0;

    while (!heap.empty()) {
      int weight = heap.top().weight;
      int vertex = heap.top().vert;
      heap.pop();

      if (visited[vertex]) {
        continue;
      }

      visited[vertex] = true;
      mstweight += weight;

      for (const Edge& edge : graph_[vertex]) {
        if (!visited[edge.end]) {
          heap.emplace(edge.weight, edge.end);
        }
      }
    }
    return mstweight;
  }
};

int main() {
  int n = 0;
  int m = 0;
  int v = 0;
  int u = 0;
  int w = 0;
  std::cin >> n >> m;
  Graph graph = Graph(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> v >> u >> w;
    graph.AddEdge(--v, Edge(--u, w));
  }
  std::cout << graph.Prim();
}
