// Remove all, but the numbers from input and add number of steps first.
LL gcd(LL a, LL b) {
  LL c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

LL lcm(LL a, LL b) {
  LL g = gcd(a,b);
  return a*b/g;
}

typedef pair<PLL,PLL> PL4;
typedef pair<PL4,PL4> PL8;

int main() {
  GI(steps);
  LL p[4][3], v[4][3];
  FORI(4) {
    cin >> p[i][0] >> p[i][1] >> p[i][2];
    v[i][0] = v[i][1] = v[i][2] = 0;
  }
  
  // Simulate:
  map<PL8,int> seen[3];

  set<PL8> matched[3];
  vector<LL> A1[3];
  vector<LL> A2[3];
  LL best = 999999999999999;

  LL SCAN = 1000000;
  for(LL k = 0; k < SCAN; k++) {
    FORI(3) {
      PL8 hash(PL4(PLL(p[0][i],p[1][i]),PLL(p[2][i],p[3][i])),PL4(PLL(v[0][i],v[1][i]),PLL(v[2][i],v[3][i])));
      if(matched[i].find(hash) != matched[i].end()) {
	continue; // Already matched.
      }
      
      if(seen[i].find(hash) != seen[i].end()) {
	LL start = seen[i][hash];
	LL loopLength = k-start;

	// Check if better start with loopLength already is found:
	bool skip = false;
	for(int a = 0; a < (int)A2[i].size(); a++) {
	  if(A2[i][a] != loopLength)
	    continue;
	  if(A1[i][a] < start) {
	    skip = true;
	    break;
	  }
	}
	if(skip) {
	  seen[i].erase(hash);
	  continue;
	}

	// Check if better LCM exists!
	LL a1[3], a2[3];
	a1[0] = start;
	a2[0] = loopLength;
	for(int a = 0; a < (int)A1[(i+1)%3].size(); a++) {
	  a1[1] = A1[(i+1)%3][a];
	  a2[1] = A2[(i+1)%3][a];
	  for(int b = 0; b < (int)A1[(i+2)%3].size(); b++) {
	    a1[2] = A1[(i+2)%3][b];
	    a2[2] = A2[(i+2)%3][b];

	    LL maxStart = max(max(a1[0],a1[1]),a1[2]);
	    // Find Least Common Multiple of the cycle lengths:
	    LL LCM = lcm(lcm(a2[0],a2[1]),a2[2]);
	    LL x = LCM + maxStart;
	    if(x < best) {
	      best = x;
	    }
	  } // b
	} // a

	A1[i].push_back(start);
	A2[i].push_back(loopLength);
	matched[i].insert(hash);
	seen[i].erase(hash);
      }
      else { // hash not in seen[i]
	seen[i][hash] = k;
      }
    } // FORI 3

    // Update velocities:
    FORI(4) {
      FORJ(4) {
	if(i == j)
	  continue;
	FORX(3) {
	  v[i][x] += p[j][x] > p[i][x] ? 1 : (p[j][x] < p[i][x] ? -1 : 0);
        }
      }
    }
    // Update positions:
    FORI(4) {
      FORX(3) {
	p[i][x] += v[i][x];
      }
    }

    if(k+1 == steps) {
      LL answer1 = 0;
      FORI(4) {
	LL pot = 0, kin = 0;
	FORX(3) {
	  pot += abs(p[i][x]);
	  kin += abs(v[i][x]);
	}
	answer1 += pot*kin;
      }
      cout << "Answer 1: " << answer1 << endl;
    }
  }
  cout << "Answer 2: " << best << endl;
}
