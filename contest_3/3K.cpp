#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
 private:
  int vert_num_;
  std::vector<std::vector<int>> weights_;
  std::vector<int> prev_;

 public:
  Graph() = default;
  explicit Graph(const int& n) {
    vert_num_ = n;
    weights_.resize(n, std::vector<int>(n));
    prev_.resize(n, -1);
  }

  void AddEdge(const int& i, const int& j, const int& w) {
    weights_[i][j] = w;
  }

  int HasCycle() {
    std::vector<int> dist(vert_num_);
    int cyclestart = -1;
    for (int k = 0; k < vert_num_; ++k) {
      cyclestart = -1;
      for (int i = 0; i < vert_num_; ++i) {
        for (int j = 0; j < vert_num_; ++j) {
          if (weights_[i][j] != 100000) {
            if (dist[i] + weights_[i][j] < dist[j]) {
              dist[j] = dist[i] + weights_[i][j];
              prev_[j] = i;
              cyclestart = j;
            }
          }
        }
      }
    }
    if (cyclestart != -1) {
      for (int i = 0; i < vert_num_; ++i) {
        cyclestart = prev_[cyclestart];
      }
    }

    return cyclestart;
  }
  auto GetPrev() {
    return prev_;
  }
};

int main() {
  int n = 0;
  int w = 0;
  std::cin >> n;
  Graph graph(n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> w;
      graph.AddEdge(i, j, w);
    }
  }

  int cyclestart = graph.HasCycle();

  if (cyclestart != -1) {
    std::cout << "YES" << '\n';

    std::vector<int> path;
    int i = cyclestart;
    std::vector<int> prev = graph.GetPrev();

    path.push_back(i);
    i = prev[i];
    while (i != cyclestart) {
      path.push_back(i);
      i = prev[i];
    }
    path.push_back(cyclestart);
    std::reverse(path.begin(), path.end());

    std::cout << path.size() << '\n';
    for (auto v : path) {
      std::cout << v + 1 << " ";
    }
  } else {
    std::cout << "NO";
  }
}