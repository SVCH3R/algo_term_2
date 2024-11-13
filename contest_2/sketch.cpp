#include <iostream>
#include <vector>
#include <algorithm>

enum Colors { WHITE, GRAY, BLACK };

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

  bool TopSortDFS(const int&, std::vector<Colors>&, std::vector<int>&);
  std::vector<int> TopSort();
  void SCC();
  void DFS();
};


void Graph::SCC() {
  std::vector<int> order = TopSort();
  std::vector<int> components = DFS()

}


bool Graph::TopSortDFS(const int& v, std::vector<Colors>& colors, std::vector<int>& top_sorted) {
  colors[v] = GRAY;
  for (auto u : graph_[v]) {
    if (colors[u] == GRAY) {
      return false;
    }
    if (colors[u] == WHITE) {
      if (!TopSortDFS(u, colors, top_sorted)) {
        return false;
      }
    }
  }
  colors[v] = BLACK;
  top_sorted.emplace_back(v);
  return true;
}

std::vector<int> Graph::TopSort() {
  std::vector<Colors> colors(graph_.size(), WHITE);
  std::vector<int> top_sorted;
  for (size_t v = 0; v < graph_.size(); ++v) {
    if (colors[v] == WHITE) {
      if (!TopSortDFS(v, colors, top_sorted)) {
        //return {-1};
      }
    }
  }
  reverse(top_sorted.begin(), top_sorted.end());
  return top_sorted;
}

void Graph::AddEdge(const int& first, const int& second) {
  graph_[first].emplace_back(second);
}

int main() {
  int vertices, edges, input1, input2;
  std::cin >> vertices >> edges;
  Graph graph = Graph(vertices);
  for (int i = 0; i < edges; ++i) {
    std::cin >> input1 >> input2;
    graph.AddEdge(input1 - 1, input2 - 1);
  }
  std::vector<int> ans = graph.TopSort();
  if (ans[0] == -1) {
    std::cout << -1;
  } else {
    for (auto i : ans) {
      std::cout << i + 1 << ' ';
    }
  }
}
