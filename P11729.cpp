#include <iostream>
#include <algorithm>

typedef std::pair<int,int> Job; // id, priority
#define B second
#define J first

int main() {
  int N;
  for(int cas = 1; true; ++cas) {
    std::cin >> N;
    if(N == 0)
      return 0;
    Job *jobs = new Job[N];
    
    for(int i = 0; i < N; ++i) {
      std::cin >> jobs[i].B >> jobs[i].J;
      jobs[i].J = -jobs[i].J;
    }
    std::sort(jobs, jobs+N);
    
    int maxTotal = 0;
    int b = 0;
    for(int i = 0; i < N; ++i) {
      b += jobs[i].B;
      if(maxTotal < b - jobs[i].J)
	maxTotal = b - jobs[i].J;
    }
    std::cout << "Case " << cas << ": " << maxTotal << std::endl;
  }
}
