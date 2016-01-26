#include <iostream>
#include <stack>
#include <vector>

bool ok(const std::vector<int> &out) {
  int in = 1;
  std::stack<int> station;
  for(std::vector<int>::const_iterator it = out.begin(); it != out.end(); ++it) {
    while(station.empty() || station.top() != *it) {
      if(in > (int)out.size())
	return false;
      //std::cerr << "Pushing " << in << " vs " << *it << " to station." << std::endl;
      station.push(in++);
    }
    //std::cerr << "Popping " << station.top() << " from station." << std::endl;
    station.pop();
  }
  return true;
}

int main() {
  int N, M;
  std::vector<int> out;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    while(true) {
      std::cin >> M;
      if(M == 0)
	break;
      out.clear();
      out.push_back(M);
      for(int i = 1; i < N; ++i) {
	std::cin >> M;
	out.push_back(M);
      }
      if(ok(out))
	std::cout << "Yes" << std::endl;
      else
	std::cout << "No" << std::endl;
    }
    std::cout << std::endl;
  }
}
