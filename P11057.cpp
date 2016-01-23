#include <iostream>
#include <algorithm>

int main() {
  int N, M, a[10000];
  while(std::cin >> N) {
    // Read data:
    for(int i = 0; i < N; ++i)
      std::cin >> a[i];
    std::sort(a, a+N);
    std::cin >> M;

    // Find be pair:
    int best = -1;
    int i = 0;
    int j = N-1;
    while(i < j) {
      if(a[i]+a[j] > M) {
	--j;
	continue;
      }
      if(a[i]+a[j] == M)
	best = a[i];
      ++i;
    }
    std::cout << "Peter should buy books whose prices are " << best << " and "<<(M-best)<<"." << std::endl << std::endl;
  }
  return 0;
}
