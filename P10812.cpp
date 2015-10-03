#include <iostream>

/*
 a, b > 0, a > b:
 a+b=s, a-b=d.
 a+b+a-b = s+d => a = (s+d)/2
 a+b-a+b = s-d => b = (s-d)/2
 */
int main() {
  int N;
  std::cin >> N;
  for(int ignore = 0; ignore < N; ++ignore) {
    int s, d;
    std::cin >> s >> d;
    if(d > s || (s+d)%2!=0) {
      std::cout << "impossible" << std::endl;
      continue;
    }
    std::cout << ((s+d)/2) << " " << ((s-d)/2) << std::endl;
  }
  return 0;
}
