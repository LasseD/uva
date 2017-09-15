#define FIBS 45
int fibs[FIBS];

// Grab numbers greedily.
void decToFib(int dec) {
  int prevI = FIBS+3;
  bool any = false;
  for(int i = FIBS-1; i >= 0; --i) {
    if(dec >= fibs[i] && prevI > i+1) {
      any = true;
      cout << 1;
      dec-=fibs[i];
      prevI = i;
    }
    else if(any)
      cout << 0;
  }
}

int main() {
  // Build fibs:
  fibs[0] = 1;
  fibs[1] = 2;
  for(int i = 2; i < FIBS; ++i) {
    fibs[i] = fibs[i-1]+fibs[i-2];
    if(fibs[i] < fibs[i-1]) {
      cerr << "Die at " << i << endl;
    }
  }

  // RUN!
  FORCAS {
    int dec;
    cin >> dec;
    cout << dec << " = ";
    decToFib(dec);
    cout << " (fib)" << endl;
  }
  return 0;
}
