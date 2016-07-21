#include <iostream>
#include <vector>
#include <stack>

typedef std::pair<int,int> edge;

void handle(int startVertex, std::vector<int> edges*, int &radius, int &diameter, bool *visited) {
  radius = 0;
  diameter = 0;
  std::stack<int> stack;
  stack.push(
}

int main() {
  int c, l;
  std::cin >> c >> l;

  std::vector<int> edges[100000];

  for(int i = 0; i < l; ++i) {
    fint a, b;
    std::cin >> a >> b;
    edges[a].push_back(b);
    edges[b].push_back(a);
  }

  int maxDiameter = 0;
  bool visited[100000];
  for(int i = 0; i < c; ++i)
    visited[i] = false;
  for(int i = 0; i < c) {
    if(visited[i])
      continue;
    
  }

  std::cout << maxDiameter << std::endl;
}
