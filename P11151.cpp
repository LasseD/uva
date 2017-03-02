int main() {
  int A[3300];
  char s[1009], cs;
  int *pp, *p, *c;
  int cases;
  scanf("%d", &cases); getchar();
  for(int cas = 0; cas < cases; ++cas) {
    int N = 0;
    while(isalpha(cs = getchar()))
      s[N++] = cs;
    if(N <= 1) {
      cout << N << endl;
      continue;
    }

    FORI(N)
      A[i] = 0;
    FORI(N)
      A[i+N] = 1;
    pp = &A[0];
    p = &A[N];
    c = &A[2*N];
    for(int len = 2; len <= N; ++len) {
      //cerr << "len=" << len << ":" << endl;
      FORI(N-len+1) {
	if(s[i] == s[i+len-1]) {
	  c[i] = 2+pp[i+1];
	}
	else {
	  c[i] = MAX(p[i], p[i+1]);
	}
	//cerr << " " << s.substr(i, len) << ": " << c[i] << endl;
      }
      // TODO: Update p, pp and c;
      int *tmp = pp;
      pp = p;
      p = c;
      c = tmp;
    }
    cout << p[0] << endl;
  }
  return 0;
}
