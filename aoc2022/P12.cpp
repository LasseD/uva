#define BIG 999999
int main() {
  PI E;
  int steps[100][100], width, height;
  vector<string> M;
  string input;

  // Parse:
  while(cin >> input) {
    M.push_back(input);
    width = (int)input.size();
  }
  height = (int)M.size();
  cout << "Map size: " << width << " x " << height << endl;

  // Initialize step map:
  FORX(width) {
    FORY(height) {
      steps[y][x] = BIG;
      if(M[y][x] == 'S' || M[y][x] == 'a') { // Remove second condition for part 1.
	steps[y][x] = 0;
	M[y][x] = 'a'; // Ensure not special.
	cout << "Start: " << x << ", " << y << endl;
      }
      else if(M[y][x] == 'E') {
	M[y][x] = 'z'; // Ensure not special.
	E=PI(x,y);
	cout << "End: " << x << ", " << y << endl;
      }
    }
  }

  // Walk:
  FORI(1000) { // while(true) {
    FORX(width) {
      FORY(height) {
	for(int xx = -1; xx < 2; xx+=2) {
	  int x2 = x+xx, y2=y;
	  if(x2 >= 0 && x2 < width && y2 >= 0 && y2 < height) {
	    if(M[y][x] <= M[y2][x2]+1) {
	      steps[y][x] = min(steps[y][x], steps[y2][x2]+1);
	    }
	  }
	} // xx
	for(int yy = -1; yy < 2; yy+=2) {
	  int x2 = x, y2=y+yy;
	  if(x2 >= 0 && x2 < width && y2 >= 0 && y2 < height) {
	    if(M[y][x] <= M[y2][x2]+1) {
	      steps[y][x] = min(steps[y][x], steps[y2][x2]+1);
	    }
	  }
	} // yy
      } // FORY
    } // FORX
    /*cout << "STEP " << i << endl;
    FORY(height) {
      FORX(width) {
	if(steps[y][x] == BIG)
	  cout << '-';
	else
	  cout << steps[y][x];
      }
      cout << endl;
    }//*/
  } // while true

  cout << "Answer 1: " << steps[E.YY][E.XX];

  
}
