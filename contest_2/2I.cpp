#include <iostream>
#include <vector>
#include <queue>
#include <vector>

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
  void AddEdge(const int&, const int&);
  void DFS(int, std::vector<bool>&, std::vector<int>&);
};

void Graph::AddEdge(const int& first, const int& second) {
  graph_[first].emplace_back(second);
  graph_[second].emplace_back(first);
}

void Graph::DFS(int v, std::vector<bool>& visited, std::vector<int>& group) {
  visited[v] = true;
  group.emplace_back(v);

  for (int u : graph_[v]) {
    if (!visited[u]) {
      DFS(u, visited, group);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph = Graph(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    graph.AddEdge(v, u);
  }

  std::vector<bool> visited(n + 1, false);
  std::vector<std::vector<int>> groups;

  for (int i = 1; i <= n; i++) {
    if (!visited[i]) {
      std::vector<int> group;
      graph.DFS(i, visited, group);
      groups.push_back(group);
    }
  }

  std::cout << groups.size() << '\n';
  for (const auto& group : groups) {
    std::cout << group.size() << '\n';
    for (int student : group) {
      std::cout << student << " ";
    }
    std::cout << '\n';
  }
}