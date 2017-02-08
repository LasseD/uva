#define EMPTY -1
#define WALL -2

void add(int x, int y, int H, int W, int *grid, vector<PI> &v, int time) {
  if(x < 0 || y < 0 || x >= W || y >= H) {
    return; // Out of bounds.
  }
  if(grid[y*1000+x] == EMPTY)
    v.push_back(PI(x,y));
  else if(grid[y*1000+x] != WALL && grid[y*1000+x] > time)
    v.push_back(PI(x,y));
}

void spread(const vector<PI> &start, int *grid, const int H, const int W) {
  int wave = 0;
  vector<PI> v;
  FORIT(vector<PI>, start)
    v.push_back(*it);

  while(!v.empty()) {
    vector<PI> v2;
    FORIT(vector<PI>, v) {
      PI pos = *it;
      if(grid[pos.YY*1000+pos.XX] != EMPTY)
	continue; // already set.
      grid[pos.YY*1000+pos.XX] = wave;
      //cerr << pos.XX << "," << pos.YY << ": " << wave << endl;
      add(pos.XX-1, pos.YY, H, W, grid, v2, -1);
      add(pos.XX+1, pos.YY, H, W, grid, v2, -1);
      add(pos.XX, pos.YY-1, H, W, grid, v2, -1);
      add(pos.XX, pos.YY+1, H, W, grid, v2, -1);
    }
    ++wave;
    v = v2;
  }
}
int possible(const PI &joe, int *grid, const int H, const int W) {
  int wave = 0;
  vector<PI> v;
  grid[joe.YY*1000+joe.XX] = 1000; // can't get Joe :)
  v.push_back(joe);

  while(!v.empty()) {
    vector<PI> v2;
    FORIT(vector<PI>, v) {
      PI pos = *it;
      if(grid[pos.YY*1000+pos.XX] == WALL)
	continue; // already handled.
      if(pos.XX == 0 || pos.YY == 0 || pos.XX == W-1 || pos.YY == H-1)
	return wave; // out!
      grid[pos.YY*1000+pos.XX] = WALL; // safe!
      //cerr << pos.XX << "," << pos.YY << ": " << wave << endl;
      add(pos.XX-1, pos.YY, H, W, grid, v2, wave+1);
      add(pos.XX+1, pos.YY, H, W, grid, v2, wave+1);
      add(pos.XX, pos.YY-1, H, W, grid, v2, wave+1);
      add(pos.XX, pos.YY+1, H, W, grid, v2, wave+1);
    }
    ++wave;
    v = v2;
  }
  return -1; // no escape :(
}

int main() {
  int W, H, *grid;
  grid = new int[1001001];
  string line;
  PI joe;
  FORCAS {
    // Read input:
    cin >> H >> W;
    vector<PI> fire;
    FORY(H) {
      cin >> line;
      FORX(W) {
	switch(line[x]) {
	case '.':
	  grid[y*1000+x] = EMPTY;
	  break;
	case '#':
	  grid[y*1000+x] = WALL;
	  break;
	case 'F':
	  fire.push_back(PI(x,y));
	  grid[y*1000+x] = EMPTY;
	  break;
	case 'J':
	  joe = PI(x,y);
	  grid[y*1000+x] = EMPTY;
	  break;
	}
      }
    }
    /*
    cerr << "W=" << W << ", H=" << H << endl;
    FORY(H) {
      FORX(W) {
	cerr << " " << grid[y*1000+x];
      }
      cerr << endl;
    }//*/   

    // Break out the fire:
    spread(fire, grid, H, W);

    /*FORY(H) {
      FORX(W) {
	cerr << " " << grid[y*1000+x];
      }
      cerr << endl;
    }//*/

    int ret = possible(joe, grid, H, W);
    if(ret < 0)
      cout << "IMPOSSIBLE" << endl;
    else
      cout << ret+1 << endl;
  }
  return 0;
}
