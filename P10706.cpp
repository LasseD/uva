int digits(int x) {
  int ret = 1;
  while(x > 9) {
    x /= 10;
    ++ret;
  }
  return ret;
}

#define MAX_RUN 50000

int main() {  
  long runIdx[MAX_RUN]; // run -> starting pos.
  long runSize[MAX_RUN]; // run -> starting pos.
  runIdx[0] = 0;
  runSize[0] = 0;
  for(long i = 1; i < MAX_RUN; ++i) {
    runIdx[i] = runIdx[i-1]+runSize[i-1];
    runSize[i] = runSize[i-1]+digits(i);
  }
  //cerr << "RUN IDX[" << MAX_RUN-1 << "] = " << runIdx[MAX_RUN-1] << endl;

  int digitsInRet = runSize[MAX_RUN-1]+1000;
  int *ret = new int[digitsInRet];
  for(int Q = 1, IDX = 0; IDX+digits(Q) < digitsInRet; ++Q) {
    int LEN = digits(Q);
    int COPY = Q;
    FORI(LEN) {
      ret[IDX+LEN-i-1] = COPY%10;
      COPY/=10;
    }
    IDX += LEN;
  }
  /*FORI(300)
    cerr << ret[i];
  cerr << endl;
  cerr << "DIgits in ret: " << digitsInRet << endl;*/
  
  FORCAS {
    long pos; cin >> pos; --pos;
    //cerr << pos+1 << " => ";
    if(pos == 0) {
      cout << 1 << endl;
      continue;
    }   
      
    long low = 1; // IDX of run left of pos
    long high = MAX_RUN; // Too much!
    while(low < high-1) {
      long mid = (low+high)/2;
      if(runIdx[mid] > pos)
	high = mid;
      else
	low = mid;
    }
    //cerr << "(LOW " << low << " -> " << runIdx[low] <<  " ~ " << runIdx[low+1] << ")";
    cout << ret[pos - runIdx[low]] << endl;
  }
  return 0;
}
