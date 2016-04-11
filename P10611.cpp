#include <iostream>

long lower_bound(long x, long *a, int size) {
  int low = 0;
  int high = size;
  while(low < high-1) {
    int mid = (low+high)/2;
    if(a[mid] >= x)
      high = mid;
    else
      low = mid;
  }
  return a[low] < x ? a[low] : -1; 
}

long upper_bound(long x, long *a, int size) {
  int low = -1;
  int high = size-1;
  while(low < high-1) {
    int mid = (low+high)/2;
    if(a[mid] <= x)
      low = mid;
    else
      high = mid;
  }
  return a[high] > x ? a[high] : -1; 
}

int main() {
  int N, Q;
  long b, a[50000];
  std::cin >> N;
  for(int i = 0; i < N; ++i)
    std::cin >> a[i];
  std::cin >> Q;
  for(int i = 0; i < Q; ++i) {
    std::cin >> b;
    long l = lower_bound(b, a, N);
    long u = upper_bound(b, a, N);
    if(l == -1)
      std::cout << "X ";
    else
      std::cout << l << " ";
    if(u == -1)
      std::cout << "X" << std::endl;
    else
      std::cout << u << std::endl;
  }
  return 0;
}
