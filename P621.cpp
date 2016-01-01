#include <iostream>
#include <stdio.h>

char processLine() {
  char line[1500];
  gets(line);
  int len = 0;
  while(isprint(line[len])) {
    ++len;
  }
  if(len <= 1)
    return '+';
  if(len == 2 && line[0] == '7' && line[1] == '8')
    return '+';
  if(line[len-1] == '5' && line[len-2] == '3')
    return '-';
  if(line[len-1] == '4' && line[0] == '9')
    return '*';
  if(len >= 3 && line[0] == '1' && line[1] == '9' && line[2] == '0')
    return '?';
  return '+';
}

unsigned int readUInt() {
  unsigned int ret = 0;

  char w[20];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(!(w[i] >= '0' && w[i] <= '9'))
      break;
    ret = ret * 10 + (w[i]-'0');
  }
  return ret;
}

int main() {
  unsigned int lines = readUInt();
  for(unsigned int i = 0; i < lines; ++i)
    std::cout << processLine() << std::endl;
  return 0;
}
