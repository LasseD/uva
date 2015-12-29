#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>

int main() {
  std::vector<unsigned int> counts;
  std::map<long,unsigned int> positions;
  std::vector<long> numbers;

  long n;
  while(std::cin >> n) {
    std::map<long,unsigned int>::const_iterator it = positions.find(n);
    if(it == positions.end()) {
      positions.insert(std::make_pair(n, (unsigned int)counts.size()));
      numbers.push_back(n);
      counts.push_back(1);
    }
    else {
      unsigned int position = it->second;
      counts[position]++;
    }
  }
  
  std::vector<long>::const_iterator it1 = numbers.begin();
  std::vector<unsigned int>::const_iterator it2 = counts.begin();
  for(; it1 != numbers.end(); ++it1, ++it2) {
    printf("%li %d\n", *it1, *it2);
  }
}
