int longestIncreasingSubsequence(const vector<int> &X) {
  const int N = X.size();
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

  delete[] M;
  return L;
}

int main() {
  int x, L1, L2;
  FORCAS {
    cin >> x >> L1 >> L2; ++L1; ++L2;
    map<int,int> M;
    FORI(L1) {
      cin >> x; --x;
      M[x] = i;
    }

    vector<int> V;
    FORI(L2) {
      cin >> x; --x;
      if(M.find(x) != M.end())
	V.push_back(M[x]);
    }
    cout << "Case " << cas+1 << ": "<< longestIncreasingSubsequence(V) << endl;
  }
}
