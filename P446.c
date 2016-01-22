#include <stdio.h>

int reverse(int a) {
  int i, b;
  b = 0;
  for(i = 0; i < 12; ++i) {
    b = (b << 1) + (a & 1);
    a >>= 1;
  }
  return b;
}

void printBinary(int a) {
  int i, b;
  b = reverse(a); /* Reverse a */
  printf("0");
  for(i = 0; i < 12; ++i) {
    if(b & 1)
      printf("1");
    else
      printf("0");
    b >>= 1;
  }
}

int main() {
  int N, a, b, cas;
  char c[4];
  
  scanf("%d", &N);
  for(cas = 0; cas < N; ++cas) {
    scanf("%x", &a);
    scanf("%s", c);
    scanf("%x", &b);

    printBinary(a);
    printf(" %s ", c);
    printBinary(b);
    printf(" = %d\n", (c[0] == '+') ? (a+b) : (a-b));
  }
  return 0;
}
