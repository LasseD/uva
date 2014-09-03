#include <iostream>
#include <stdio.h>

#define SIZE 5100

int main() {
  // read tree:
  int *tree = new int[3*SIZE];
  int *closest = new int[SIZE];
  int treeI = 0;

  while(true) {
    int a, b, c;
    std::cin >> a >> b >> c;
    if(a == 0 && b == 0 && c == 0)
      break;
    tree[3*treeI+0] = a;
    tree[3*treeI+1] = b;
    tree[3*treeI+2] = c;
    closest[treeI] = 20;
    ++treeI;
  }

  // construct lookup:
  int *root = new int[100];
  int rootI = 0;
  for(int i = 0; i < 100; ++i) {
    root[i] = rootI;
    //std::cerr << "root(" << i << ")=" << rootI << std::endl;
    if((rootI+1)*(rootI+1) == i+1) {
      ++rootI;
    }
  }

  // run!:
  for(int i = 0; i < treeI-1; ++i) {
    for(int j = i+1; j < treeI; ++j) {
      int da = tree[3*i]-tree[3*j];
      int db = tree[3*i+1]-tree[3*j+1];
      int dc = tree[3*i+2]-tree[3*j+2];
      int distSq = da*da + db*db + dc*dc;
      if(distSq >= 100) {
	continue;
      }
      const int dist = root[distSq];
      //std::cerr << "distSq: " << distSq << " -> " << dist << ", from " << closest[i] << "/" << closest[j] << std::endl;

      if(closest[i] > dist)
	closest[i] = dist;
      if(closest[j] > dist)
	closest[j] = dist;
    }
  }

  // count and write:
  int distCounters[10];
  for(int i = 0; i < 10; ++i) {
    distCounters[i] = 0;
  }
  for(int i = 0; i < treeI; ++i) {
    int dist = closest[i];
    if(dist < 10)
      ++distCounters[dist];
  }
  for(int i = 0; i < 10; ++i) {
    printf("%4i", distCounters[i]);
  }
  printf("\n");

  delete[] tree;
  delete[] closest;
  delete[] root;
}
