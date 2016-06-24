#include <iostream>
#include <stdio.h>
#include <map>

typedef std::string String;
typedef std::map<int,int> Map;

int parse(char c) {
  if(c >= '0' && c <= '9')
    return c-'0';  
  switch(c) {
  case 'A':
  case 'B':
  case 'C':
    return 2;
  case 'D':
  case 'E':
  case 'F':
    return 3;
  case 'G':
  case 'H':
  case 'I':
    return 4;
  case 'J':
  case 'K':
  case 'L':
    return 5;
  case 'M':
  case 'N':
  case 'O':
    return 6;
  case 'P':
  case 'R':
  case 'S':
    return 7;
  case 'T':
  case 'U':
  case 'V':
    return 8;
  case 'W':
  case 'X':
  case 'Y':
    return 9;
  default:
    return -1;
  }
}

int readLine() {
  char c, w[39];
  if(!gets(w))
    return -1;
  int i = 0;
  int ret = 0;
  while(isprint(c = w[i++])) {
    int digit = parse(c);
    if(digit >= 0) {
      ret = 10*ret + digit;
    }
  }
  return ret;
}

int main() {
  int cases = readLine();
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      printf("\n");
    Map map;
    readLine();
    int numbers = readLine();
    int line;
    for(int j = 0; j < numbers; ++j) {
      line = readLine();
      if(map.find(line) != map.end()) {
	int before = map[line];
	map.erase(line);
	map.insert(std::make_pair(line,before+1));
      }
      else {
	map.insert(std::make_pair(line,1));
      }
    }
    bool any = false;
    for(Map::const_iterator it = map.begin(); it != map.end(); ++it) {
      if(it->second == 1)
	continue;
      any = true;
      int n = it->first;
      printf("%.3d-%.4d %d\n", n/10000, n%10000, it->second);
    }
    if(!any)
      printf("No duplicates.\n");
  }

  return 0;
}
