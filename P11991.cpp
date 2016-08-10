#include <iostream>
#include <stdio.h>
#include <map>

typedef std::pair<int,int> PP;
typedef std::map<PP,int> Map;

int main() {
  int *a = new int[1000001];
  int n, m, x, y;
  while(std::cin >> n >> m) {
    Map map;
    for(int i = 1; i <= n; ++i) {
      std::cin >> x;
      if(map.find(PP(x, 1)) == map.end()) {
	map.insert(std::make_pair(PP(x, 1), i));
	a[x] = 1;
      }
      else {
	++a[x];
	map.insert(std::make_pair(PP(x, a[x]), i));	
      }
    }
    // queries:
    for(int i = 0; i < m; ++i) {
      std::cin >> x >> y;
      if(map.find(PP(y, x)) != map.end()) {
	std::cout << map[PP(y, x)] << std::endl;
      }
      else {
	std::cout << 0 << std::endl;
      }
    }
  }
  return 0;
}
