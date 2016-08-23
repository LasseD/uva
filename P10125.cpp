#include <iostream>
#include <stdio.h>
#include <algorithm>

typedef std::pair<long,long> PP;
typedef std::pair<long,PP> IP;
#define ELE1 second.first
#define ELE2 second.second

int main() {
  long n, a[1000];
  while(true) {
    std::cin >> n;
    if(n == 0)
      return 0;
    for(long i = 0; i < n; ++i)
      std::cin >> a[i];
    std::sort(a, a+n);
    long N = n*(n-1)/2;
    IP *sums = new IP[N+1]; // No zero initialization by adding 1.
    IP *diffs = new IP[N+1]; // No zero initialization.
    long idx = 0;
    for(long i = 0; i < n; ++i) {
      for(long j = i+1; j < n; ++j) {
	sums[idx] = IP(a[i]+a[j], PP(i,j)); // a+b, a, b
	diffs[idx] = IP(a[j]-a[i], PP(i,j)); // d-c, c, d
	++idx;
      }
    }
	
    std::sort(sums, sums+N);
    std::sort(diffs, diffs+N);
    /*
    std::cerr << "N=" << N << ", idx=" << idx << std::endl;
    std::cerr << "SUMS:";
    for(long i = 0; i < N; ++i)
      std::cerr << " " << sums[i].first;
    std::cerr << std::endl;
    std::cerr << "DIFFS:";
    for(long i = 0; i < N; ++i)
      std::cerr << " " << diffs[i].first;
    std::cerr << std::endl;//*/

    long maxD = -5368709120;
    long idxDiffs = 0;
    for(long idxSums = 0; idxSums < N; ++idxSums) {
      long sum = sums[idxSums].first;
      while(idxDiffs < N-1 && diffs[idxDiffs].first < sum)
	++idxDiffs;
      //std::cerr << "idxSums[" << idxSums << "]=" << sums[idxSums].first << ", idxDiffs[" << idxDiffs << "]=" << diffs[idxDiffs].first << std::endl;
      long aI = sums[idxSums].ELE1;
      long bI = sums[idxSums].ELE2;
      for(long idx2 = idxDiffs; idx2 < N && diffs[idx2].first == sum; ++idx2) {
	long cI = diffs[idx2].ELE1;
	long dI = diffs[idx2].ELE2;
	if(aI == cI || aI == dI || bI == cI || bI == dI)
	  continue;
	//std::cerr << "TRY " << a[aI] << "+" << a[bI] << "+" << a[cI] << "=" << a[dI] << std::endl;
	long d = a[dI];
	if(d > maxD)
	  maxD = d;
      }
    }

    if(maxD == -5368709120)
      std::cout << "no solution" << std::endl;
    else
      std::cout << maxD << std::endl;
    delete[] sums;
    delete[] diffs;
  }  
}
