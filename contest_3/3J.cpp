#include <iostream>
#include <vector>
#include <queue>

const int kInf = INT32_MAX;

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
  int vert_num_;
  std::vector<std::vector<int>> weights_;

 public:
  Graph() = default;
  explicit Graph(const int& n) {
    weights_.resize(n, std::vector<int>(n));
    vert_num_ = n;
  }

  void AddEdge(const int& i, const int& j, const int& w) {
    weights_[i][j] = w;
  }

  std::vector<int> Dijkstra(const int& s) {
    std::vector<int> dist(vert_num_, kInf);
    auto cmp = [](const WeightAndVert& left, const WeightAndVert& right) { return left.weight > right.weight; };

    std::priority_queue<WeightAndVert, std::vector<WeightAndVert>, decltype(cmp)> heap(cmp);
    dist[s] = 0;
    heap.emplace(0, s);
    while (!heap.empty()) {
      int w = heap.top().weight;
      int v = heap.top().vert;
      heap.pop();
      if (w > dist[v]) {
        continue;
      }
      for (int j = 0; j < vert_num_; ++j) {
        if (v != j && weights_[v][j] != -1) {
          if (dist[v] + weights_[v][j] < dist[j]) {
            dist[j] = dist[v] + weights_[v][j];
            heap.emplace(dist[j], j);
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
  int s = 0;
  int t = 0;
  int w = 0;

  std::cin >> n >> s >> t;
  --s;
  --t;
  Graph graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> w;
      graph.AddEdge(i, j, w);
    }
  }
  int dist = graph.Dijkstra(s)[t];
  if (dist != kInf) {
    std::cout << dist;
  } else {
    std::cout << -1;
  }
}