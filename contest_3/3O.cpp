#include <iostream>
#include <vector>
#include <queue>

const int kInf = INT32_MAX;

class Graph {
 private:
  int verts_num_;
  std::vector<std::vector<int>> capacity_;
  std::vector<std::vector<int>> flow_;
  std::vector<std::vector<int>> adjlist_;

  bool BFS(std::vector<int>& parent) {
    std::queue<int> queue;
    parent[0] = 0;
    queue.push(0);

    while (!queue.empty()) {
      int cur = queue.front();
      queue.pop();

      for (const auto& next : adjlist_[cur]) {
        if (parent[next] == -1 && capacity_[cur][next] > flow_[cur][next]) {
          parent[next] = cur;
          queue.push(next);
        }
      }
    }

    return parent[verts_num_ - 1] != -1;
  }

 public:
  Graph() = default;
  explicit Graph(const int& vertices) {
    verts_num_ = vertices;
    capacity_.assign(verts_num_, std::vector<int>(verts_num_, 0));
    flow_.assign(verts_num_, std::vector<int>(verts_num_, 0));
    adjlist_.resize(verts_num_);
  }

  void AddEdge(const int& start, const int& end, const int& cap) {
    capacity_[start][end] += cap;
    adjlist_[start].push_back(end);
    adjlist_[end].push_back(start);
  }

  int EdmondsKarp() {
    int max_flow = 0;

    while (true) {
      std::vector<int> parent(verts_num_, -1);
      if (!BFS(parent)) {
        break;
      }

      int delta = kInf;
      for (int cur = verts_num_ - 1; cur != 0; cur = parent[cur]) {
        int prev = parent[cur];
        delta = std::min(delta, capacity_[prev][cur] - flow_[prev][cur]);
      }

      for (int cur = verts_num_ - 1; cur != 0; cur = parent[cur]) {
        int prev = parent[cur];
        flow_[prev][cur] += delta;
        flow_[cur][prev] -= delta;
      }

      max_flow += delta;
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

  std::cout << graph.EdmondsKarp();
}
