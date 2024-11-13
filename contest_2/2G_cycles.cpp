#include <algorithm>
#include <iostream>
#include <vector>

enum Colors { WHITE = 0, GRAY = 1, BLACK = 2 };

void Print(const std::vector<int>& v) {
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] + 1 << ' ';
  }
}

std::vector<int> RestorePath(const std::vector<int>& parent, const int& v) {
  std::vector<int> path;
  for (int i = parent[v]; i != v; i = parent[i]) {
    path.emplace_back(i);
  }
  path.emplace_back(v);
  reverse(path.begin(), path.end());
  return path;
}

void DFS(const std::vector<std::vector<int>>& graph, const int& v, std::vector<Colors>& colors,
         std::vector<int>& parent, std::vector<int>& cycle) {
  colors[v] = GRAY;
  for (auto cur : graph[v]) {
    if (colors[cur] == WHITE) {
      parent[cur] = v;
      DFS(graph, cur, colors, parent, cycle);
      if (!cycle.empty()) {
        return;
      }
    } else {
      if (colors[cur] == GRAY) {
        parent[cur] = v;
        cycle = RestorePath(parent, cur);
        return;
      }
    }
  }
  colors[v] = BLACK;
}

int main() {
  int v, e;
  std::cin >> v >> e;
  std::vector<std::vector<int>> graph;
  graph.resize(v);
  int input1, input2;
  for (int i = 0; i < e; ++i) {
    std::cin >> input1;
    std::cin >> input2;
    --input1;
    --input2;
    graph[input1].emplace_back(input2);
  }
  std::vector<Colors> colors(v);
  std::vector<int> parent(v, -1);
  std::vector<int> cycle;

  for (int i = 0; i < v; ++i) {
    if (!colors[i]) {
      DFS(graph, i, colors, parent, cycle);
    }
    if (!cycle.empty()) {
      std::cout << "YES" << '\n';
      Print(cycle);
      return 0;
    }
  }
  std::cout << "NO";
  return 0;
}