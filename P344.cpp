#include <iostream>

void toRomanUpToTen(char *w, int &idx, int n) {
  if(n <= 3) {
    for(int i = 0; i < n; ++i)
      w[idx++] = 'i';
    return;
  }
  if(n == 4) {
    w[idx++] = 'i';
    w[idx++] = 'v';
    return;
  }
  if(n <= 8) {
    w[idx++] = 'v';
    for(int i = 6; i <= n; ++i)
      w[idx++] = 'i';
    return;
  }
  if(n == 9) {
    w[idx++] = 'i';
  }
  w[idx++] = 'x';
}

void toRomanTens(char *w, int &idx, int n) {
  if(n <= 3) {
    for(int i = 0; i < n; ++i)
      w[idx++] = 'x';
    return;
  }
  if(n == 4) {
    w[idx++] = 'x';
    w[idx++] = 'l';
    return;
  }
  if(n <= 8) {
    w[idx++] = 'l';
    for(int i = 6; i <= n; ++i)
      w[idx++] = 'x';
    return;
  }
  if(n == 9) {
    w[idx++] = 'x';
  }
  w[idx++] = 'c';
}

void toRoman(char *w, unsigned int n) {
  int idx = 0;
  toRomanTens(w, idx, n/10);
  toRomanUpToTen(w, idx, n%10);
  w[idx] = '\0';
}

void countRoman(int *counts, int n) {
  char w[20]; // Word.
  toRoman(w, n);
  for(int i = 0; w[i] != '\0'; ++i) {
    ++counts[(int)w[i]];
  }
}

int main() {
  char letters[5] = {'i', 'v', 'x', 'l', 'c'};
  int counts[255];

  int N;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    // reset counts:
    for(int i = 0; i < 5; ++i)
      counts[(int)letters[i]] = 0;
    // Perform counts:
    for(int i = 1; i <= N; ++i)
      countRoman(counts, i);
    // Output:
    std::cout << N << ":";
    for(int i = 0; i < 5; ++i) {
      if(i != 0)
	std::cout << ",";
      std::cout << " " << counts[(int)letters[i]] << " " << letters[i];
    }
    std::cout << std::endl;
  }
}
