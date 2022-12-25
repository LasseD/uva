// Input size 75x75
#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3

char toDir(int i) {
  switch(i) {
  case NORTH:
    return 'N';
  case SOUTH:
    return 'S';
  case WEST:
    return 'W';
  case EAST:
    return 'E';
  }
  return '?';
}

struct Elve {
  PI pos, next;
  //int dirs[4];
  bool willMove;
};

Elve* M[4000][4000];
vector<Elve*> elves;  

void print() {
  int miX = 20000, miY = 20000, maX = -200, maY = -200;
  FORIT(vector<Elve*>, elves) {
      Elve* elve = *it;
      int x = elve->pos.XX;
      int y = elve->pos.YY;
      miX = min(miX, x);
      miY = min(miY, y);
      maX = max(maX, x);
      maY = max(maY, y);
  }
  long empty = 0;
  for(int y = miY; y<=maY; y++) {
    for(int x = miX; x <= maX; x++) {
      Elve *elve = M[y][x];
      if(elve == NULL) {
	empty++;
	cout << ".";
      }
      else {
	cout << "#";
      }
    }
    cout << endl;
  }
  cout << empty << " empty fields" << endl;
}

int main() {
  // Parse input:
  int y = 2000;
  string line;
  while(cin >> line) {
    int x = 2000;
    FORUI(line.size()) {
      if(line[i] == '#') {
	Elve *e = new Elve();
	e->pos = PI(x,y);
	M[y][x] = e;
	elves.push_back(e);
      }
      x++;
    }
    y++;
  }
  cout << "Read " << elves.size() << " elves. Initial grid:" << endl;
  print();

  for(int i = 0; true; i++) { // Part 1: Simulate 10 rounds:
    vector<PI> destinations;
    int moves = 0;
    
    // Firt half: Propose direction:
    FORIT(vector<Elve*>, elves) {
      Elve* elve = *it;
      int x = elve->pos.XX, y = elve->pos.YY;
      elve->willMove = false;

      // Check if not neighbours:
      bool allFree = true;
      for(int xx = x-1; xx <= x+1; xx++) {
	for(int yy = y-1; yy <= y+1; yy++) {
	  if(xx==x && yy==y)
	    continue;
	  if(M[yy][xx] != NULL) {
	    allFree = false;
	    break;
	  }
	}
      }
      if(allFree) {
	continue; // No move.
      }

      FORJ(4) {
	int dir = (j+i)%4;
	PI spots[3];
	switch(dir) {
	case NORTH:
	  spots[0] = PI(x-1,y-1);
	  spots[1] = PI(x,  y-1);
	  spots[2] = PI(x+1,y-1);
	  break;
	case SOUTH:
	  spots[0] = PI(x-1,y+1);
	  spots[1] = PI(x,  y+1);
	  spots[2] = PI(x+1,y+1);
	  break;
	case WEST:
	  spots[0] = PI(x-1,y+1);
	  spots[1] = PI(x-1,y);
	  spots[2] = PI(x-1,y-1);
	  break;
	case EAST:
	  spots[0] = PI(x+1,y-1);
	  spots[1] = PI(x+1,y);
	  spots[2] = PI(x+1,y+1);
	  break;
	}
	bool ok = true;
	FORK(3) {
	  if(M[spots[k].YY][spots[k].XX] != NULL) {
	    ok = false;
	    break;
	  }
	}
	if(ok) {
	  elve->willMove = true;
	  elve->next = spots[1];
	  destinations.push_back(elve->next);
	  moves++;

	  //cout << "Proposal: " << x <<","<<y<<" -> "<<elve->next.XX<<","<<elve->next.YY<<" NEW DIRS " << toDir(elve->dirs[0]) << " " <<toDir(elve->dirs[1]) << " " <<toDir(elve->dirs[2]) << " " <<toDir(elve->dirs[3]) << endl;
	  break; // FORJ 4
	}
      } // FORJ 4 directions
    } // FORIT elves

    // Find elves that should not move:
    sort(destinations.begin(), destinations.end());
    set<PI> noMove;
    for(int j = 1; j < (int)destinations.size(); j++) {
      if(destinations[j] == destinations[j-1]) {
	noMove.insert(destinations[j]);
      }
    }
    FORIT(vector<Elve*>, elves) {
      Elve* elve = *it;
      if(!elve->willMove) {
	continue; // Not moving.
      }
      PI p = elve->next;
      if(noMove.find(p) != noMove.end()) {
	elve->willMove = false;
	moves--;
      }
    }

    if(moves == 0) {
      cout << "No moves from round " << (i+1) << endl;
      return 0;
    }

    // Second half: Move
    FORIT(vector<Elve*>, elves) {
      Elve* elve = *it;
      if(!elve->willMove) {
	continue; // Not moving.
      }
      PI from = elve->pos;
      PI to = elve->next;
      M[to.YY][to.XX] = elve;
      M[from.YY][from.XX] = NULL;
      elve->pos = elve->next;
    }

    //cout << "Grid after " << (i+1) << " rounds:" << endl;
    //xsprint();
  } // FORI 10 rounds
}
