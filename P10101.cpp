#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef unsigned long long ul;

#define KUTI 10000000 
#define LAKH   100000 
#define HAJAR    1000
#define SHATA     100

void print(ul n) {
  ul kutis = n / KUTI;
  if(kutis > 0) {
    print(kutis);
    printf(" kuti");
  }
  n = n % KUTI;
  // lakh
  ul lakh = n / LAKH;
  if(lakh > 0) {
    printf(" %llu lakh", lakh);
  }
  n = n % LAKH;
  // hajar:
  ul hajar = n / HAJAR;
  if(hajar > 0) {
    printf(" %llu hajar", hajar);
  }
  n = n % HAJAR;
  // shata:
  ul shata = n / SHATA;
  if(shata > 0) {
    printf(" %llu shata", shata);
  }
  n = n % SHATA;
  if(n > 0)
    printf(" %llu", n);
}

/*
 'kuti' (10.000.000), 'lakh' (100.000), 'hajar' (1.000), 'shata' (100)
n < 999.999.999.999.999
 */
int main() {
  ul n;
  for(int cas = 1; cin >> n; ++cas) {
    printf("%4d.", cas);
    // 10 mill's:
    if(n == 0)
      printf(" 0");
    else
      print(n);
    printf("\n");
  }
  return 0;
}
