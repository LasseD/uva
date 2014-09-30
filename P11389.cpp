#include <iostream>
#include <algorithm>

int main() {
  while(true) {
    int n, d, r;
    std::cin >> n >> d >> r;
    if(n == 0 && d == 0 && r == 0)
      return 0;
    int *morn = new int[n];
    int *afte = new int[n];
    for(int i = 0; i < n; ++i) {
      int a;
      std::cin >> a;
      morn[i] = a;
    }
    for(int i = 0; i < n; ++i) {
      int a;
      std::cin >> a;
      afte[i] = -a;
    }
    std::sort(morn, &morn[n]);
    std::sort(afte, &afte[n]);
    int sum = 0;
    for(int i = 0; i < n; ++i) {
      int hours = morn[i] - afte[i];
      if(hours <= d)
	continue;
      sum += hours - d;
    }
    std::cout << (r*sum) << std::endl;
    delete[] morn;
    delete[] afte;
  }
}
