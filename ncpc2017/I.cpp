#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

vector<vector<int> > graph(501);
bool marked[501];
int path[501], bestPath[501];

void dfs(int dest, int cur, int &pathI, int &bestPathSize) {
  if(pathI+1 >= bestPathSize)
    return;

  marked[cur] = true;
  path[pathI++] = cur;
  for(vector<int>::const_iterator it = graph[cur].begin(); it != graph[cur].end(); ++it) {
    int neighbour = *it;
    //cerr << "Walk " << cur << "->" << neighbour << endl;
    if(dest == neighbour) {
      //cerr << "Found best path size " << pathI << endl;
      // UPDATE!
      if(pathI < bestPathSize) {
	// Update best path!
	for(int i = 0; i < pathI; ++i) {
	  bestPath[i] = path[i];
	}
	bestPathSize = pathI;
      }
      break;
    }
    if(marked[neighbour]) {
      //cerr << "Marked " << neighbour << endl;
      continue;
    }
    dfs(dest, neighbour, pathI, bestPathSize);
  }
  --pathI;
}



int main() {
  string line;

  getline(cin, line);
  stringstream ss1; ss1 << line;
  int n, k;
  ss1 >> n;

  map<string,int> m;
  string names[501], name;

  getline(cin, line);
  stringstream ss2; ss2 << line;
  
  for(int i = 0; i < n; ++i) {
    ss2 >> names[i];
    m[names[i]] = i;
  }
  for(int i = 0; i < n; ++i) {
    getline(cin, line);
    stringstream ss3; ss3 << line;
    ss3 >> name >> k;
    for(int j = 0; j < k; ++j) {
      getline(cin, line);
      //cerr << "Line read: " << line << endl;
      for(unsigned int x = 0; x < line.size(); ++x) {
	if(line[x] == ',')
	  line[x] = ' ';
      }
      stringstream ss; ss << line;
      ss >> line; // import
      while(ss >> name) {
	graph[i].push_back(m[name]);
	//cerr << j << "->" << m[name] << endl;
      }
    }
  }
  
  int bestPathSize = 999;
  for(int i = 0; i < n; ++i) {
    int pathSize = 0;
    //cerr << "START " << i << endl;
    for(int j = 0; j < n; ++j) {
      marked[j] = false;
    }
    dfs(i, i, pathSize, bestPathSize);
  }
  if(bestPathSize == 999)
    cout << "SHIP IT" << endl;
  else {
    cout << names[bestPath[0]];
    for(int i = 1; i < bestPathSize; ++i)
      cout << " " << names[bestPath[i]];
    cout << endl;
  }
  return 0;
}
