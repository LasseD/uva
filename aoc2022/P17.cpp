#include <bitset>

#define WIDTH 7
// Choose the right define for task a and b:
//#define ITERATIONS 2022
#define ITERATIONS 1000000000000
                // 1.000.000.000.000

int jetIdx = 0;
string jets;
bitset<100000> cave[WIDTH];

int nextJet() {
  int ret = (jets[jetIdx++] == '>') ? 1 : -1;
  if(jetIdx == (int)jets.size()) {
    jetIdx = 0;
  }
  //cout << " Jet " << ret << endl;
  return ret;
}

string rocks[5][4] = {
  {"####","","",""},
  {" # ",
   "###",
   " # ",""},
  {"  #",
   "  #",
   "###",""},
  {"#","#","#","#"},
  {"##","##","",""}
};
int heights[5] = {1,3,3,4,2};
int  widths[5] = {4,3,3,1,2};

bool checkRow(int x, LL y, string &row) {
  FORI((int)row.size()) {
    if(row[i] == '#' && cave[i+x][y]) {
      //cout << "Rock colission at " << (i+x) << "," << y << endl;
      return false;
    }
  }
  return true;
}

bool checkRock(int x, LL y, LL idx) {
  string *rock = rocks[idx%5];
  int rockHeight = heights[idx%5];
  FORI(rockHeight) {
    if(!checkRow(x, y-i, rock[i])) {
      return false;
    }
  }
  return true;
}

LL height = 0;

bool blocked() {
  FORI(WIDTH) {
    if(!(cave[i][height-3] || cave[i][height-4])) {
      return false;
    }
  }
  return true;
}

void printCave(LL max) {
  cout << "Cave height " << height << endl;
  FORI(min(height,max)) {
    cout << "|";
    FORJ(WIDTH) {
      cout << (cave[j][height-i-1] ? '#' : ' ');
    }
    cout << "|" << endl;
  }
  cout << "+";
  FORJ(WIDTH) {
    cout << ".";
  }
  cout << "+";
  cout << endl;
}

int main() {
  map<LL,PLL> states; // Blocked -> iteration, height
  bool skipped = false;
  
  cin >> jets;
  cout << "Jet cycle: " << jets.size() << endl;

  FORI(WIDTH) {
    cave[i].reset(); // All 0
  }

  // Check rock types:
  /*
  FORI(5) {
    string *rock = rocks[i];
    FORJ(heights[i]) {
      cout << rock[j] << endl;
    }
    cout << endl;
  }//*/

  // Run simulation:
  cout << "Running " << ITERATIONS << " iterations" << endl;
  LL heightAdd = 0;
  for(LL i = 0; i < ITERATIONS; i++) { // 2022
    string *rock = rocks[i%5];
    int rockHeight = heights[i%5];
    int rockWidth = widths[i%5];
    //cout << "Rock " << i << " falling with size " << rockWidth << " x " << rockHeight << endl;
    int x = 2;
    LL y = height + 2 + rockHeight;
    // Simulate falling:
    while(true) {
      //cout << "Rock " << i << " at " << x << "," << y << endl;
      // Move with jet:
      int x2 = x + nextJet();
      //cout << " x2: " << x2 << endl;
      bool x2ok = (x2 >= 0) && (x2+rockWidth <= WIDTH) && checkRock(x2, y, i);
      if(x2ok) {
	x = x2;
      }
      //cout << " After jet " << x << "," << y << endl;
      // Move down:
      int y2 = y-1;
      bool y2ok = y2-rockHeight+1 >= 0 && checkRock(x, y2, i);
      if(y2ok) {
	y = y2;
      }
      else {
	break;
      }
    } // while true

    // Update cave
    //cout << "Rock " << i << " landed at " << x << "," << y << endl;
    FORJ(rockHeight) {
      FORK(rockWidth) {
	if(rock[j][k] == '#') {
	  cave[k+x].set(y-j, true);
	  //cout << " Set bit at " << (k+x) << "," << (y-j) << endl;
	}
      }
    }

    height = max(height, y+1);

    //printCave(20);

    if(!skipped && height > 10 && blocked()) {
      cout << "BLOCK! iteration " << i << " height " << height << " rock " << (i%5) << " jet " << jetIdx << endl;
      //printCave(10);
      
      // Compute hash for state (cave + rock + jet):
      LL state = 0;
      FORJ(4) {
	FORK(WIDTH) {
	  state = 2*state + (cave[k][height-1-j] ? 1 : 0);
	}
      }
      state = 1000000*state + jetIdx; // Include jet index into state
      state = 10*state + (i%5); // Include rock into state

      if(states.find(state) == states.end()) { // New state to store:
	states[state] = PLL(i, height);
      }
      else {
	cout << "STATE FOUND! iteration " << i << endl;
	LL remainingIterations = ITERATIONS-i;
	cout << " Remaining iterations: " << remainingIterations << endl;
	PLL oldState = states[state];
	LL iterationsGap = i-oldState.first;
	cout << " Iterations gap: " << iterationsGap << endl;
	LL heightGap = height-oldState.second;
	cout << " height gap: " << heightGap << endl;
	LL blocksToSkip = remainingIterations/iterationsGap-9;

	cout << " Blocks to skip " << blocksToSkip << endl;
	LL iterationsToSkip = iterationsGap * blocksToSkip;
	cout << "Skip " << iterationsToSkip << " iterations" << endl;

	heightAdd = heightGap * blocksToSkip;
	i += iterationsToSkip;
	cout << "Continuing from iteration " << i << endl;
	
	skipped = true;
      }
    } // SKIP
    
  } // FORI 2022

  //printCave();
  
  cout << endl << "Answer: " << height << "+" << heightAdd << " = " << (height+heightAdd) << endl;
  // Learning: Remember that type int is really, really small...
  return 0;
} // int main
