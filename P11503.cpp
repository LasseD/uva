#include <iostream>
#include <map>

struct Circle {
  Circle *c;
  int size;
};

int main() {
  Circle *cs = new Circle[200000];  

  int T, n;
  std::cin >> T;
  for(int ig = 0; ig < T; ++ig) {
    std::cin >> n;
    int csi = 0; // reset circles;

    std::map<std::string, Circle*> people;
    
    std::string a, b;
    for(int i = 0; i < n; ++i) {
      std::cin >> a >> b;
      if(people.find(a) == people.end()) {
	if(people.find(b) == people.end()) {
	  cs[csi].size = 1;
	  cs[csi].c = NULL;
	  people.insert(std::make_pair(b, &cs[csi]));
	  csi++;

	  cs[csi].size = 1;
	  cs[csi].c = NULL;
	  people.insert(std::make_pair(a, &cs[csi]));
	  csi++;
	}
	else {
	  Circle *cb = people.find(b)->second;
	  while(cb->c != NULL) {
	    cb = cb->c;
	  }
	  cb->size+=1;
	  people.insert(std::make_pair(a, cb));	  
	  std::cout << cb->size << std::endl;	  
	  continue;
	}
      }
      else if(people.find(b) == people.end()) {
	Circle *ca = people.find(a)->second;
	while(ca->c != NULL) {
	  ca = ca->c;
	}
	ca->size+=1;
	people.insert(std::make_pair(b, ca));	  
	std::cout << ca->size << std::endl;
	continue;
      }

      int steps = 0;
      Circle *ca = people.find(a)->second;
      while(ca->c != NULL) {
	ca = ca->c;
	++steps;
      }
      Circle *cb = people.find(b)->second;
      while(cb->c != NULL) {
	cb = cb->c;
	++steps;
      }
      if(ca == cb) {
	std::cout << cb->size << std::endl;
	continue;
      }
      // merge:
      //std::cerr << "a/b: " << cb->size << ", " << ca->size << ", steps=" << steps << std::endl;
      if(ca->size < cb->size) {
	ca->c = cb;
	cb->size+=ca->size;
	ca->size = 0;
	std::cout << cb->size << std::endl;
      }
      else {
	cb->c = ca;
	ca->size+=cb->size;
	cb->size = 0;
	std::cout << ca->size << std::endl;
      }
    }
  }
  delete[] cs;
  return 0;
}
