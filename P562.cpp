#include <iostream>
#include <algorithm>

#define MAX_SUM 50000

int maxUsage(int m, int *a, int max) {
  int *b = new int[max+1];
  for(int i = 0; i < max+1; ++i)
    b[i] = 0;
  
  for(int coinI = 0; coinI < m; ++coinI) {
    int coin = a[coinI];
    
    for(int i = max; i >= coin; --i) {
      int v = coin + b[i-coin];
      if(v > b[i]) {
	b[i] = v;
      }
    }
  }

  int ret = b[max];
  delete[] b;
  return ret;
}

int main() {
  int n, m, a[100];
  std::cin >> n;
  for(int cas = 0; cas < n; ++cas) {    
    std::cin >> m;
    int sum = 0;
    for(int i = 0; i < m; ++i) {
      std::cin >> a[i];
      sum += a[i];
    }
    std::sort(a, a+m);
    int maxHalf = maxUsage(m, a, sum/2);
    //std::cerr << "Sum: " << sum << ", half usage: " << maxHalf << std::endl;
    std::cout << (sum-2*maxHalf) << std::endl;
  }
}
