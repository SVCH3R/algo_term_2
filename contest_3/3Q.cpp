#include <iostream>
#include <vector>
#include <queue>

const int kInf = INT32_MAX;

class Graph {
 private:
  int vert_num_;
  std::vector<std::vector<int>> capacity_;
  std::vector<std::vector<int>> flow_;

 public:
  Graph() = default;
  explicit Graph(const int& n) {
    vert_num_ = n;
    capacity_.resize(n, std::vector<int>(n));
    flow_.resize(n, std::vector<int>(n));
  }

  void AddEdge(const int& u, const int& v, const int& c) {
    capacity_[u][v] = c;
  }

  std::vector<int> BFS() {
    std::vector<int> dist(vert_num_, kInf);
    std::queue<int> queue;
    dist[0] = 0;
    queue.push(0);
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      for (int i = 0; i < vert_num_; ++i) {
        if (dist[i] == kInf && flow_[v][i] < capacity_[v][i]) {
          dist[i] = dist[v] + 1;
          queue.push(i);
        }
      }
    }
    return dist;
  }

  int DFS(const int& v, const std::vector<int>& dist, int min_delta) {
    if (min_delta == 0 || v == vert_num_ - 1) {
      return min_delta;
    }
    for (int i = 0; i < vert_num_; ++i) {
      if (dist[i] == dist[v] + 1) {
        int delta = DFS(i, dist, std::min(min_delta, capacity_[v][i] - flow_[v][i]));
        if (delta > 0) {
          flow_[i][v] -= delta;
          flow_[v][i] += delta;
          return delta;
        }
      }
    }
    return 0;
  }

  int Dinic() {
    int delta = 0;
    auto dist = BFS();
    while (dist[vert_num_ - 1] != kInf) {
      delta = DFS(0, dist, kInf);
      while (delta > 0) {
        delta = DFS(0, dist, kInf);
      }
      dist = BFS();
    }
    int max_flow = 0;
    for (int i = 0; i < vert_num_; ++i) {
      max_flow += flow_[0][i];
    }
    return max_flow;
  }
};

int main() {
  int n = 0;
  int m = 0;
  int u = 0;
  int v = 0;
  int c = 0;
  std::cin >> n >> m;
  Graph graph(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v >> c;
    graph.AddEdge(--u, --v, c);
  }

  std::cout << graph.Dinic();
}