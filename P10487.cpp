#include <iostream>
#include <algorithm>

#define DIFF(a,b) ((a)<(b) ? ((b)-(a)) : ((a)-(b)))

int main() {
  int n, m, a[1000], b;
  for(int cas = 1; true; ++cas) {
    std::cin >> n;
    if(n == 0)
      return 0;
    std::cout << "Case " << cas << ":" << std::endl;
    for(int i = 0; i < n; ++i)
      std::cin >> a[i];
    std::sort(a, a+n);
    /*
    std::cerr << "Numbers: " << std::endl;
    for(int i = 0; i < n; ++i)
      std::cerr << " " << a[i];
    std::cerr << std::endl;//*/
    std::cin >> m;
    for(int i = 0; i < m; ++i) {
      std::cin >> b;
      int bestSum = a[0] + a[n-1];
      // Best sum above b:
      int high = n-1;
      for(int low = 0; low < high; ++low) {
	while(low < high-1 && a[low]+a[high-1] >= b) {
	  --high;
	}
	if(low < high && DIFF(b,bestSum) > DIFF(b,a[low]+a[high]))
	  bestSum = a[low]+a[high];
	if(low < high-1 && DIFF(b,bestSum) > DIFF(b,a[low]+a[high-1]))
	  bestSum = a[low]+a[high-1];
      }
      std::cout << "Closest sum to " << b << " is " << bestSum << "." << std::endl;
    }
  }
}
