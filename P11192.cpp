#include <stdio.h>
#include <iostream>

int main() {
  char line[209];
  while(true) {
    gets(line);
    int G = line[0]-'0';
    if(G == 0)
      return 0;
    int len = 0;
    while(isprint(line[2+len]))
      ++len;
    G = len/G;
    for(int i = 2; isprint(line[i]); i+=G) {
      for(int j = 0; 2*j < G; ++j) {
	std::swap(line[i+j],line[i+G-j-1]);
      }
    }
    printf("%s\n", &line[2]);
  }
}
