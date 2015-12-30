#include <iostream>
#include <map>
#include <algorithm>

int main() {
  int N, Q, a;
  for(int cas = 0; true; ++cas) {
    std::cin >> N >> Q;
    if(N == 0 && Q == 0)
      return 0;
    std::cout << "CASE# " << (cas+1) << ":" << std::endl;
    int *v = new int[N];
    for(int i = 0; i < N; ++i) {
      std::cin >> v[i];
    }
    std::sort(v, v+N);

    std::map<int,int> map; // marble -> first occurence
    for(int i = 0; i < N; ++i) {
      if(map.find(v[i]) == map.end())
	map.insert(std::make_pair(v[i], i+1));
    }
    delete[] v;

    for(int i = 0; i < Q; ++i) {
      std::cin >> a;
      std::map<int,int>::const_iterator it = map.find(a);
      if(map.find(a) == map.end())
	std::cout << a << " not found" << std::endl;
      else
	std::cout << a << " found at " << it->second << std::endl;
    }
  }
}
