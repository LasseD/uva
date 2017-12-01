int main() {
  long inside[151], outside[151];
  long n;
  for(n = 1; n <= 150; ++n) {
    long i = 0, o = 0;

    long N = 2*n-1;
    FORX(n) {
      FORY(n) {
	long X = 2*x;
	long Y = 2*y;
	if((X+2)*(X+2)+(Y+2)*(Y+2) <= N*N)
	  ++i;
	if(X*X+Y*Y >= N*N)
	  ++o;	
      }
    }

    //cerr << "n=" << n << " => inside " << i << ", outside: " << o << endl;
    inside[n] = i*4;
    outside[n] = n*n*4 - o*4 - i*4;
  }

  bool first = true;
  while(cin >> n) {
    // Output:
    if(!first)
      cout << endl;
    first = false;

    cout << "In the case n = " << n << ", " << outside[n] << " cells contain segments of the circle." << endl;
    cout << "There are "<<inside[n]<<" cells completely contained in the circle." << endl;
  }
  return 0;
}
