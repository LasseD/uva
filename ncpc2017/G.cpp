#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef pair<int,int> PI; // -solved, penalty
typedef pair<PI,int> TEAM; // -solved, penalty

int main() {
  int N, M;
  cin >> N >> M;

  vector<PI> teams(N); // -solved,penalty
  set<TEAM> better;

  for(int k = 0; k < M; ++k) {
    int a, b;
    cin >> a >> b;

    if(a == 1) {
      // Update team:
      teams[a-1].first--;
      teams[a-1].second+=b;
      // Remove from better set
      while(!better.empty() && teams[0] <= better.rbegin()->first) {
	better.erase(*better.rbegin());
      }
    }
    else {
      bool alreadyInSet = teams[a-1] < teams[0];
      if(alreadyInSet) {
	better.erase(TEAM(teams[a-1], a-1));
      }

      // Update team:
      teams[a-1].first--;
      teams[a-1].second+=b;
      if(teams[a-1] < teams[0]) {
	better.insert(TEAM(teams[a-1], a-1));
      }
    }
    cout << 1+better.size() << endl;
  }
  return 0;
}
