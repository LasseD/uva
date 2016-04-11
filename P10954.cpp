#include <iostream>
#include <set>

typedef std::multiset<unsigned long> Set;

int main() {
  unsigned int n, m;
  while(true) {
    std::cin >> n;
    if(n == 0)
      return 0;
    Set s;
    for(unsigned int i = 0; i < n; ++i) {
      std::cin >> m;
      s.insert(m);
    }
    unsigned long sum = 0;
    while(s.size() > 1) {
      unsigned long a = *s.begin();
      s.erase(s.begin());
      unsigned long b = *s.begin();
      s.erase(s.begin());
      sum += a+b;
      s.insert(a+b);
    }
    std::cout << sum << std::endl;
  }
}
