#include <iostream>
#include <stdio.h>
#include <vector>

// Algorithm from: http://en.wikipedia.org/wiki/Longest_increasing_subsequence
void longestIncreasingSubsequence(const std::vector<int> &X, std::vector<int> &S) {
  const int N = X.size();
  int *P = new int[N]; // P[k] = index of pred. of X[k] in lis ending at X[k] // for backtrc.
  int *M = new int[N+1]; // M[j] = index k of smallest X[k]: E inc. seq. of _len. j_ until X[k]
  
  int L = 0;
  for(int i = 0; i < N; ++i) {
    // Binary search for the largest positive j <= L
    // such that X[M[j]] < X[i]
    int lo = 1;
    int hi = L;
    while(lo <= hi) {
      int mid = (lo+hi)/2;
      if(X[ M[mid] ] < X[i]) {
	lo = mid+1;
      }
      else {
	hi = mid-1;
      }
    }

    // After searching, lo is 1 greater than the
    // length of the longest prefix of X[i]
    const int newL = lo;

    // The predecessor of X[i] is the last index of 
    // the subsequence of length newL-1
    P[i] = M[newL-1];

    if(newL > L) {
      // If we found a subsequence longer than any we've
      // found yet, update M and L
      M[newL] = i;
      L = newL;
    }
    else if(X[i] < X[M[newL]]) {
      // If we found a smaller last value for the
      // subsequence of length newL, only update M
      M[newL] = i;
    }
  }

  // Reconstruct the longest increasing subsequence S
  S.resize(L);
  int k = M[L];
  for(int i = L-1; i >= 0; --i) {
    S[i] = X[k];
    k = P[k];
  }
  delete[] M;
  delete[] P;
}

int main() {
  int counter = 0;
  while(true) {
    std::vector<int> X;
    while(true) {
      int val;
      std::cin >> val;
      if(val == -1) {
	if(X.empty())
	  return 0;
	break;
      }
      X.push_back(-val);
    }
    std::vector<int> S;
    longestIncreasingSubsequence(X, S);

    if(counter > 0)
      std::cout << std::endl;
    std::cout << "Test #" << (++counter) << ":" << std::endl;
    std::cout << "  maximum possible interceptions: " << S.size() << std::endl;
  }
}
