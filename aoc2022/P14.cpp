#define W 400
#define H 160
#define OFFSETW 300
// Fix input: rm , and ->
char cave[H][W];
void output() {
  FORY(H) {
    FORX(W) {
      cout << cave[y][x];
    }
    cout << endl;
  }
}

bool blocked(char c) {
  return c == '#' || c == 'o';
}
int main() {
  FORX(W) {
    FORY(H) {
      cave[y][x] = '.';
    }
  }

  int maxW = 0, maxH = 0, minW = 1000, minH = 1000;
  
  string line;
  while(getline(cin, line)) {
    stringstream ss; ss << line;
    int x1, y1, x2, y2;
    ss >> x1 >> y1; x1-=OFFSETW;
    maxW = max(maxW, x1);
    maxH = max(maxH, y1);
    minW = min(minW, x1);
    minH = min(minH, y1);
    while(ss >> x2 >> y2) { x2-=OFFSETW;
      // Draw:
      if(x1 == x2) {
	for(int y = y1; true; y = (y2 > y1 ? y+1:y-1)) {
	  cave[y][x1] = '#';
	  if(y == y2)
	    break;
	}
      }
      else if(y1 == y2) {
	for(int x = x1; true; x = (x2 > x1 ? x+1:x-1)) {
	  cave[y1][x] = '#';
	  if(x == x2)
	    break;
	}
      }
      else {
	cerr << "Not rectilinear!" << endl;
	die();
      }
      x1 = x2;
      y1 = y2;
      maxW = max(maxW, x1);
      maxH = max(maxH, y1);
      minW = min(minW, x1);
      minH = min(minH, y1);
    }
  }

  // Part 2 floor:
  FORX(W)
    cave[maxH+2][x] = '#';

  // Simulate:
  bool voided = false;
  for(int drop = 0; !voided; drop++) {
    PI p(500-OFFSETW, 0);
    while(true) {
      if(p.YY >= 160) {
	voided = true;
	cout << "Answer 1: " << drop << endl;
	break;
      }
      if(!blocked(cave[p.YY+1][p.XX])) {
	p.YY+=1;
      }
      else if(!blocked(cave[p.YY+1][p.XX-1])) {
	p.XX-=1;
	p.YY+=1;
      }
      else if(!blocked(cave[p.YY+1][p.XX+1])) {
	p.XX+=1;
	p.YY+=1;
      }
      else {
	// blocked!
	cave[p.YY][p.XX] = 'o';
	if(p.YY == 0) {
	  voided = true; // Part 2
	  cout << "Answer 2: " << (drop+1) << endl;
	}
	break;
      }
    } // while true;
  } // FOR DROP
  output();

  cout << " MAX: " << maxW << ", " << maxH << endl;
  cout << " MIN: " << minW << ", " << minH << endl;

  return 0;
}
