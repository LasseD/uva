#include <iostream>
#include <stdio.h>

unsigned int readUInt() {
  unsigned int ret = 0;

  char w[20];
  std::cin.getline(w, 20);
  for(int i = 0; i < 20; ++i) {
    if(!(w[i] >= '0' && w[i] <= '9'))
      break;
    ret = ret * 10 + (w[i]-'0');
  }
  std::cerr << ret << " lines" << std::endl;
  return ret;
}

bool lineLoops() {
  char w[200];
  std::cin.getline(w, 200);
  int diff = 0;
  int cnt = 0;

  for(int i = 0; true; ++i) {
    if(w[i] == ' ')
      continue;
    if(w[i] == 'M') {
      ++diff;
      ++cnt;
    }
    else if(w[i] == 'F') {
      --diff;
      ++cnt;
    }
    else {
      return diff == 0 && cnt > 2;
    }
  }
}

int main() {
  int lines = readUInt();

  for(int ignore = 0; ignore < lines; ++ignore) {
    if(lineLoops())
      printf("LOOP\n");
    else
      printf("NO LOOP\n");
  }

  return 0;
}
