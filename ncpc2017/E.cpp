#include<iostream>
#include<vector>
#include<algorithm>
#include <set>

using namespace std;

#define MAX(a,b) ((a) < (b) ? (b) : (a))

typedef long long LL;
typedef pair<int,int> PI;
typedef pair<int,PI> PII;

int h,w;
bool visited[501][501];
int altitude[501][501];
//LL waterTaken[501][501];

LL waterDrained=0;

bool check(int i,int j){
  if(i<0 || j<0) return false;
  if(i>=h || j >=w) return false;
  return true;
}

void flow(int i, int j, LL minDepth){
  visited[i][j] = true;

  /*
  if(!check(i,j)) return;
  
  LL currentDepth= altitude[i][j];
  
  if(currentDepth>=0) return;

  LL possible = -1*MAX(currentDepth,minDepth);
  

 
  if(waterTaken[i][j]<possible){
    waterDrained = waterDrained + possible - waterTaken[i][j];
    waterTaken[i][j]= possible; 
  }
  else{
    return;
  }

  LL a= MAX(minDepth,altitude[i][j]);
  */


	/*
  flow(i-1,j-1,a);
  flow(i-1,j,a);
  flow(i-1,j+1,a);

  flow(i,j-1,a);
  flow(i,j+1,a);

  flow(i+1,j-1,a);
  flow(i+1,j,a);
  flow(i+1,j+1,a);*/
}

int main(){
  cin >> h >> w;

  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      visited[i][j] = false;
      cin >> altitude[i][j];
    }
  }

  int i,j;
  cin >> i >> j;

  set<PII> PQ;
  PQ.insert(PII(altitude[i-1][j-1], PI(i-1, j-1)));
  while(!PQ.empty()) {
    PII t = *PQ.begin();
    PQ.erase(t);
    int a = t.first;
    i = t.second.first;
    j = t.second.second;
    if(visited[i][j])
      continue;
    //cerr << "Adding " << -a << " from (" << i << "," << j << ") at " << a << endl;
    waterDrained -= a;
    visited[i][j] = true;

    for(int x = i-1; x <= i+1; ++x) {
      for(int y = j-1; y <= j+1; ++y) {
	if(x == i && y == j)
	  continue;
	if(!check(x, y) || visited[x][y] || altitude[x][y] > 0)
	  continue;
	int possible = MAX(altitude[x][y], a);	
	PQ.insert(PII(possible, PI(x, y)));
      }
    }
  }
  //  flow(i-1,j-1,altitude[i-1][j-1]);

  cout << waterDrained << endl;
}

