#include <iostream>
#include <cstdio>
#include <stack>
#include <set>
#include <vector>
#include <map>
#include <sstream>

using namespace std;
typedef map<string,int> Dic;

void assert(bool b) {
  if(b)
    return;
  int *a = NULL;
  a[3] = 2;
}

int getLine(string &s1, string &s2) {
  char line[39];
  if(!gets(line))
    return 0;
  string s(line);
  stringstream ss;
  ss << s;
  int ret = 0;
  if(ss >> s1) {
    ++ret;
    if(ss >> s2)
      ++ret;
  }
  return ret;
}

bool neighbours(const string &s1, const string &s2) {
  if(s1.size() != s2.size())
    return false;
  bool foundDiff = false;
  for(unsigned int i = 0; i < s1.size(); ++i) {
    if(s1[i] == s2[i])
      continue;
    if(foundDiff)
      return false;
    foundDiff = true;
  }
  return foundDiff;
}

int main() {
  int cases;
  vector<int> adjacent[200];
  string s1, s2;
  scanf("%d\n", &cases);
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      cout << endl;
    Dic dictionary;
    
    while(true) {
      if(getLine(s1, s2) < 1)
	continue;
      if(s1[0] == '*')
	break;
      int idx1 = (int)dictionary.size();
      adjacent[idx1].clear();
      for(Dic::const_iterator it = dictionary.begin(); it != dictionary.end(); ++it) {
	if(neighbours(it->first, s1)) {
	  int idx2 = it->second;
	  adjacent[idx1].push_back(idx2);
	  adjacent[idx2].push_back(idx1);
	}
      }
      dictionary.insert(make_pair(s1, idx1));
    }

    while(2 == getLine(s1, s2)) {
      assert(s1.size() == s2.size());
      // Find path from s1 to s2:
      int ret = 1;
      set<int> handled;
      stack<int> wavefront;
      int is1 = dictionary[s1];
      int is2 = dictionary[s2];
      wavefront.push(is1);
      bool done = false;
      if(is1 == is2) {
	cout << s1 << " " << s2 << " 0" << endl;
	done = true;
      }
      while(!done) {
	stack<int> nextWave;
	// Handle all in wavefront:
	while(!done && !wavefront.empty()) {
	  int t = wavefront.top();
	  wavefront.pop();
	  if(handled.find(t) != handled.end())
	    continue;
	  handled.insert(t);
	  for(vector<int>::const_iterator it = adjacent[t].begin(); it != adjacent[t].end(); ++it) {
	    int q = *it;
	    if(q == is2) {
	      cout << s1 << " " << s2 << " " << ret << endl;
	      done = true;
	      break;
	    }
	    if(handled.find(q) == handled.end())
	      nextWave.push(q);
	  }
	}
	++ret;
	while(!nextWave.empty()) {
	  wavefront.push(nextWave.top());
	  nextWave.pop();
	}
      }
    }    
  }
  return 0;
}
