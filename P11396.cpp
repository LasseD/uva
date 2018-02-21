/*
V = 4
1 2
1 3
1 4
2 3
2 4
3 4
0 0

  2
 /|\
3-1-4
 \_/


V = 6
1 2
1 3
1 6
2 3
2 5
3 4
4 5
4 6
5 6

  2-5
 /| |\
1-3-4 |
 \ / /
  6_/


Example of OK input:

1     4
2 ALL 5
3     6



Decompose => bipartite with degree 3 on all nodes:
- Assume node is center of a claw: Degree 3 => All leafs must be leafs of any other claw (0, 1, or 2 other claws)!
- Assume node is leaf of a given claw: Must always be a leaf => any other is a center

bipartite with degree 3 on all nodes => decompose:
- Simply assign one side as centers, the other as leafs.

 */
#define MAXN 300

int main() {
  int colors[MAXN]; // 0 = unassigned, 1 = white, 2 = black
  vector<int> neighbours[MAXN];
  while(true) {
    GI(V);
    if(V == 0)
      return 0;
    FORI(V) {
      colors[i] = 0;
      neighbours[i].clear();
    }
    while(true) {
      GI(a); GI(b); --a; --b;
      if(a == -1 && b == -1)
	break;
      neighbours[a].push_back(b);
      neighbours[b].push_back(a);      
    }
    // Try bipartite coloring:
    colors[0] = 1;
    stack<int> q; q.push(0);
    bool ok = true;
    while(ok && !q.empty()) {
      int x = q.top(); q.pop();
      int color = colors[x];
      FORIT(vector<int>, neighbours[x]) {
	int n = *it;
	if(colors[n] == 0) {
	  colors[n] = 3-color;
	  q.push(n);
	}
	else if(colors[n] == color) {
	  ok = false;
	  break;
	}
      } // FORIT
    } // while ok && ...
    if(ok)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  } // while(true)
} // int main
