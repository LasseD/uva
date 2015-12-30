#include <iostream>
#include <stdio.h>

char sub(char c) {
  if((c >= '0' && c <= '9') ||c == '-')
    return c;
  if(c >= 'A' && c <= 'C')
    return '2';
  if(c >= 'D' && c <= 'F')
    return '3';
  if(c >= 'G' && c <= 'I')
    return '4';
  if(c >= 'J' && c <= 'L')
    return '5';
  if(c >= 'M' && c <= 'O')
    return '6';
  if(c >= 'P' && c <= 'S')
    return '7';
  if(c >= 'T' && c <= 'V')
    return '8';
  if(c >= 'W' && c <= 'Z')
    return '9';
  return '\0';
}

int main() {
  char line[100];
  while(gets(line)) {
    char c;
    for(int i = 0; isprint(c = line[i]); ++i) {
      line[i] = sub(c);
    }
    std::cout << line << std::endl;
  }
}
