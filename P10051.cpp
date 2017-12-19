struct Cube {
  int colors[6];
};

#define CUBE first
#define SIDE second

typedef PI Info;
typedef map<int,vector<Info> > MAP;

int main() {
  string sides[6] = {"front","back","left","right","top","bottom"};
  
  Cube cubes[500];
  vector<Info> stacks[100]; // One for each color.
  
  for(int cas = 1; true; ++cas) {
    // Reset:
    FORI(100)
      stacks[i].clear();
    
    // Read data:
    GI(N); if(N == 0) return 0;

    FORI(N) {
      FORJ(6) {
	cin >> cubes[N-1-i].colors[j]; --cubes[N-1-i].colors[j]; // 0-index
      }
    }
    // Cubes are now sorted heavy -> light.
    int tallestHeight = 0;
    int tallestColor;
    
    FORI(N) { // Add each cube:
      Cube &cube = cubes[i];
      MAP toAdd;
      FORJ(6) {
	int topColor = cube.colors[j];
	int bottomColor = cube.colors[(j%2 == 0 ? j+1 : j-1)];
	int newHeight = stacks[bottomColor].size()+1;
	if(stacks[topColor].size() < newHeight) {
	  if(toAdd.find(topColor) != toAdd.end() && toAdd[topColor].size() >= newHeight)
	    continue; // Already have a better one.
	  toAdd[topColor] = stacks[bottomColor];
	  toAdd[topColor].push_back(Info(N-i, j));
	}
      }
      // Update using "toAdd":
      FORIT(MAP, toAdd) {
	stacks[it->first] = it->second;
	if(tallestHeight < it->second.size()) {
	  tallestHeight = it->second.size();
	  tallestColor = it->first;
	}	  
      }
    }
    // Output best tower:
    if(cas != 1)
      cout << endl;
    cout << "Case #" << cas << endl;
    cout << tallestHeight << endl;
    for(vector<Info>::reverse_iterator it = stacks[tallestColor].rbegin(); it != stacks[tallestColor].rend(); ++it) {
      cout << it->CUBE << " " << sides[it->SIDE] << endl;
    }
  } // for cas
} // int main
