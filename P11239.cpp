#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

void add(map<string,int> &m, const string &name, const int a) {
  map<string,int>::iterator it = m.find(name);
  it->second += a;
}

int main() {
  string line;
  while(true) { // cases
    map<string,int> assignments;
    set<string> banned;
    map<string,int> projects;
    map<int,string> rprojects;

    int projectI = -1;
    while(true) { // Read lines
      getline(cin, line);
      if(line[0] == '0')
	return 0;
      else if(line[0] == '1')
	break;
      else if(isupper(line[0])) { // new project:
	++projectI;
	projects[line] = projectI;
	rprojects[projectI] = line;
      }
      else { // userid:
	if(banned.find(line) != banned.end())
	  continue; // banned!
	if(assignments.find(line) == assignments.end()) {// assign!
	  assignments[line] = projectI;
	}
	else {
	  if(assignments[line] != projectI) { // ban!
	    assignments.erase(line);
	    banned.insert(line);
	  }
	}
      }
    } // read lines

    // Compute output:
    pair<int,string> *ret = new pair<int,string>[projects.size()];
    
    for(map<string,int>::const_iterator it = projects.begin(); it != projects.end(); ++it) {
      ret[it->second] = pair<int,string>(0, it->first);
    }
    for(map<string,int>::const_iterator it = assignments.begin(); it != assignments.end(); ++it) {
      --ret[it->second].first;
    }
    sort(ret, ret+projects.size());
    for(unsigned int i = 0; i < projects.size(); ++i) {
      cout << ret[i].second << " " << (-ret[i].first) << endl;
    }

    delete[] ret;
  } // while(true) for cases
} // int main
