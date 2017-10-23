void run(LL prevLow, LL prevHigh, LL &x, LL val) {
  // Compute current interval:
  int low = prevLow, high = prevHigh;
  if(val < 0)
    low+=val;
  else
    high+=val;

  
  if(x < low || x > high) { // Out of current interval!
    // Recurse!
    run(low, high, x, val*-2);
  }

  // x now in interval:
  if(prevLow <= x && x <= prevHigh) {
    cout << 0;
  }
  else {
    x-=val;
    cout << 1;
  }
}

int main() {
  LL x;
  FORCAS {
    cout << "Case #" << cas+1 << ": ";
    cin >> x;
    run(0, 0, x, 1);
    cout << endl;
  }
  return 0;
}
