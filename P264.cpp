#include <iostream>

#define ROW_LEN 4500

int lowerBound(int v, int const * const a) {
  int low = 0;
  int high = ROW_LEN; // Always > v
  while(low < high-1) {
    int mid = (low+high)/2;
    if(a[mid] > v)
      high = mid;
    else if(a[mid] == v)
      return mid;
    else // a[mid] < v
      low = mid;
  }
  return low;
}

/*
1   2   4   7   11 
1/1 1/2 1/3 1/4 1/5

1/N is term T(N) = T(N-1)+N-1 or T(N+1) = T(N)+N
 */
int main() {
  int topRow[ROW_LEN];
  topRow[0] = 1;
  for(int i = 1; i < ROW_LEN; ++i) {
    topRow[i] = topRow[i-1] + i;
    //std::cerr << i << ": " << topRow[i] << std::endl;
  }

  int n;
  while(std::cin >> n) {
    int topRowIdx = lowerBound(n, topRow);
    int sum = topRowIdx+2;
    int slack = n - topRow[topRowIdx]+1;
    int nom = sum - slack;
    int denom = sum - nom;
    if(topRowIdx % 2 == 1)
      std::swap(nom,denom);
    //std::cerr << "SUM: " << sum << ", SLACK: " << slack << " TOP ROW IDX: " << topRowIdx << ", TOP ROW VAL: " << topRow[topRowIdx] << std::endl;
    std::cout << "TERM " << n << " IS " << nom << "/" << denom << std::endl;
  }
  return 0;
}
