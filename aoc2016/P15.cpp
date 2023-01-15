// Clean input by rm "Disc #", "positions; at time=0, it is at position ", ".", "har "
int size[10], startPosition[10];

int main() {
  int SIZE;
  while(cin >> SIZE >> size[SIZE-1] >> startPosition[SIZE-1]) {
    // Read input :)
  }
  for(long time0 = 0; true; time0++) {
    bool ok = true;
    FORI(SIZE) {
      if((startPosition[i] + time0 + i+1) % size[i] != 0) {
	ok = false;
	break;
      }
    }
    if(ok) {
      cout << time0 << endl;
      return 0;
    }
  } // for time0  
}
