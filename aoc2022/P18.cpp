// Clean , from input, so cin >> works
typedef pair<int,PI> P3;

#define SIZE 25

int main() {
  vector<P3> v;
  bool Q[SIZE][SIZE][SIZE]; // Lava
  bool A[SIZE][SIZE][SIZE]; // Air
  FORX(SIZE) {
    FORY(SIZE) {
      FORZ(SIZE) {
	Q[x][y][z] = false;
	A[x][y][z] = false;
      }
    }
  }
  int x, y, z, mi[3]={SIZE,SIZE,SIZE}, ma[3]={0,0,0};
  
  while(cin >> x >> y >> z) {
    x++;y++;z++; // So no 0 checks :)
    
    int xyz[3] = {x,y,z};
    FORI(3) {
      mi[i] = min(mi[i],xyz[i]);
      ma[i] = max(ma[i],xyz[i]);
    }
    Q[x][y][z] = true;
    v.push_back(P3(x,PI(y,z)));
  }

  cout << "STATS" << endl;
  cout << "Min: " << mi[0] << ", " << mi[1] << ", " << mi[2] << endl;
  cout << "Max: " << ma[0] << ", " << ma[1] << ", " << ma[2] << endl;

  int answer1 = 0;
  FORIT(vector<P3>, v) {
    P3 p = *it;
    int x = p.XX, y=p.YY.XX, z=p.YY.YY;
    if(!Q[x-1][y][z])
      answer1++;
    if(!Q[x+1][y][z])
      answer1++;
    if(!Q[x][y-1][z])
      answer1++;
    if(!Q[x][y+1][z])
      answer1++;
    if(!Q[x][y][z-1])
      answer1++;
    if(!Q[x][y][z+1])
      answer1++;
  }
  cout << "Answer 1: " << answer1 << endl;

  // Answer 2: Use A to expand from
  // First make walls of air:
  // x = 0 and x=max+1:
  FORY(ma[1]) {
    FORZ(ma[2]) {
      A[0][y][z] = true;
      A[ma[0]+1][y][z] = true;
    }
  }
  // y:
  FORX(ma[0]) {
    FORZ(ma[2]) {
      A[x][0][z] = true;
      A[x][ma[1]+1][z] = true;
    }
  }
  // z:
  FORX(ma[0]) {
    FORY(ma[1]) {
      A[x][y][0] = true;
      A[x][y][ma[2]+1] = true;
    }
  }
  // Iterate expantion:
  bool ok = true;
  while(ok) {
    ok = false;
    // Add air A:
    for(int x = 1; x <= ma[0]; x++) {
      for(int y = 1; y <= ma[1]; y++) {
	for(int z = 1; z <= ma[2]; z++) {
	  if(Q[x][y][z] || A[x][y][z])
	    continue; // Lava or water already!
	  if(A[x-1][y][z] || A[x+1][y][z] || A[x][y-1][z] || A[x][y+1][z] || A[x][y][z-1] || A[x][y][z+1]) {
	    ok = true;
	    A[x][y][z] = true;
	  }
	}
      }
    }
  } // while ok

  // Compute answer2:
  long answer2 = 0;
  for(int x = 1; x <= ma[0]; x++) {
      for(int y = 1; y <= ma[1]; y++) {
	for(int z = 1; z <= ma[2]; z++) {
	  if(!A[x][y][z])
	    Q[x][y][z] = true;
	}
      }
  }
  FORIT(vector<P3>, v) {
    P3 p = *it;
    int x = p.XX, y=p.YY.XX, z=p.YY.YY;
    if(!Q[x-1][y][z])
      answer2++;
    if(!Q[x+1][y][z])
      answer2++;
    if(!Q[x][y-1][z])
      answer2++;
    if(!Q[x][y+1][z])
      answer2++;
    if(!Q[x][y][z-1])
      answer2++;
    if(!Q[x][y][z+1])
      answer2++;
  }
  cout << "Answer 2: " << answer2 << endl;
}
  
