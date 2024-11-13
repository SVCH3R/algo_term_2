#include <iostream>
#include <vector>
#include <queue>

const int kInf = INT32_MAX;

struct Edge {
  int start, end, weight;
  Edge() = default;
  explicit Edge(const int& cstart, const int& cend, const int& cweight) : start(cstart), end(cend), weight(cweight){};
};

struct Graph {
  Graph() = default;
  explicit Graph(const int& n) {
    vertices = n;
    adj.resize(n);
  }
  int vertices;
  std::vector<std::vector<std::pair<int, int>>> adj;
  std::vector<Edge> edges;
};

std::vector<int> FordBellman(const Graph& graph) {
  std::vector<int> dist(graph.vertices, INT32_MAX);
  dist[0] = 0;
  for (int i = 0; i < graph.vertices - 1; ++i) {
    for (const auto& edge : graph.edges) {
      if (dist[edge.start] < INT32_MAX) {
        dist[edge.end] = std::min(dist[edge.end], dist[edge.start] + edge.weight);
      }
    }
  }
  return dist;
}

auto Dijkstra(const Graph& graph, const int& s) {
  std::vector<int> dist(graph.vertices, INT32_MAX);
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
  dist[s] = 0;
  queue.emplace(0, s);
  while (!queue.empty()) {
    auto top = queue.top();
    int w = top.first;
    int v = top.second;
    queue.pop();
    if (w > dist[v]) {
      continue;
    }
    for (const auto& u : graph.adj[v]) {
      if (dist[v] + u.second < dist[u.first]) {
        dist[u.first] = dist[v] + u.second;
        queue.emplace(dist[u.first], u.first);
      }
    }
  }
  return dist;
}

int Max(const std::vector<int>& dist) {
  int max = INT32_MIN;
  for (size_t i = 0; i < dist.size(); ++i) {
    if (dist[i] != INT32_MAX && max < dist[i]) {
      max = dist[i];
    }
  }
  return max;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n + 1);

  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int w = 0;
    std::cin >> u >> v >> w;
    ++u;
    ++v;
    graph.edges.emplace_back(u, v, w);
  }

  for (int i = 1; i < n + 1; ++i) {
    graph.edges.emplace_back(0, i, 0);
  }

  auto dist = FordBellman(graph);

  Graph new_graph(n);
  for (auto& edge : graph.edges) {
    --edge.start;
    --edge.end;
    if (edge.start == -1) {
      break;
    }
    new_graph.adj[edge.start].emplace_back(edge.end, edge.weight + dist[edge.start + 1] - dist[edge.end + 1]);
  }

  auto distance = Dijkstra(new_graph, 0);
  for (size_t j = 0; j < distance.size(); ++j) {
    distance[j] = distance[j] + dist[j + 1] - dist[1];
  }
  int max = Max(distance);

  for (int i = 1; i < n; ++i) {
    distance = Dijkstra(new_graph, i);
    for (size_t j = 0; j < distance.size(); ++j) {
      if (distance[j] == INT32_MAX) {
        continue;
      }
      distance[j] = distance[j] + dist[j + 1] - dist[i + 1];
    }
    max = std::max(max, Max(distance));
  }
  std::cout << max;
}