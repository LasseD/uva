int gib(int *x, int &max) {
  while(max > 0) {
    if(x[max] > 0) {
      int ret = max;
      --x[ret];
      if(x[ret] == 0) {
	--max;
	while(max > 0 && x[max] == 0)
	  --max;
      }
      return ret;      
    }
    --max;
  }
  return 0;
}

int main() {
  int b[101], g[101];
  FORCAS {
    if(cas > 0)
      cout << endl;
    // Read input:
    int maxG = 0, maxB = 0;
    GI(B); GI(SG); GI(SB); // B battlefields, size green, size blue.
    FORI(101)
      b[i] = g[i] = 0;
    FORI(SG) {
      GI(p);
      g[p]++;
      maxG = MAX(maxG, p);
    }
    FORI(SB) {
      GI(p);
      b[p]++;
      maxB = MAX(maxB, p);
    }

    // Simulate:
    while(maxB > 0 && maxG > 0) {

      /*
      cerr << "green";
      for(int j = 100; j > 0; --j) {
	FORK(g[j])
	  cerr << " " << j;
      }
      cerr << endl;
      cerr << "Blue:";
      for(int j = 100; j > 0; --j) {
	FORK(b[j])
	  cerr << " " << j;
      }
      cerr << endl;
      //*/
      
      
      stack<int> sg, sb;
      FORI(B) {
	if(maxB == 0 || maxG == 0)
	  break; // No more fights this round.
	int green = gib(g, maxG);
	int blue = gib(b, maxB);
	if(green < blue)
	  sb.push(blue-green);
	else if(green > blue)
	  sg.push(green-blue);
      }
      while(!sg.empty()) {
	int green = sg.top();
	++g[green];
	maxG = MAX(maxG, green);
	sg.pop();
      }
      while(!sb.empty()) {
	int blue = sb.top();
	++b[blue];
	maxB = MAX(maxB, blue);
	sb.pop();
      }
    }

    if(maxG == 0 && maxB == 0) {
      cout << "green and blue died" << endl;
    }
    else if(maxB > 0) {
      cout << "blue wins" << endl;
      for(int j = 100; j > 0; --j) {
	FORK(b[j])
	  cout << j << endl;
      }
    }
    else {
      cout << "green wins" << endl;
      for(int j = 100; j > 0; --j) {
	FORK(g[j])
	  cout << j << endl;
      }
    }
  } // FORCAS
}
