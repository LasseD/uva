/*
  Clean non-ints from input.
  24 minutes
 */
int costOre[4], costC, costO;

int rf[8];
int *robots = rf;
int *fuel = &(rf[4]);

ULL encode() {
  ULL ret = 0;
  FORI(8) {
    ret = (ret << 8) + rf[i];
  }
  return ret;
}

void decode(ULL x) {
  FORI(8) {
    rf[7-i] = x & 0xFF;
    x = x >> 8;
  }
}

void print(ULL x) {
  decode(x);
  cout << "  Fuel:";
  FORI(4)
    cout << " " << fuel[i];
  cout << " Robots:";
  FORI(4)
    cout << " " << robots[i];
  cout << endl;
}

ULL encodeNext() {
  FORI(4) {
    fuel[i] += robots[i];
  }
  ULL ret = encode();
  FORI(4) {
    fuel[i] -= robots[i];
  }
  return ret;
}

int maxOreCost() {
  int ret = 0;
  FORI(4)
    ret = max(ret, costOre[i]);
  return ret;
}

int go(set<ULL> &from, set<ULL> &to) {
  int ret = 0;

  FORIT(set<ULL>, from) {
    ULL x = *it;
    decode(x);

    int geodes = fuel[3]+robots[3];
    if(geodes >= ret) {
      ret = geodes;
    }

    // No robot:
    ULL z = encodeNext();
    // Only skip a bot if ressources are missing for something:
    if(!(fuel[0] >= maxOreCost() && fuel[1] >= costC && fuel[2] >= costO)) {
      if(to.find(z) == to.end()) {
	to.insert(z);
      }
    }
    
    // Build each type of robot:
    for(int i = 3; i >= 0; i--) {
      if(fuel[0] < costOre[i]) {
	continue; // Not enough ore
      }
      if(i == 2 && costC > fuel[1]) {
	continue; // Not enough clay
      }
      if(i == 3 && costO > fuel[2]) {
	continue; // Not enough obsidian
      }
      if(i == 0 && robots[0] >= maxOreCost()) {
	continue; // No need to build more ore bots.
      }
      if(i == 1 && robots[1] >= costC) {
	continue; // No need to build more clay bots.
      }
      if(i == 2 && robots[2] >= costO) {
	continue; // No need to build more obsidian bots.
      }
      
      fuel[0] -= costOre[i];
      if(i == 2) fuel[1]-=costC;
      if(i == 3) fuel[2]-=costO;
      
      robots[i]++;
      fuel[i]--;      
      
      ULL y = encodeNext();
      if(to.find(y) == to.end()) {
	to.insert(y);
      }
      
      robots[i]--;
      fuel[i]++;
      fuel[0] += costOre[i];
      if(i == 2) fuel[1]+=costC;
      if(i == 3) fuel[2]+=costO;

    } // FORI 4
  
    FORI(4) {
      fuel[i] -= robots[i];
    }
  }
  
  from.clear();
  return ret;
}

int main() {
  int idx, expectedIdx = 1;
  int answer1 = 0;
  LL answer2 = 1;
  while(cin >> idx >> costOre[0] >> costOre[1] >> costOre[2] >> costC >> costOre[3] >> costO) {
    if(idx != expectedIdx++) {
      cerr << "Index error" << endl;
      die();
    }
    if(idx > 3) break; // For answer 1, remove this!

    cout << "Blueprint " << idx << endl;
    
    int geodes = 0;
    set<ULL> m1, m2;

    FORI(4)
      robots[i] = fuel[i] = 0;
    robots[0] = 1;
    m1.insert(encode());
    
    FORI(32) { // 24 for answer 1
      geodes = go(m1, m2);
      swap(m1, m2);
      cout << "== Minute " << (i+1) << " ==" << endl << "  " << m1.size() << ", geodes max: " << geodes << endl;
      /*FORIT(set<ULL>, m1) {
	print(*it);
      }//*/
    }
    cout << "Blueprint " << idx << ": " << geodes << " geodes " << endl;
    answer1 += geodes * idx;
    answer2 *= geodes;
  }
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
  /*
    Test input for answer 2: 56*62 = 3472
   */
}
