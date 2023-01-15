// Remove commas from input
int Q[1000][1000];

int main() {
  vector<PI> v;
  int x, y, miX = 999, miY = 999, maX = -1, maY = -1;
  while(cin >> x >> y) {
    v.push_back(PI(x,y));
    miX = min(miX,x);
    miY = min(miY,y);
    maX = max(maX,x);
    maY = max(maY,y);
  }
  cout << "Stuff in area " << miX << "," << miY << " -> " << maX << "," << maY << endl;
  FORUI((int)v.size()) {
    v[i].XX-=miX;
    v[i].YY-=miY;
  }
  maX-=miX;
  maY-=miY;
  cout << "Now in area 0,0 -> " << maX << "," << maY << endl;
  
  FORY(maY+1) {
    FORX(maX+1) {
      int minDist = 99999;
      int minIdx;
      int cntMin = 0;
      int idx = 0;
      FORIT(vector<PI>, v) {
	int dist = abs(x - it->XX) + abs(y - it->YY);
	if(dist < minDist) {
	  minDist = dist;
	  cntMin = 1;
	  minIdx = idx;
	}
	else if(dist == minDist) {
	  cntMin++;
	}
	idx++;
      }
      if(cntMin == 1) {
	Q[y][x] = minIdx;
      }
      else {
	Q[y][x] = -1;
      }
    }
  }
  
  // Print:
  FORY(maY+1) {
    FORX(maX+1) {
      int idx = Q[y][x];
      if(idx == -1)
	cout << ".";
      else
	cout << ((char)('a'+idx));
    }
    cout << endl;
  }
  
  int *areaSize = new int[v.size()];
  FORUI(v.size()) {
    areaSize[i] = 0;
  }
  FORY(maY+1) {
    FORX(maX+1) {
      int idx = Q[y][x];
      if(idx == -1)
	continue;
      else if(areaSize[idx] == -1)
	continue;
      else if(x == 0 || x == maX || y == 0 || y == maY) {
	areaSize[idx] = -1;
      }
      else {
	areaSize[idx]++;
      }
    }
  }
  int largestArea = -1;
  FORUI(v.size()) {
    cout << "Area size for " << i << ": " << areaSize[i] << endl;
    largestArea = max(areaSize[i], largestArea);
  }
  cout << "Answer 1: " << largestArea << endl;

  // Part 2:
  LL maxDist = 10000;
  int answer2 = 0;
  FORY(maY+1) {
    FORX(maX+1) {
      LL sumDist = 0;
      FORIT(vector<PI>, v) {
	int dist = abs(x - it->XX) + abs(y - it->YY);
	sumDist += dist;
      }
      if(sumDist <= maxDist)
	answer2++;
    }
  }
  cout << "Answer 2: " << answer2 << endl;
}
