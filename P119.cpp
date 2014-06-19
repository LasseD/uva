#include <iostream>
#include <map>
#include <vector>

void add(std::map<std::string,int> &m, const std::string &name, const int a) {
  std::map<std::string,int>::iterator it = m.find(name);
  it->second += a;
}

int main() {
  int n;
  bool first = true;
  while(std::cin >> n) {
    if(!first)
      std::cout << std::endl;
    first = false;

    std::map<std::string,int> map;
    std::vector<std::string> v;
    // Read names and add to m:
    char name[13];
    char name2[13];
    for(int i = 0; i < n; ++i) {
      std::cin >> name;
      std::string sname(name);
      map.insert(std::make_pair(sname,0));
      v.push_back(sname);
    }
    // Read gift lines:
    for(int i = 0; i < n; ++i) {
      int money, m;
      std::cin >> name >> money >> m;      
      std::string sname(name);
      //std::cerr << "Processing " << sname << " with " << money << " to " << m << std::endl;

      int rest = m == 0 ? money : money % m;
      add(map, sname, -money+rest);
      for(int j = 0; j < m; ++j) {
	std::cin >> name2;
	std::string sname2(name2);	
	add(map, sname2, m == 0 ? 0 : money/m);	
      }
    }
    // output:
    for(std::vector<std::string>::const_iterator it = v.begin(); it != v.end(); ++it) {
      std::string user = *it;
      std::cout << user << " " << map.find(user)->second << std::endl;
    }
  }
  return 0;
}
