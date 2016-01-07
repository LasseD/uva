#include <iostream>
#include <stdio.h>

int main() {
  short *n1 = new short[1000000];
  short *n2 = new short[1000000];
  char *sum = new char[1000001];
  long N, M;
  std::cin >> N;
  for(long cas = 0; cas < N; ++cas) {
    std::cin >> M;
    for(long i = 0; i < M; ++i) {
      std::cin >> n1[M-1-i] >> n2[M-1-i];
    }
    int carry = 0;
    for(long i = 0; i < M; ++i) {
      int digit = carry + n1[i] + n2[i];
      carry = digit/10;
      sum[M-1-i] = '0'+(digit%10);
    }
    sum[M] = '\0';
    if(cas > 0)
      printf("\n");
    printf("%s\n", sum);
  }
  delete[] n1;
  delete[] n2;
  delete[] sum;
  return 0;
}
