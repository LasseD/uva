int main() {
  string v[102], s;
  int height = 0, width;
  while(cin >> s) {
    v[height] = s;
    height++;
  }
  width = (int)v[0].size();
  cout << "Read map " << width << " x " << height << endl;
  PI neighbours[4] = {PI(-1,0), PI(1,0), PI(0,1), PI(0,-1)};

  int answer1 = 0;
  vector<int> basins;
  set<PI> allBasins;
  
  FORY(height) {
    FORX(width) {
      char h = v[y][x];
      bool allHigher = true;
      FORI(4) {
	const PI &p = neighbours[i];
	int xx = x+p.XX;
	int yy = y+p.YY;
	if(xx >= 0 && yy >= 0 && xx < width && yy < height) {
	  if(v[yy][xx] <= h) {
	    allHigher = false;
	    break;
	  }
	}
      }
      if(allHigher) {
	cout << "LOW " << x << ", " << y << endl;
	answer1 += h+1-'0';

	if(allBasins.find(PI(x,y)) != allBasins.end())
	  continue; // Already seen basin.

	// Compute basin:
	stack<PI> ready;
	set<PI> basin;
	ready.push(PI(x,y));
	while(!ready.empty()) {
	  PI p = ready.top(); ready.pop();
	  if(basin.find(p) != basin.end())
	    continue; // Already seen
	  basin.insert(p);
	  allBasins.insert(p);
	  FORI(4) {
	    const PI &q = neighbours[i];
	    int xx = p.XX+q.XX;
	    int yy = p.YY+q.YY;
	    if(xx >= 0 && yy >= 0 && xx < width && yy < height) {
	      if(v[yy][xx] != '9') {
		ready.push(PI(xx,yy));
	      }
	    }
	  }
	}
	cout << "Basin of size " << basin.size() << endl;
	basins.push_back(basin.size());
      }
    } // FORX width
  } // FORY height
  sort(basins.begin(), basins.end());
  LL answer2 = basins[basins.size()-1] * basins[basins.size()-2] * basins[basins.size()-3];
  cout << answer1 << endl;
  cout << answer2 << endl;
}
