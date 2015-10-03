#include <iostream>
#include <algorithm>

int main() {
  int cases;
  std::cin >> cases;
  for(int ignore = 0; ignore < cases; ++ignore) {
    int r;
    std::cin >> r;
    int *s = new int[r];
    for(int i = 0; i < r; ++i) {
      int si;
      std::cin >> si;
      s[i] = si;
    }
    std::sort(s, &s[r]);
    int vito = s[r/2];
    int sum = 0;
    for(int i = 0; i < r; ++i) {
      if(i <= r/2) {
	sum += vito-s[i];
      }
      else {
	sum += s[i]-vito;
      }
    }
    std::cout << sum << std::endl;
    delete[] s;
  }
}
