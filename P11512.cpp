/*
Suffix array implementation: http://web.stanford.edu/class/cs97si/suffix-array.pdf
Input: String A=a0a1...an-1
Denote suffices: Ai = ai...an-1
Sort for suffix array:
abac = A0
ac = A2
bac = A1
c = A3
=> Suffix array P = (A0, A2, A1, A3) = (0,2,1,3)
Algorithm maintains order of suffixes sorted by prefixes of length 2^k.
m steps. (because m=ceil(logn)
Ai^k = "Aik" = Subsequence of A of length 2^k starting at position i.
Ex: A = abcdefg, A12 = bcde.
Maintain position of Ajk, (j=1..n) in P(k,i)
 */
struct Entry { 
  int nr[2], p; 
};
bool cmp(struct Entry a, struct Entry b) { 
  return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1]) : (a.nr[0] < b.nr[0]); 
}
std::ostream& operator<<(std::ostream& os, const Entry& e) {
  if(e.nr[0] >= 0)
    os << (char)(e.nr[0]+'A');
  else
    os << e.nr[0];
  os << "/";
  if(e.nr[1] >= 0)
    os << (char)(e.nr[1]+'A');
  else
    os << e.nr[1];
  os << "/" << e.p;
  return os;
}

/*
Suffix array in last row of P.
 */
int* computeSuffixArray(const string &A, int &step) {
  int N = (int)A.size();

  int MAXLG = 4;
  {
    int maxN = 2;
    while(maxN <= N) {
      ++MAXLG;
      maxN <<= 1;
    }
  }
  int *P = new int[MAXLG*N]; // index level*N + i
  Entry *L = new Entry[N];

  FORI(N) {
    P[i] = (int)A[i]-'A'; // Initially ordered P[0*N+i] by characters.
  }
  
  step = 1;
  for(int cnt = 1; (cnt >> 1) < N; step++, cnt <<= 1) { 
    // Update L:
    FORI(N) {
      L[i].nr[0] = P[(step-1)*N+i]; 
      L[i].nr[1] = i + cnt < N ? P[(step-1)*N + i + cnt] : -1; 
      L[i].p = i; 
    }
    //cerr << "Step " << step << " P=";

    sort(L, L+N, cmp); // STL sort can be replaced with bucket sort.
    FORI(N) {
      if(i > 0 && L[i].nr[0] == L[i-1].nr[0] && L[i].nr[1] == L[i-1].nr[1])
	P[step*N + L[i].p] = P[step*N + L[i-1].p];
      else
	P[step*N + L[i].p] = i; 
    }
  } 
  //cerr << "Suffix array constructed started A=" << A << ", N=" << N << ", MAXLG=" << MAXLG << ", N=" << N << endl;

  delete[] L;

  return P;
} 

// Longest common prefix of the two suffixes on positions x and y.
int lcp(int x, int y, int *P, int step, int N) { 
  int k, ret = 0; 
  if (x == y) 
    return N - x; 
  for (k = step - 1; k >= 0 && x < N && y < N; k--) {
    if (P[k*N + x] == P[k*N + y]) {
      x += 1 << k, y += 1 << k, ret += 1 << k; 
    }
  }
  return ret; 
} 

int main() {
  string A; 
  int N, step;
  FORCAS {
    cin >> A;
    N = (int)A.size();
    int* P = computeSuffixArray(A, step);
    PI *sortedIndices = new PI[N];
    FORI(N)
      sortedIndices[i] = PI(P[(step-1)*N+i], i);
    sort(sortedIndices,sortedIndices+N);
      
    string longest;
    int cnt = 0;
    //cerr << "suffix='" << A.substr(sortedIndices[0].second) << "'" << endl;
    for(int i = 1; i < (int)A.size(); ++i) {
      int len = lcp(sortedIndices[i-1].second, sortedIndices[i].second, P, step, (int)A.size());
      int pos = sortedIndices[i].second;
      if(len > (int)longest.size()) {
	longest = A.substr(pos, len);
	cnt = 2;
      }
      else if(len > 0 && len == (int)longest.size() && longest == A.substr(pos, len)) {
	++cnt;
      }
      //cerr << "len=" << len << ", suffix='" << A.substr(pos) << "', common='" << longest << "'" << endl;
    }
    if(cnt == 0)
      cout << "No repetitions found!" << endl;
    else
      cout << longest << " " << cnt << endl;
  }
  return 0;
}
