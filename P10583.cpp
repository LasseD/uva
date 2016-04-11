#include <iostream>

typedef std::pair<int,int> PP;

unsigned int find(unsigned int i, unsigned int *uf) {
  unsigned int store = i;
  while(i != uf[i])
    i = uf[i];
  unsigned int j = store;
  while(i != j) {
    store = uf[j]; // next.
    uf[j] = i;
    j = store; // stored next.
  }
  return i;
}

void _union(unsigned int i, unsigned int j, unsigned int *uf) {
  i = find(i, uf);
  j = find(j, uf);
  if(i == j)
    return;
  uf[i] = j;
}

int main() {
  unsigned int n, m, I, J; // n = number of students, m = connections.
  for(int cas = 1; true; ++cas) {
    std::cin >> n >> m;
    if(n == 0 && m == 0)
      return 0;
    bool *countedStudents = new bool[n];
    unsigned int *uf = new unsigned int[n];
    for(unsigned int i = 0; i < n; ++i) {
      countedStudents[i] = false;
      uf[i] = i;
    }
    for(unsigned int i = 0; i < m; ++i) {
      std::cin >> I >> J;
      _union(I, J, uf);
    }
    unsigned int count = 0;
    for(unsigned int i = 0; i < n; ++i) {
      unsigned int found = find(i, uf);
      if(countedStudents[found])
	continue;
      ++count;
      countedStudents[found] = true;
    }
    std::cout << "Case " << cas << ": " << count << std::endl;
    delete[] countedStudents;
    delete[] uf;
  }
  return 0;
}
