#include <iostream>
#include <stack>
#include <queue>
#include <set>

typedef std::pair<int,int> Pair;
typedef std::set<Pair> PQ;
typedef std::stack<int> Stack;
typedef std::queue<int> Queue;

int main() {
  int n, e, o;
  while(std::cin >> n) {
    bool canBeQueue = true;
    bool canBeStack = true;
    bool canBePQ = true;
    
    PQ pq;
    Queue q; // push, front, pop.
    Stack s;
    int size = 0;

    for(int i = 0; i < n; ++i) {
      std::cin >> o >> e;
      if(o == 1) {
	if(canBePQ)
	  pq.insert(Pair(-e,i)); // i ensures uniqueness.
	if(canBeQueue)
	  q.push(e);
	if(canBeStack)
	  s.push(e);
	++size;
      }
      else {
	if(size <= 0) {
	  canBeQueue = canBeStack = canBePQ = false;
	  continue;
	}
	--size;

	if(canBeQueue) {
	  canBeQueue = q.front() == e;
	  q.pop();
	}
	if(canBeStack) {
	  canBeStack = s.top() == e;
	  s.pop();
	}
	if(canBePQ) {
	  canBePQ = -e == pq.begin()->first;
	  pq.erase(pq.begin());
	}
      }
    }
    int canBeCount = (canBeQueue?1:0) + (canBeStack?1:0) + (canBePQ?1:0);
    if(canBeCount > 1)
      std::cout << "not sure" << std::endl;
    else if(canBeCount == 0)
      std::cout << "impossible" << std::endl;
    else if(canBeQueue)
      std::cout << "queue" << std::endl;
    else if(canBeStack)
      std::cout << "stack" << std::endl;
    else if(canBePQ)
      std::cout << "priority queue" << std::endl;
  }
}
