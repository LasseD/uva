#include <iostream>

unsigned int readUInt() {
  unsigned int ret = 0;

  char w[20];
  std::cin.getline(w, 20);
  for(int i = 0; i < 20; ++i) {
    if(!(w[i] >= '0' && w[i] <= '9'))
      break;
    ret = ret * 10 + (w[i]-'0');
  }
  return ret;
}

unsigned long space(unsigned int lines) {
  unsigned int minSpace = 100;
  unsigned long spaceTotal = 0;

  char w[30];
  for(unsigned int line = 0; line < lines; ++line) {
    std::cin.getline(w, 30);
    unsigned long spaceOnLine = 0;
    for(int i = 0; i < 25; ++i) {
      if(w[i] != 'X')
	++spaceOnLine;
    }
    spaceTotal += spaceOnLine;
    if(spaceOnLine < minSpace)
      minSpace = spaceOnLine;
  }
  return spaceTotal - minSpace*lines;
}

int main() {
  while(true) {
    unsigned int lines = readUInt();
    if(lines == 0)
      return 0;
    std::cout << space(lines) << std::endl;
  }
}
