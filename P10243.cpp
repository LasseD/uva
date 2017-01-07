#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void die() {
  return;
  int *a = NULL;
  a[2] = 3;
}

int main() {
  bool colored[1000], handled[1000];
  int numberOfNeighbours[1000];
  vector<int> adjacencyList[1000];

  while(true) {
    int n, len, dest;
    cin >> n;
    if(n == 0)
      return 0;
    for(int i = 0; i < n; ++i) {
      colored[i] = handled[i] = false;
      adjacencyList[i].clear();
    }

    stack<int> s; // Ready stack :)
    for(int i = 0; i < n; ++i) {
      cin >> len;
      numberOfNeighbours[i] = len;
      if(len == 1)
	s.push(i);
      if(len == 0)
	die();
      for(int j = 0; j < len; ++j) {
	cin >> dest;
	--dest;
	adjacencyList[i].push_back(dest);
      }
    }

    int numHandled = 0;
    int ret = 0;
    if(n == 1)
      ret = 1;
    while(!s.empty()) {
      int t = s.top();
      s.pop();
      if(handled[t])
	continue;
      handled[t] = true;
      ++numHandled;

      int neighbour = -1; // Find the unhandled neighbour:
      for(vector<int>::iterator it = adjacencyList[t].begin(); it != adjacencyList[t].end(); ++it) {
	if(!handled[*it]) {
	  neighbour = *it;
	  break;
	}
      } // for iterator
      if(neighbour == -1)
	continue;

      --numberOfNeighbours[neighbour];
      if(numberOfNeighbours[neighbour] == 1)
	s.push(neighbour);
      
      if(!colored[t] && !colored[neighbour]) {
	//cerr << "Coloring " << neighbour << endl;
	colored[neighbour] = true;
	++ret;
      }
    } // while(!s.empty())
    if(numHandled != n)
      die();
    cout << ret << endl;
  } // while(true)
}
