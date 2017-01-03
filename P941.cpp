#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ul;

ul fac(int n) {
  ul ret = 1;
  for(int i = 2; i <= n; ++i)
    ret *= i;
  return ret;
}

ul permutations(string s, int begin, char skip) {
  ul out = fac(-begin+(int)s.size()-1);
  int rep = 1;
  char prev = '_';
  bool skipped = false;
  for(unsigned int i = begin; i < s.size(); ++i) {
    if(!skipped && s[i] == skip) {
      skipped = true;
      continue; // skip.
    }
    if(s[i] == prev)
      ++rep;
    else {
      out /= fac(rep);
      rep = 1;
      prev = s[i];
    }
  }
  out /= fac(rep);
  //cerr << "Permutations for " << s << ", start index " << begin << ", skipping " << skip << ": " << out << endl;
  return out;
}

int main() {
  int N;
  cin >> N;
  for(int cas = 1; cas <= N; ++cas) {
    string s;
    cin >> s;
    ul rem, sub;
    cin >> rem;

    for(int i = 0; i < (int)s.size(); ++i) {
      sort(s.begin()+i, s.end()); // Because of letter swapping.
      int toSwapIndex = i;
      while(toSwapIndex < (int)s.size() && (sub = permutations(s, i, s[toSwapIndex])) <= rem) {
	//cerr << "Skipping letter " << s[toSwapIndex] << " in " << s << ", index " << toSwapIndex << ": " << rem << " -> " << (rem-sub) << endl;
	rem -= sub;
	do {
	  ++toSwapIndex;
	} while(toSwapIndex < (int)s.size()&& s[toSwapIndex-1] == s[toSwapIndex]);
      }
      if(toSwapIndex < (int)s.size()) {
	swap(s[i], s[toSwapIndex]);
      }
    }

    cout << s << endl;
  }
}
