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

void Print(const std::vector<int>& v) {
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] + 1 << ' ';
  }
}

class Graph {
 private:
  std::vector<std::vector<int>> graph_;

 public:
  explicit Graph() : graph_(std::vector<std::vector<int>>()) {
  }
  explicit Graph(const std::vector<std::vector<int>>& graph) : graph_(graph) {
  }
  explicit Graph(const int& v) : graph_(std::vector<std::vector<int>>(v)) {
  }
  DistAndPath BFS(const int& start, const int& end, const int& v);
  void AddEdge(const int&, const int&);
};

DistAndPath Graph::BFS(const int& start, const int& end, const int& v) {
  std::vector<int> dist = std::vector<int>(v, kInf);
  std::vector<int> parent = std::vector<int>(v, -1);
  std::queue<int> q;
  q.push(start);
  dist[start] = 0;
  while (not q.empty()) {
    int v = q.front();
    q.pop();
    for (auto u : graph_[v]) {
      if (dist[u] == kInf) {
        dist[u] = dist[v] + 1;
        parent[u] = v;
        q.push(u);
      }
    }
  }
  std::vector<int> path;
  int cur = end;
  path.push_back(cur);
  while (parent[cur] != -1) {
    cur = parent[cur];
    path.push_back(cur);
  }
  reverse(path.begin(), path.end());
  return DistAndPath(dist, path);
}

void Graph::AddEdge(const int& first, const int& second) {
  graph_[first].emplace_back(second);
  graph_[second].emplace_back(first);
}

int main() {
  int v, e;
  std::cin >> v >> e;
  Graph graph = Graph(v);
  int start, end, input1, input2;
  std::cin >> start >> end;
  --start;
  --end;
  for (int i = 0; i < e; ++i) {
    std::cin >> input1;
    std::cin >> input2;
    --input1;
    --input2;
    graph.AddEdge(input1, input2);
  }
  DistAndPath ans = graph.BFS(start, end, v);

  std::cout << ((ans.dist[end] == kInf) ? -1 : ans.dist[end]) << '\n';
  if (ans.dist[end] != kInf) {
    Print(ans.path);
  }
}