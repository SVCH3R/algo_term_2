#include <algorithm>
#include <iostream>
#include <vector>

enum Colors { WHITE = 0, GRAY = 1, BLACK = 2 };

class Graph {
 public:
  Graph() = default;
  explicit Graph(const int& n) {
    graph.resize(n);
    colors.resize(n, WHITE);
  }
  std::vector<std::vector<int>> graph;
  std::vector<Colors> colors;
  bool TopSortDFS(const int&, std::vector<Colors>&, std::vector<int>&);
  std::vector<int> TopSort();
};

bool Graph::TopSortDFS(const int& v, std::vector<Colors>& colors, std::vector<int>& top_sorted) {
  colors[v] = GRAY;
  for (auto u : graph[v]) {
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
  std::vector<Colors> colors(graph.size(), WHITE);
  std::vector<int> top_sorted;
  for (size_t v = 0; v < graph.size(); ++v) {
    if (colors[v] == WHITE) {
      if (!TopSortDFS(v, colors, top_sorted)) {
        return {-1};
      }
    }
  }
  reverse(top_sorted.begin(), top_sorted.end());
  return top_sorted;
}

int main() {
  int n;
  std::cin >> n;
  std::string s;

  Graph red(n);
  Graph blue(n);
  for (int i = 0; i < n - 1; ++i) {
    std::cin >> s;
    for (int j = 0; j < n - i; ++j) {
      if (s[j] == 'R') {
        red.graph[i].push_back(j + i + 1);
      }
      if (s[j] == 'B') {
        blue.graph[i].push_back(j + i + 1);
      }
    }
  }
  std::vector<int> topsorted_blue = blue.TopSort();
  std::vector<int> topsorted_red = red.TopSort();
  std::reverse(topsorted_red.begin(), topsorted_red.end());

  if (topsorted_blue == topsorted_red) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}