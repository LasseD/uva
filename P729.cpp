#include <stdio.h>
#include <iostream>

void handle(char *w, int idx, int N, int H) {
  if(H == N) {
    for(int i = 0; i < N; ++i)
      w[idx+i] = '1';
    printf("%s\n", w);
    return;
  }
  if(H == 0) {
    for(int i = 0; i < N; ++i)
      w[idx+i] = '0';
    printf("%s\n", w);
    return;
  }
  w[idx] = '0';
  handle(w, idx+1, N-1, H);
  w[idx] = '1';
  handle(w, idx+1, N-1, H-1);
}

int main() {
  int cases, N, H;
  char w[20];
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    std::cin >> N >> H;
    w[N] = '\0';
    if(cas != 0)
      printf("\n");
    handle(w, 0, N, H);
  }
}
