/**
Take 2...(int)(N/2) out of the N:
- Are the two partitions Len/2? If not, reject.
- Can the two partitions create Len/4? If Yes, accepts.
- Else: Reject.
 */
bool quarterOK(int const * const sticks, const int n, const int avg) {
  /*cerr << "Checking quarter! avg=" << avg << " n=" << n << endl;
  FORI(n)
    cerr << " " << sticks[i];//*/
  bool *B = new bool[avg+1];
  memset(B, false, sizeof(bool)*(avg+1));
  B[0] = true;

  FORI(n) {
    int stick = sticks[i];
    for(int target = avg; target >= stick; --target) {
	B[target] |= B[target-stick];
    }
  }

  bool ok = B[avg];
  delete[] B;
  //cerr << endl << " OK=" << ok << endl;
  return ok;
}

bool tryFromStartPosition(int startPosition, int splitSize, int const * const sticks, int n, int avg, int *selection, int sizeSelection, int sumSelection, int *deselection, int sizeDeselection, int sumDeselection) {
  if(sizeSelection == splitSize) {
    if(sumSelection != 2*avg)
      return false;
    while(sizeSelection + sizeDeselection < n) {
      //cerr << "Adding deselection " << sizeDeselection << " = " << sticks[startPosition] << endl;
      sumDeselection += sticks[startPosition];
      deselection[sizeDeselection++] = sticks[startPosition++];
    }
    if(sumDeselection != 2*avg)
      return false;
    if(!quarterOK(selection, splitSize, avg))
      return false;
    //cerr << "FIRST OK!" << endl;
    return quarterOK(deselection, sizeDeselection, avg);
  }
  for(int pos = startPosition; pos < n; ++pos) {
    // Try with pos in selection:
    selection[sizeSelection] = sticks[pos];
    if(sumSelection + sticks[pos] > 2*avg)
      return false; // OK because sticks are sorted.
    if(tryFromStartPosition(pos+1, splitSize, sticks, n, avg, selection, sizeSelection+1, sumSelection + sticks[pos], deselection, sizeDeselection, sumDeselection))
      return true;
    //cerr << "Setting deselection " << sizeDeselection << " = " << sticks[pos] << endl;
    deselection[sizeDeselection++] = sticks[pos];
    sumDeselection += sticks[pos];
    if(sumDeselection > 2*avg)
      return false;
  }
  return false;
}

int main() {
  int n, stick, sticks[20], selection[20], deselection[20];
  FORCAS {
    cin >> n;
    int sum = 0;
    FORI(n) {
      cin >> stick;
      sticks[i] = stick;
      sum += stick;
    }
    sort(sticks, sticks+n);
    int avg = sum/4;
    if(avg*4 != sum || sticks[n-1] > avg) {
      cout << "no" << endl;
      //cerr << "Early fail!" << endl;
      continue;
    }

    bool any = false;
    for(int splitSize = 2; splitSize <= n/2; ++splitSize) {
      any = tryFromStartPosition(0, splitSize, sticks, n, avg, selection, 0, 0, deselection, 0, 0);
      if(any)
	break;
    }
    if(any)
      cout << "yes" << endl;
    else
      cout << "no" << endl;
  }
  return 0;
}
