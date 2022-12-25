typedef pair<PI,char> Blizzard;

string M[30];
Blizzard blizzards[2800];
PI pos[5] = {PI(0,0),PI(-1,0),PI(1,0),PI(0,-1),PI(0,1)};

int main() {
  int height = 1, width, startX = -1, endX = -1;
  set<PI> me, me2;
  
  // Parse input:
  string s;

  cin >> s;
  M[0] = s;
  width = (int)s.size();
  FORI(width) {
    if(s[i] == '.') {
      me.insert(PI(i,0));
      M[0][i] = 'E';
      break;
    }
  }
  FORI(width) {
    if(s[i] == '.') {
      startX = i;
      break;
    }
  }

  bool done = false;
  int bi = 0;
  while(!done) {
    cin >> s;
    M[height] = s;
    for(int i = 1; i < width-1; i++) {
      if(s[i] == '.')
	continue; // No blizzard
      if(s[i] == '#') {
	done = true;
	break; // Done!
      }
      blizzards[bi++] = Blizzard(PI(i,height),s[i]);
    }
    height++;
  }
  FORI(width) {
    if(s[i] == '.') {
      endX = i;
      break;
    }
  }
  
  cout << endl << endl << endl << "Read " << bi << " blizzards. Width: " << width << ", height: " << height << " startX=" << startX << ", endX=" << endX << endl;
  /*FORI(bi) {
    Blizzard &b = blizzards[i];
    cout << "Blizzard " << i << ": " << b.first.XX << "," << b.first.YY << " " << b.second << endl;
  }//*/
  int H2 = height-2, W2 = width-2;
  FORI(height) {
    cout << M[i] << endl;
  }

  // Simulate:
  int state = 0;
  for(int round = 0; true; round++) {
    // Clean board:
    for(int x = 1; x < width-1; x++) {
      for(int y = 1; y < height-1; y++) {
	M[y][x] = '.';
      }
    }
    M[0][startX] = '.';
    M[height-1][endX] = '.';

    // Move blizzards:
    FORI(bi) {
      Blizzard &b = blizzards[i];
      switch(b.second) {
      case 'v':
	b.first.YY = (b.first.YY+1-1)%H2+1;
	break;
      case '^':
	b.first.YY = (b.first.YY-1-1+H2)%H2+1;
	break;
      case '<':
	b.first.XX = (b.first.XX-1-1+W2)%W2+1;
	break;
      case '>':
	b.first.XX = (b.first.XX-1+1)%W2+1;
	break;
      default:
	cerr << "Unknown direction " << b.second << endl;
	die();
      }
      // Mark the map:
      char &c = M[b.first.YY][b.first.XX];
      if(c == '.')
	c = b.second;
      else if(c >= '2' && c <= '9')
	c++;
      else
	c = '2';
    }
    
    // Wind out where we can be:
    me2.clear();
    bool stateTransitioned = false;
    FORIT(set<PI>, me) {
      PI p = *it;
      FORI(5) {
	int x2 = p.XX + pos[i].XX, y2 = p.YY + pos[i].YY;
	if(y2 < 0 || y2 >= height || M[y2][x2] != '.')
	  continue; // Out of bounds or blizzard.
	if(y2 == height-1) {
	  if(state == 0) {
	    state++;
	    cout << "Answer 1: " << (round+1) << endl;
	    me2.clear();
	    stateTransitioned = true;
	  }
	  else if(state == 2) {
	    cout << "Answer 2: " << (round+1) << endl;
	    return 0;
	  }
	}
	if(y2 == 0 && state == 1) {
	  state++;
	  me2.clear();
	  stateTransitioned = true;
	}
	if(M[y2][x2] == '.') {
	  me2.insert(PI(x2,y2));
	  M[y2][x2] = 'E';
	}
	if(stateTransitioned) {
	  break;
	}
      } // FORI 5
      if(stateTransitioned) {
	break;
      }
    } // FORIT me
    swap(me, me2);
    /*
    cout << "Map after minute " << (round+1) << ", state " << state << endl;
    FORI(height) {
      cout << M[i] << endl;
    }//*/
    if(me.empty()) {
      cerr << "No moves!" << endl;
      return 1;
    }
    cout << "Round " << round << ": " << me.size() << " positions" << endl;
  } // for rounds
}
