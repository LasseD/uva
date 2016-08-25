#include <iostream>
#include <stdio.h>
#include <cstring>

char iToC(int a) {
  switch(a) {
  case 0:
    return ' ';
  case 1:
    return '.';
  case 2:
    return 'x';
  default:
    return 'W';
  }
}

int main() {
  int cases, dnaProgram[10], dishes[40], nextDishes[40];
  char line[41];
  line[40] = '\0';
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      puts("");

    for(int i = 0; i < 10; ++i)
      std::cin >> dnaProgram[i];
    for(int i = 0; i < 40; ++i)
      dishes[i] = 0;
    dishes[19] = 1;
    //memset(dishes, 1, 40*sizeof(int));

    for(int y = 0; y < 50; ++y) {
      // Writeout:
      for(int i = 0; i < 40; ++i)
	line[i] = iToC(dishes[i]);
      puts(line);

      // Update dishes:
      nextDishes[0] = dnaProgram[dishes[0]+dishes[1]];
      nextDishes[39] = dnaProgram[dishes[39]+dishes[38]];
      for(int i = 1; i < 39; ++i)
	nextDishes[i] = dnaProgram[dishes[i-1]+dishes[i]+dishes[i+1]];
      for(int i = 0; i < 40; ++i)
	dishes[i] = nextDishes[i];
    }
  }
  return 0;
}
