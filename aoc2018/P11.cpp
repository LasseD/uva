int serial;

LL get(int x, int y) {
  LL rackID = x+10;
  LL powerLevel = rackID*y;
  powerLevel += serial;
  powerLevel *= rackID;
  powerLevel /= 100;
  powerLevel = powerLevel%10;
  powerLevel -= 5;
  return powerLevel;
}

int main() {
  cin >> serial;
  
  LL best = -9999999;
  int bestX, bestY, bestSize;
  for(int y = 1; y <= 300; y++) {
    for(int x = 1; x <= 300; x++) {
      LL v = get(x,y);
      if(v > best) {
	bestX = x;
	bestY = y;
	best = v;
	bestSize = 1;
      }
      for(int size = 2; x + size-1 <= 300 && y + size-1 <= 300; size++) {
	int xx = x + size-1;
	for(int i = 0; i < size; i++) {
	  v += get(xx, y+i);
	}
	int yy = y + size-1;
	for(int i = 0; i < size-1; i++) {
	  v += get(x+i, yy);
	}
	if(v > best) {
	  bestX = x;
	  bestY = y;
	  best = v;
	  bestSize = size;
	}
      }
    }
  }

  cout << "Best square at top-left " << bestX << "," << bestY << "," << bestSize << endl;
  cout << "Best value: " << best << endl;
}
