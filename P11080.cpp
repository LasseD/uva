#define EMPTY 0
#define GUARD 1
#define NOGUARD 2

bool run(int i, int color, int &g, int &ng, vector<int> *a, int *colors) {
  //cerr << "Coloring " << i << " " << color << endl;
  if(colors[i] != EMPTY)
    return colors[i] == color;

  if(color == GUARD)
    ++g;
  else
    ++ng;
  colors[i] = color;
  int neighbourColor = 3-color;
  FORIT(vector<int>, a[i]) {
    if(colors[*it] == EMPTY) {
      if(!run(*it, neighbourColor, g, ng, a, colors))
	return false;
    }
    if(colors[*it] == color)
      return false;
  }
  return true;
}

int main() {
  vector<int> adjacent[201];
  int colors[201];
  FORCAS {
    int vertices, edges, s, t; cin >> vertices >> edges;
    FORI(vertices) {
      adjacent[i].clear();
      colors[i] = EMPTY;
    }
    FORI(edges) {
      cin >> s >> t;
      adjacent[s].push_back(t);
      adjacent[t].push_back(s);
    }
    int ret = 0;
    int numGuards = 0;
    int numNoGuards = 0;
    FORI(vertices) {
      if(colors[i] == EMPTY) {
	int tmpG = numGuards, tmpNG = numNoGuards;
	if(!run(i, GUARD, numGuards, numNoGuards, adjacent, colors)) {
	  ret = -1;
	  break;
	}
	int addG = numGuards-tmpG;
	int addNG = numNoGuards-tmpNG;
	ret += MAX(1, MIN(addG, addNG));
      }
    }
    cout << ret << endl;
  }
  return 0;
}
