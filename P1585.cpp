#include <iostream>
#include <cstdlib>

int main() {
  char line[83];
  std::cin.getline(line, 83);
  int lines = atoi(line);
  for(int ignore = 0; ignore < lines; ++ignore) {
    std::cin.getline(line, 83);
    int res = 0;
    int bonus = 0;
    for(int i = 0; true; ++i) {
      if(line[i] == 'O') {
	++bonus;
	res+=bonus;
      }
      else if(line[i] == 'X') {
	bonus = 0;
      }
      else
	break;
    }
    std::cout << res << std::endl;
  }
  return 0;
}
