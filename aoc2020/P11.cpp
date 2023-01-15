#define SIZE 200

string m1[SIZE], m2[SIZE];
int width, height = 0;
PI dirs[8] = {PI(-1,0),PI(-1,-1),PI(-1,1),PI(0,1),PI(0,-1),PI(1,-1),PI(1,0),PI(1,1)};

void print() {
  FORY(height) {
    cout << m1[y] << endl;
  }
  cout << endl;
}

bool same() {
  FORY(height) {
    FORX(width) {
      if(m1[y][x] != m2[y][x])
	return false;
    }
  }
  return true;
}

int main() {
  while(getline(cin, m1[height])) {
    m2[height] = m1[height];
    height++;
  }
  width = (int)m1[0].size();
  // Simulate:
  print();
  int rounds = 0;
  do {
    FORY(height) {
      FORX(width) {
	char c = m1[y][x];
	m2[y][x] = c;
	if(c == 'L') {
	  // Find out if it gets occupied:
	  bool allEmpty = true;
	  FORI(8) { // Dirs
	    for(int j = 1; true; j++) { // Only part 2!
	      int xx = x + dirs[i].XX*j;
	      int yy = y + dirs[i].YY*j;
	      if(xx < 0 || xx >= width || yy < 0 || yy >= height)
		break;
	      if(m1[yy][xx] == '#') {
		allEmpty = false;
		break;
	      }
	      if(m1[yy][xx] == 'L') {
		break;
	      }	      
	    }
	  }
	  if(allEmpty) {
	    m2[y][x] = '#'; // Occupied now.
	  }
	}
	else if(c == '#') {
	  // Find out if it gets occupied:
	  int cntOccupied = 0;
	  FORI(8) { // Dirs
	    for(int j = 1; true; j++) { // Only part 2!
	      int xx = x + dirs[i].XX*j;
	      int yy = y + dirs[i].YY*j;
	      if(xx < 0 || xx >= width || yy < 0 || yy >= height)
		break;
	      if(m1[yy][xx] == '#') {
		cntOccupied++;
		break;
	      }
	      if(m1[yy][xx] == 'L') {
		break;
	      }	      
	    }
	  }
	  if(cntOccupied >= 5) // 4 for part 1
	    m2[y][x] = 'L'; // Leave
	}
      }
    }
    rounds++;
    swap(m1, m2);
    print();
  }while(!same());

  int answer1 = 0;
  FORY(height) {
    FORX(width) {
      if(m1[y][x] == '#')
	answer1++;
    }
  }
  cout << answer1 << endl;
}
