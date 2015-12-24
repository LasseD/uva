#include <stdio.h>

int main() {
  char s[1000];
  while(gets(s)) {
    for(int i = 0; '\0' != s[i]; ++i)
      s[i] = (char)(s[i]-7);
    printf("%s\n", s);
  }
  return 0;
}
