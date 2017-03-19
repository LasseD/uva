#include <iostream>
#include <algorithm>

int main() {
  int N;
  std::cin >> N;
  int *trees = new int[N];
  for(int i = 0; i < N; ++i) {
    int a;
    std::cin >> a;
    trees[i] = -a;
  }
  std::sort(trees, &trees[N]);
  int day = 1;
  int max = 0;
  for(int i = 0; i < N; ++i) {
    int time = day - trees[i] + 1;
    if(time > max)
      max = time;
    ++day;
  }
  std::cout << max << std::endl;
  delete[] trees;
}
