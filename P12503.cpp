#include <iostream>
#include <stdio.h>

int main() {
  bool dirs[101];
  char line[100];
  int T, n, prev;
  std::cin >> T;

  for(int cas = 0; cas < T; ++cas) {
    std::cin >> n;
    int pos = 0;
    for(int i = 0; i < n; ++i) {
      std::cin >> line;
      if(line[0] == 'L') {
	dirs[i] = false;
	--pos;
      }
      else if(line[0] == 'R') {
	dirs[i] = true;
	++pos;
      }
      else {
	std::cin >> line >> prev;
	if(dirs[i] = dirs[prev-1])
	  ++pos;
	else
	  --pos;
      }	
    } // for directions
    std::cout << pos << std::endl;
  } // for case
}
