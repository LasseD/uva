#include <iostream>
#include <stdio.h>

bool isWovel(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int countVowels(char *w, int &idx) {
  int cnt = 0;
  char c;
  while(isprint(c = w[idx]) && c != '/') {
    if(isWovel(c) && (idx == 0 || !isWovel(w[idx-1])))
      ++cnt;
    ++idx;
  }
  //std::cerr << "Counted " << cnt << std::endl;
  return cnt;
}

char isHaiku(char *w) {
  int idx = 0;
  if(countVowels(w, idx) != 5)
    return '1';
  ++idx;
  if(countVowels(w, idx) != 7)
    return '2';
  ++idx;
  if(countVowels(w, idx) != 5)
    return '3';
  return 'Y';
}

int main() {
  char w[309];
  while(true) {
    gets(w);
    if(w[0]=='e'&&w[1]=='/'&&w[2]=='o'&&w[3]=='/'&&w[4]=='i'&& !isprint(w[5]))
      return 0;
    std::cout << isHaiku(w) << std::endl;
  }
}
