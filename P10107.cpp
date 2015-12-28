#include <iostream>
#include <set>

typedef unsigned long ul;
typedef std::multiset<ul> set;

int main() {
  set low, high; // |high| <= |low|+1, |low| <= |high|+1
  ul X;
  while(std::cin >> X) {
    if(high.empty() || X > *high.begin()) {
      high.insert(X);
      if(high.size() > low.size()+1) {
	int mid = *high.begin();
	high.erase(high.begin());
	low.insert(mid);
      }
    }
    else {
      low.insert(X);
      if(low.size() > high.size()) {
	int mid = *low.rbegin();
	set::iterator it = low.end();
	--it;
	low.erase(it);
	high.insert(mid);
      }
    }

    if(high.size() == low.size()) {
      //std::cerr << "|low|==|hig|, |low| = " << low.size() << ", |high|=" << high.size() << std::endl;
      std::cout << (*low.rbegin() + *high.begin())/2 << std::endl;
    }
    else {
      //std::cerr << "|low|!=|hig|, |low| = " << low.size() << ", |high|=" << high.size() << std::endl;
      std::cout << *high.begin() << std::endl;
    }
  }
  return 0;
}
