#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cmath>

int main() {
  char c, w[10009];
  gets(w);
  int N = 0;
  for(int i = 0; isdigit(c = w[i]); ++i)
    N = 10*N+(c-'0');

  for(int cas = 1; cas <= N; ++cas) {
    std::cout << "Case #" << cas << ":" << std::endl;
    gets(w);
    int len = 0;
    for(int i = 0; isprint(c = w[i]); ++i) {
      if(c >= 'a' && c <= 'z')
	w[len++] = c;
    }
    w[len] = '\0';
    int root = (int)(sqrt(len)+0.5);
    //std::cerr << "root=" << root << ", len=" << len << ", matrix=" << w << std::endl;
    bool ok = len == root*root;
    for(int i = 0; ok && i < root; ++i) {
      int idx1 = i;
      int idx2 = len-1-i;
      int x = i % root;
      int y = i / root;
      int idx3 = root*x+y;
      int idx4 = len - 1 - idx3;
      ok = (w[idx1] == w[idx2]) && (w[idx1] == w[idx3]) && (w[idx1] == w[idx4]);
    }

    if(!ok)
      std::cout << "No magic :(" << std::endl;
    else
      std::cout << root << std::endl;
  }
  return 0;
}
