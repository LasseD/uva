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

int cmpPrefix(int startS, string &S, string &T) {
  //cerr << T << " vs " << S.substr(startS) << endl;
  FORUI(T.size()) {
    int j = i+startS;
    if(j >= (int)S.size())
      return -1;
    if(S[j] == T[i])
      continue;
    if(S[j] < T[i])
      return -1;
    return 1;
  }
  return 0;
}

int main() {
  char c, cS[100004], cT[1004];
  int cases;
  scanf("%d", &cases);
  getchar(); // newline
  for(int cas = 0; cas < cases; ++cas) {
    int q, step; 
    
    int x = 0;
    for(; isalpha(c = getchar()); ++x)
      cS[x] = c;
    cS[x] = '\0';
    //gets(cS);
    string S(cS);
    scanf("%d", &q);
    getchar(); // new line
    //cerr << "S='" << S << "'" << endl;

    int N = (int)S.size();
    int* P = computeSuffixArray(S, step);
    int* sortedIndices = new int[N];
    FORI(N)
      sortedIndices[P[(step-1)*N+i]] = i;
    
    /*
    cerr << "Sorted suffix indices of " << S << ": ";
    FORI(N)
      cerr << " " << sortedIndices[i];
    cerr << endl;//*/

    FORI(q) {
      for(x = 0; isalpha(c = getchar()); ++x)
	cT[x] = c;
      cT[x] = '\0';
      //gets(cT);
      string T(cT);
      //cerr << "T='" << T << "'" << endl;
      
      int min = 0;
      int max = N;
      while(min < max-1) {
	int mid = (min+max)/2;
	int c = cmpPrefix(sortedIndices[mid], S, T);
	if(c == 0) {
	  min = mid;
	  break;
	}
	else if(c < 0)
	  min = mid;
	else
	  max = mid;
      } // while min < max

      if(cmpPrefix(min >= N ? 0 : sortedIndices[min], S, T) == 0)
	cout << "y" << endl;
      else
	cout << "n" << endl;
    } // for q
    delete[] P;
    delete[] sortedIndices;
  }
  return 0;
}
