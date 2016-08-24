#include <iostream>

int main() {
  int N;
  bool b[1000]; // Stack of decisions (even and odd steps)
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    // Build b:
    int bi = 0;
    while(N > 1) {
      if(N % 2 == 0) {
	N /= 2;
	b[bi++] = true;
      }
      else {
	N = N/2+1;
	b[bi++] = false;
      }
    }
    // Construct ret:
    int ret = 0;
    while(--bi >= 0) {
      if(b[bi]) { // Was even:
	N *= 2;
	ret = 2*ret+1;
      }
      else {
	N = (N-1)*2+1;
	if(ret == 0)
	  ret = N-1;
	else
	  ret = 2*(ret-1) + 1;
      }
    }
    std::cout << 1+ret << std::endl;
  }
}

/*
This is too slow:
int main() {
  int N, a[500000];
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    int mult = 1;
    int M = N;
    while(M%2 == 0) {
      M/=2;
      mult*=2;
    }
    for(int i = 0; i < M; ++i) {
      a[i] = mult*i+mult-1;
    }
    while(M > 1) {
      if(M % 2 == 0) {
	M /= 2;
	for(int i = 0; i < M; ++i)
	  a[i] = a[2*i+1];
      }
      else {
	a[0] = a[M-1];
	M = M/2+1;
	for(int i = 0; i < M-1; ++i)
	  a[i+1] = a[2*i+1];
      }
    }
    std::cout << 1+a[0] << std::endl;
  }
}
*/
