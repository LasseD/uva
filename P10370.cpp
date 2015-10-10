#include <iostream>
#include <stdio.h>

int main() {
  int C;
  std::cin >> C;
  int a[1001];
  for(int ignore = 0; ignore < C; ++ignore) {
    int N;
    std::cin >> N;
    int sum = 0;
    for(int i = 0; i < N; ++i) {
      int m;
      std::cin >> m;
      a[i] = m;
      sum += m;
    }
    double avg = sum/(double)N;
    int aboveAverage = 0;
    for(int i = 0; i < N; ++i) {
      if(a[i] > avg)
	++aboveAverage;
    }
    printf("%.3f%%\n", 100*aboveAverage/(double)N);
  }
  return 0;
}
