#include <iostream>
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
  int ComponentsNumber();
  void DFS(const int&, std::vector<bool>&);
};

void Graph::DFS(const int& vertex, std::vector<bool>& visited) {
  visited[vertex] = true;
  for (int i : graph_[vertex]) {
    if (!visited[i]) {
      DFS(i, visited);
    }
  }
}

void Graph::AddEdge(const int& first, const int& second) {
  graph_[first].emplace_back(second);
  graph_[second].emplace_back(first);
}

int Graph::ComponentsNumber() {
  int components = 0;
  std::vector<bool> visited(graph_.size(), false);
  for (size_t i = 0; i < graph_.size(); ++i) {
    if (!visited[i]) {
      DFS(i, visited);
      ++components;
    }
  }
  return components;
}

int main() {
  int input;
  std::cin >> input;
  int vertices = input;
  Graph graph = Graph(vertices);
  for (int i = 0; i < vertices; ++i) {
    std::cin >> input;
    graph.AddEdge(input - 1, i);
  }
  std::cout << graph.ComponentsNumber();
}
