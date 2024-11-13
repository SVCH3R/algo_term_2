#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const int kMinNum = 1111;

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
    std::cout << v[i] << '\n';
  }
}

class Graph {
 private:
  std::vector<std::vector<int>> graph_;

 public:
  explicit Graph() : graph_() {
  }
  explicit Graph(const std::vector<std::vector<int>>& graph) : graph_(graph) {
  }
  explicit Graph(const int& v) : graph_(std::vector<std::vector<int>>(v)) {
  }
  DistAndPath BFS(const int& start, const int& end);
  void AddEdge(const int&, const int&);
};

DistAndPath Graph::BFS(const int& start, const int& end) {
  std::vector<int> dist = std::vector<int>(10000, kInf);
  std::vector<int> parent = std::vector<int>(10000, -1);
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
}

int Plus(int x) {
  if (x / 1000 != 9) {
    return 1000 + x;
  }
  return -1;
}
int Minus(int x) {
  if (x % 10 != 1) {
    return x - 1;
  }
  return -1;
}
int Left(int x) {
  return 10 * (x % 1000) + x / 1000;
}
int Right(int x) {
  return 1000 * (x % 10) + x / 10;
}

int main() {
  int start, end;
  std::cin >> start >> end;
  if (start == end) {
    std::cout << start << '\n';
    return 0;
  }
  Graph graph = Graph(10000);
  for (int i = kMinNum; i < 10000; ++i) {
    if (i / 1000 != 0 && i / 100 % 10 != 0 && i / 10 % 10 != 0 && i % 10 != 0) {
      graph.AddEdge(i, Right(i));
      graph.AddEdge(i, Left(i));
      if (Plus(i) != -1) {
        graph.AddEdge(i, Plus(i));
      }
      if (Minus(i) != -1) {
        graph.AddEdge(i, Minus(i));
      }
    }
  }
  DistAndPath ans = graph.BFS(start, end);
  std::cout << ans.dist[end] + 1 << '\n';
  Print(ans.path);
}