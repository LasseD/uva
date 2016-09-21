#include <iostream>
#include <cstdio>
#include <cstring>

int main() {
  int M, N, K, a[10000];
  int possible[100];
  scanf("%d", &M);
  for(int cas = 0; cas < M; ++cas) {
    // Read input:
    scanf("%d %d", &N, &K);
    long sum = 0;
    for(int i = 0; i < N; ++i) {
      scanf("%d", &a[i]);
      if(a[i] < 0)
	a[i] = -a[i];
      sum += a[i];
    }
    sum %= K;
    memset(possible, 0, K*sizeof(int));
    possible[sum] = 1;

    for(int i = 0; i < N; ++i) {
      // find all divisible:
      int add = 2*K*a[i]-2*a[i];
      for(int j = 0; j < K; ++j) {
	int j2 = (j+add)%K;
	if(possible[j] > 0 && possible[j] <= i+1 && possible[j2] == 0)
	  possible[j2] = i+2;
      }
      if(possible[0] != 0)
	break;
    }

    if(possible[0] != 0)
      puts("Divisible");
    else
      puts("Not divisible");
  }
  return 0;
}
