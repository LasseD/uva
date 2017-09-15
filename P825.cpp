int main() {
  int cases, c, r, x, y;
  string line;
  scanf("%d", &cases);
  for(int cas = 0; cas < cases; ++cas) {
    getline(cin, line);
    scanf("%d %d", &r, &c);
    getchar();
    int *a = new int[c*r];
    memset(a, 0, sizeof(int)*r*c);
    a[0] = 1;
    //cerr << "r=" << r << ", c=" << c << endl;
    
    FORI(r) {
      getline(cin, line);
      stringstream ss; ss << line;
      ss >> y;
      --y;
      while(ss >> x) {
	--x;
	a[y*c+x] = -1;
      }
    }

    FORY(r) {
      FORX(c) {
	int idx = y*c+x;
	if(a[idx] == -1) {
	  a[idx] = 0;
	  //cerr << " " << a[idx];
	  continue;
	}
	if(x > 0)
	  a[idx] += a[idx-1];
	if(y > 0)
	  a[idx] += a[idx-c];
	//cerr << " " << a[idx];
      }
      //cerr << endl;
    }

    if(cas > 0)
      cout << endl;
    cout << a[r*c-1] << endl;

    delete[] a;
  }
  return 0;
}
