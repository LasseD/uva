#include <stdio.h>
#include <stdbool.h>

int main() {
  int i, j, k;
  bool a[1000001];
  for(i = 0; i < 1000001; ++i)
    a[i] = false;
  for(i = 1; i <= 1000000; ++i) {
    if(a[i])
      continue;
    printf("%d\n", i);
    j = i;
    do {
      a[j] = true;
      /* Increment j: */
      k = j;
      while(k > 0) {
	j += k%10;
	k /= 10;
      }
    } while(j < 1000001 && !a[j]);
  }
}
