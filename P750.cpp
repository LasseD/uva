typedef int Solution;

Solution flipHorizontal(Solution s) {
  int digits[8];
  FORI(8) {
    digits[7-i] = 9 - (s % 10);
    s /= 10;
  }
  FORI(8)
    s = 10 * s + digits[i];
  return s;
}
Solution flipVertical(Solution s) {
  Solution ret = 0;
  FORI(8) {
    ret = 10 * ret + s % 10;
    s /= 10;
  }
  return ret;
}
Solution rotate90(Solution s) {
  int digits[8];
  FORI(8) {
    digits[s % 10 - 1] = i+1;
    s /= 10;
  }
  FORI(8)
    s = 10 * s + digits[i];
  return s;
}

void add(Solution x, set<Solution> &s) {
  if(s.find(x) != s.end())
    return; // No add.
  s.insert(x);
  /*
  cerr << "Added";
  int digits[8];
  FORI(8) {
    digits[7-i] = x % 10;
    x /= 10;
  }
  FORI(8)
    cerr << " " << digits[i];
  cerr << endl;//*/    
}

int main() {
  set<Solution> allSolutions; // digits indicating row [1;8] for each column.

  // See base solutions at https://en.wikipedia.org/wiki/Eight_queens_puzzle
  int baseSolutions[12] = {24683175, 17468253, 17582463, 41582736,
                           51842736, 31758246, 51468273, 71386425,
                           51863724, 57142863, 63184275, 53172864};

  // Step 1: Build all solutions:
  FORI(12) {
    Solution base = baseSolutions[i];
    FORJ(4) {
      add(base, allSolutions);
      Solution flipH = flipHorizontal(base);
      add(flipH, allSolutions);
      Solution flipV = flipVertical(base);
      add(flipV, allSolutions);
      Solution flipVH = flipHorizontal(flipV);
      add(flipVH, allSolutions);
      
      base = rotate90(base);
    }
  }

  //cerr << "Should be 92: " << allSolutions.size() << endl;

  // Step 2: Solve!
  FORCAS {
    if(cas != 0)
      printf("\n");
    printf("SOLN       COLUMN\n");
    printf(" #      1 2 3 4 5 6 7 8\n\n");
    int cnt = 1;    
    int row, col;
    cin >> row >> col;

    FORIT(set<Solution>, allSolutions) {
      Solution x = *it;
      int digits[8];
      FORI(8) {
	digits[7-i] = x % 10;
	x /= 10;
      }
      if(digits[col-1] != row)
	continue;
      printf("%2d     ", cnt++);
      FORI(8)
	printf(" %d", digits[i]);
      printf("\n");
    }
  }
  return 0;
}
