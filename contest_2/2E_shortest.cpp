#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int kInf = 2147483647;

struct PointAndWeight {
  int point;
  int weight;
  PointAndWeight(const int& c_point, const int& c_weight) : point(c_point), weight(c_weight){};
};

struct ComparePoints {
  bool operator()(const PointAndWeight& lhs, const PointAndWeight& rhs) const {
    return lhs.point > rhs.point;
  }
};

class Graph {
 private:
  std::vector<std::vector<PointAndWeight>> graph_;

 public:
  explicit Graph() : graph_(std::vector<std::vector<PointAndWeight>>()) {
  }
  explicit Graph(const std::vector<std::vector<PointAndWeight>>& graph) : graph_(graph) {
  }
  explicit Graph(const int& v) : graph_(std::vector<std::vector<PointAndWeight>>(v)) {
  }
  int BFS(const int& start, const int& end);
  void AddEdge(const int&, const PointAndWeight&);
};

void Graph::AddEdge(const int& first, const PointAndWeight& second) {
  graph_[first].emplace_back(second);
  // graph_[second.point].emplace_back(PointAndWeight(first, second.weight));
}
int Graph::BFS(const int& start, const int& end) {
  std::vector<int> dist = std::vector<int>(graph_.size(), kInf);
  std::priority_queue<PointAndWeight, std::vector<PointAndWeight>, ComparePoints> q;
  dist[start] = 0;
  q.push({0, start});
  while (!q.empty()) {
    PointAndWeight dv = q.top();
    q.pop();
    if (dv.point > dist[dv.weight]) {
      continue;
    }
    for (auto uw : graph_[dv.weight]) {
      if (dist[dv.weight] + uw.weight < dist[uw.point]) {
        dist[uw.point] = dist[dv.weight] + uw.weight;
        q.push({dist[uw.point], uw.point});
      }
    }
  }
  if (dist[end] == kInf) {
    return -1;
  }
  return dist[end];
}

int main() {
  int vertices, edges, start, end, input1, input2, weight;
  std::cin >> vertices >> edges >> start >> end;
  --start;
  --end;
  Graph graph = Graph(vertices);

  for (int i = 0; i < edges; ++i) {
    std::cin >> input1;
    std::cin >> input2;
    std::cin >> weight;
    --input1;
    --input2;
    graph.AddEdge(input1, PointAndWeight(input2, weight));
  }

  std::cout << graph.BFS(start, end);
}