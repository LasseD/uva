struct Tree {
  int height;
  bool left,top,right,bottom; // hidden
  int dists[4];
};

int main() {
  Tree trees[100][100];
  string S;
  int rows = 0, columns;
  while(cin >> S) {
    FORUI(S.size()) {
      Tree &t = trees[rows][i];
      t.height = S[i]-'0';
      t.left=t.top=t.right=t.bottom=false;
    }
    columns = (int)S.size();
    rows++;
  }
  cout << rows << " rows, " << columns << " columns" << endl;

  // Left
  FORI(rows-1) {
    if(i == 0) continue; // Not first row.
    int M = trees[i][0].height;
    FORJ(columns-1) {
      if(j == 0) continue; // Not first column.
      Tree &t = trees[i][j];
      if(t.height > M) {
	M = t.height;
      }
      else {
	t.left = true;
      }
    }
  }
  // Right:
  FORI(rows-1) {
    if(i == 0) continue; // Not first row.
    int M = trees[i][columns-1].height;
    FORJ(columns-1) {
      if(j == 0) continue; // Not first column.
      Tree &t = trees[i][columns-1-j];
      if(t.height > M) {
	M = t.height;
      }
      else {
	t.right = true;
      }
    }
  }
  // Top:
  FORI(columns-1) {
    if(i == 0) continue; // Not first c
    int M = trees[0][i].height;
    FORJ(rows-1) { 
      if(j == 0) continue; // Not first r
      Tree &t = trees[j][i];
      if(t.height > M) {
	M = t.height;
      }
      else {
	t.top = true;
      }
	  	
    }
  }
  // Bottom:
  FORI(columns-1) {
    if(i == 0) continue; // Not first c
    int M = trees[columns-1][i].height;
    FORJ(rows-1) { 
      if(j == 0) continue; // Not first r
      Tree &t = trees[columns-1-j][i];
      if(t.height > M) {
	M = t.height;
      }
      else {
	t.bottom = true;
      }
    }
  }
  int answer1 = 2 * rows - 2 + 2*columns-2;
  long answer2 = 0;
  FORI(rows-1) {
    if(i == 0) continue; // Not first row.
    FORJ(columns-1) { 
      if(j == 0) continue; // Not first column.
      Tree &t = trees[i][j];
      if(t.left && t.right && t.top && t.bottom) {
      }
      else {
	answer1++;
      }
      // Answer2:
      long x1 = 0, x2 = 0, x3 = 0, x4 = 0;
      for(int i2 = i-1; i2>=0; i2--) {
	x1++;
	if(trees[i2][j].height >= t.height) {
	  break;
	}
      }
      for(int i2 = i+1; i2<rows; i2++) {
	x2++;
	if(trees[i2][j].height >= t.height) {
	  break;
	}
      }
      for(int j2 = j-1; j2>=0; j2--) {
	x3++;
	if(trees[i][j2].height >= t.height) {
	  break;
	}
      }
      for(int j2 = j+1; j2<rows; j2++) {
	x4++;
	if(trees[i][j2].height >= t.height) {
	  break;
	}
      }
      answer2 = max(answer2, x1*x2*x3*x4);
    }
  }
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
