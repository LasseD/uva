#include <iostream>
#include <stdio.h>
#include <cstring>

int main() {
  int N, M;
  char w[89], name[89], bestName[89];
  for(int cas = 1; true; ++cas) {
    float bestPrice;
    int best = 0;
    scanf("%d %d\n", &N, &M);
    if(N == 0 && M == 0)
      return 0;
    if(cas > 1)
      printf("\n");
    printf("RFP #%d\n", cas);
    for(int i = 0; i < N; ++i)
      gets(w);
    for(int i = 0; i < M; ++i) {
      int lines;
      float price;
      gets(name);
      scanf("%f %d\n", &price, &lines);
      for(int j = 0; j < lines; ++j)
	gets(w);
      if(lines > best || (lines == best && price < bestPrice)) {
	//std::cerr << name << " has " << lines << std::endl;
	best = lines;
	bestPrice = price;
	strcpy(bestName, name);
      }
    }
    puts(bestName);
  }
}
