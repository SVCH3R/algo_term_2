#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

struct Edge {
  int end;
  int weight;

  Edge(const int& cend, const int& cweight) : end(cend), weight(cweight) {
  }
};

class Graph {
  std::vector<std::vector<Edge>> edges_;
  int size_;

 public:
  explicit Graph(const int& size) : edges_(size + 1), size_(size) {
  }
  void AddEdge(const int&, const int&);
  int BFS(const int&, const int&);
};

void Graph::AddEdge(const int& start, const int& end) {
  edges_[start].emplace_back(Edge(end, 0));
  edges_[end].emplace_back(Edge(start, 1));
}

int Graph::BFS(const int& start, const int& end) {
  std::vector<int> dist(size_ + 1, size_ + 1);
  dist[start] = 0;
  std::deque<int> deque;
  deque.push_front(start);
  int v;

  while (!deque.empty()) {
    v = deque.front();
    deque.pop_front();
    for (auto u : edges_[v]) {
      if (dist[u.end] > dist[v] + u.weight) {
        dist[u.end] = dist[v] + u.weight;
        if (u.weight == 1) {
          deque.push_back(u.end);
        } else {
          deque.push_front(u.end);
        }
      }
    }
  }
  return dist[end] != size_ + 1 ? dist[end] : -1;
}

int main() {
  int n, m, a, b;
  std::cin >> n >> m;
  Graph graph = Graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    graph.AddEdge(a, b);
  }
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> a >> b;
    std::cout << graph.BFS(a, b) << '\n';
  }
}