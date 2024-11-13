#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int kInf = 2147483647;

struct DistAndPath {
  std::vector<int> dist;
  std::vector<int> path;
  DistAndPath(const std::vector<int>& constr_dist, const std::vector<int>& constr_path)
      : dist(constr_dist), path(constr_path) {
  }
};

class Graph {
 private:
  std::vector<int> graph_;

 public:
  explicit Graph() : graph_() {
  }
  explicit Graph(const int& v) : graph_(std::vector<int>(v, kInf)) {
  }
  DistAndPath BFS(const int& start, const int& end, const int& v);
  void AddEdge(const int&, const int&);
  void FindSub(const int& n, const int& m);
  std::vector<int> Data();
};

std::vector<int> Graph::Data() {
  return graph_;
}

void Graph::AddEdge(const int& first, const int& second) {
  graph_[first] = second;
}

void Graph::FindSub(const int& n, const int& m) {
  std::queue<int> q;
  int size = n * m;
  for (int i = 0; i < size; ++i) {
    if (!graph_[i]) {
      q.emplace(i);
    }
  }

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    int i = v / m;
    int j = v % m;

    if (j != m - 1 && graph_[v + 1] > graph_[v] + 1) {
      graph_[v + 1] = graph_[v] + 1;
      q.emplace(v + 1);
    }
    if (j != 0 && graph_[v - 1] > graph_[v] + 1) {
      graph_[v - 1] = graph_[v] + 1;
      q.emplace(v - 1);
    }
    if (i != 0 && graph_[v - m] > graph_[v] + 1) {
      graph_[v - m] = graph_[v] + 1;
      q.emplace(v - m);
    }
    if (i != n - 1 && graph_[v + m] > graph_[v] + 1) {
      graph_[v + m] = graph_[v] + 1;
      q.emplace(v + m);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n * m);
  for (int i = 0; i < n * m; ++i) {
    bool intput;
    std::cin >> intput;
    if (intput) {
      graph.AddEdge(i, 0);
    }
  }
  graph.FindSub(n, m);
  std::vector<int> data = graph.Data();
  int k = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << data[k] << ' ';
      ++k;
    }
    std::cout << '\n';
  }
}
