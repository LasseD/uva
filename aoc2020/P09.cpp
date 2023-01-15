// Add pre-append to input
int main() {
  GI(pSize);
  vector<LL> all;

  // Read preample:
  LL preample[25], x;
  int idx = 0;
  FORI(pSize) {
    cin >> preample[idx++];
    all.push_back(preample[idx-1]);
  }
  // Find first problematic char:
  LL invalid;
  while(cin >> x) {
    all.push_back(x);
    bool match = false;
    for(int i = 0; !match && i+1 < pSize; i++) {
      for(int j = i+1; j < pSize; j++) {
	if(preample[i] + preample[j] == x) {
	  match = true;
	  break;
	}
      }
    }
    if(!match) {
      cout << "Answer 1: " << x << endl;
      invalid = x;
      break;
    }
    preample[idx++ % pSize] = x;
  }
  while(cin >> x) {
    all.push_back(x);
  }

  // Part 2:
  for(int i = 0; i < (int)all.size()-1; i++) {
    LL sum = all[i];
    for(int j = i+1; j < (int)all.size(); j++) {
      sum+=all[j];
      if(sum > invalid)
	break; // could not be found
      if(sum == invalid) {
	// Find min and max in range:
	LL mi = all[i], ma = all[i];
	for(int k = i+1; k <= j; k++) {
	  mi = min(mi, all[k]);
	  ma = max(ma, all[k]);
	}
	cout << "Answer 2: " << mi+ma << endl;
	return 0;
      }
    }
  }
}
