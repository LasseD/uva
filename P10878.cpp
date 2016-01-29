#include <stdio.h>

int main() {
  char w[29];
  while(gets(w)) {
    if(w[0] != '|')
      continue;
    char c = 0;
    int mask = 1;
    for(int i = 0; i < 7; ++i, mask <<= 1) {
      int pos = i + 2;
      if(i >= 4)
	++pos;
      c = (c<<1) + (w[pos] == 'o' ? 1 : 0);
    }
    putchar(c);
  }
  return 0;
}
