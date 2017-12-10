#define MARKED 1
#define OUTER 2

string a[40];
char border;
int height;

bool isLimiter(string &s) {
  return s[0] == '_';
}

bool getFill(int x, int y, char &f) {
  if(x < 0 || y < 0 || y >= height - 1 || x >= (int)a[y].size())
    return false; // out of bounds
  char c = a[y][x];
  if(c == ' ') {
    a[y][x] = MARKED;
    return getFill(x-1, y, f) || getFill(x, y-1, f) || getFill(x+1, y, f) || getFill(x, y+1, f);
  }
  else if(c != border && c != MARKED) {
    f = c;
    return true;
  }
  else
    return false;
}

void fill(int x, int y, char f) {
  if(x < 0 || y < 0 || y >= height - 1 || x >= (int)a[y].size())
    return; // out of bounds
  //cerr << "F(" << x << "," << y << ")";
  char c = a[y][x];
  if(c == ' ' || c == MARKED) {
    a[y][x] = f;
    fill(x-1, y, f);
    fill(x, y-1, f); 
    fill(x+1, y, f);
    fill(x, y+1, f);
  }
}

void run(int x, int y) {
  char c = a[y][x];
  if(c != ' ' || c == border)
    return; // Don't run for borders, and don't run on space.
  char f;
  if(!getFill(x, y, f))
    f = OUTER;
  //cerr << "Fill found at " << x << ","  << y << ". Fill: " << (int)f << endl;
  fill(x, y, f);
}

int main() {
  while(true) {
    height = 0;
    while(getline(cin, a[height++])) {
      if(isLimiter(a[height-1]))
	break;
    }
    if(height <= 1)
      return 0;
    // Find border char:
    border = ' ';
    FORI(height-1) {
      FORUJ(a[i].size()) {
	char c = a[i][j];
	if(isprint(c) && c != ' ') {
	  border = c;
	  break;
	}
      }
    }
    // Fill:
    if(border != ' ') {
      FORY(height-1) {
	FORUX(a[y].size())
	  run(x, y);
      }
    }
    // Print:
    FORI(height) {
      if(i < height-1) {
	// Reset '_':
	FORUJ(a[i].size())
	  if(a[i][j] == OUTER)
	    a[i][j] = ' ';
      }
      cout << a[i] << endl;
    }
  }
}
