// 5k numbers.
int main() {
  PLL v[5000]; // value, original sizeition
  LL size = 0, val, mi = 0, ma = 0, key = 811589153;
  while(cin >> val) {
    val *= key; // For part 1, do not do this!
    v[size] = PLL(val, size);
    if(val == 0)
      cout << "0 at " << size << endl;
    mi = min(mi, val);
    ma = max(ma, val);
    size++;
  }
  LL mod = (((ma-mi)/size)+1)*(size-1);
  cout << "Scanned " << size << " numbers. Min: " << mi << ", Max: " << ma << ", mod: " << mod << endl;
  FORJ(size) cout << " " << v[j].XX; cout << endl;
  
  FORK(10) { // For part 1, remove this.
    FORI(size) {
      // Find value to move:
      PLL p;
      LL from, to;
      for(LL j = 0; true; j++) {
	if(v[j].YY == i) {
	  p = v[j];
	  from = j;
	  to = (j+p.XX + mod)%(size-1); // Size-1 for the smaller list without the element
	  break;
	}
      }
      //cout << "Moving " << v[from].XX << " from " << from << " to " << to << endl;
      // Move:
      if(from == to) {
	// done.
      }
      else if(to > from) {
	for(LL k = from+1; k <= to; k++) {
	  swap(v[k],v[k-1]);
	}
      }
      else {
	for(LL k = from-1; k >= to; k--) {
	  swap(v[k],v[k+1]);
	}      
      }
      //FORJ(size) cout << " " << v[j].XX; cout << endl;
    }
    cout << "After round " << (k+1) << endl;
    FORJ(size) cout << " " << v[j].XX; cout << endl;
  } // To remove for part 1

  LL p0;
  for(LL j = 0; true; j++) {
    if(v[j].XX == 0) {
      p0 = j;
      break;
    }
  }
  
  cout << "Adding " << v[(p0+1000)%size].XX << ", " << v[(p0+2000)%size].XX << ", " <<  v[(p0+3000)%size].XX << endl;
  LL answer1 = v[(p0+1000)%size].XX + v[(p0+2000)%size].XX + v[(p0+3000)%size].XX;
  cout << "Answer 1: " << answer1 << endl; // 4045  wrong
}
