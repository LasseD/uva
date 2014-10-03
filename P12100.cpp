#include <iostream>
#include <deque>
#include <algorithm>

typedef std::pair<int,int> job; // id, priority
#define PRIO second
#define ID first

int main() {
  int N, n, m;
  std::cin >> N;
  for(int ig = 0; ig < N; ++ig) {
    // Read and set up:
    std::cin >> n >> m;
    //std::cerr << "n=" << n << ", m=" << m << std::endl;
    int *priorities = new int[n];
    std::deque<job> deck;
    for(int i = 0; i < n; ++i) {
      job j;
      std::cin >> j.PRIO;
      j.ID = i;
      priorities[i] = j.PRIO;
      deck.push_back(j);
    }
    std::sort(priorities, &priorities[n]);
    
    int time = 1;
    while(true) {
      job j = deck.front();
      deck.pop_front();
      if(j.PRIO == priorities[n-1]) {
	if(j.ID == m) {
	  std::cout << time << std::endl;
	  break;
	}
	--n; // print :)
	++time;
      }
      else {
	deck.push_back(j);
      }
    }
  }
  return 0;
}
