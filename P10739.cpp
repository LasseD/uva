int main() {
  int *A[1001];
  FORI(1001)
    A[i] = new int[1001]; // A[i][j] = i=|L|+|R|, j=cut idx
  
  FORCAS {
    GS(s);
    //cerr << s << endl;
    int len = (int)s.size();
    if(len == 1) {
      cout << "Case " << cas+1 << ": 0" << endl;
      continue;
    }
    if(len == 2) {
      cout << "Case " << cas+1 << ": " << (s[0] == s[1] ? 0 : 1) << endl;
      continue;
    }
    // Len >= 3:

    // Handle rows 0 and 1 first:
    A[0][0] = 0;
    A[1][0] = A[1][1] = 1;
    
    for(int i = 2; i <= len; ++i) {
      A[i][0] = A[i][i] = i;
      //cerr << "|L|+|R|=" << i << ": ";
      for(int j = 1; j < i; ++j) {
	if(s[j-1] == s[len-i+j])
	  A[i][j] = A[i-2][j-1];
	else {
	  // Assume rm left letter:
	  int a = 1 + A[i-1][j-1];
	  // Assume rm right letter:
	  int b = 1 + A[i-1][j];
	  // Assume change left letter to right:
	  int c = 1 + A[i-2][j-1];
	  A[i][j] = MIN(a,MIN(b,c));
	}
	//cerr << " " << A[i][j];
      }
      //cerr << endl;
    }

    int ret = 99999999;
    for(int j = 1; j < len; ++j) {
      ret = MIN(ret, A[len][j]);
    }
    for(int j = 1; j < len-1; ++j) {
      ret = MIN(ret, A[len-1][j]);
    }
    cout << "Case " << cas+1 << ": " << ret << endl;
  }
}
