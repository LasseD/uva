#include <iostream>
#include <cstdio>
#include <set>
#include <string>

using namespace std;
typedef set<string> Set;

void add(Set &s, string x, int start, int len) {
  string abe = x.substr(start, len);
  if(s.find(abe) == s.end())
    s.insert(abe);
}

int main() {
  string line;
  bool a[83];
  while(cin >> line) {
    Set s;
    int N = (int)line.size();
    // Add odd length palindromes:
    for(int i = 0; i < N; ++i) {
      a[i] = true;
      add(s, line, i, 1);
    }
    for(int length = 3; length <= N; length += 2) {
      for(int start = 0; start+length <= N; ++start) {
	if(a[start+1] && line[start] == line[start+length-1]) {
	  a[start] = true;
	  add(s, line, start, length);
	  //cerr << "Palindrome of length " << length << " at " << start << endl;
	}
	else
	  a[start] = false;
      }
    }
    // Add even length substrings:
    for(int i = 0; i < N; ++i)
      a[i] = true;
    for(int length = 2; length <= N; length += 2) {
      for(int start = 0; start+length <= N; ++start) {
	if(a[start+1] && line[start] == line[start+length-1]) {
	  a[start] = true;
	  add(s, line, start, length);
	}
	else
	  a[start] = false;
      }
    }
    cout << "The string '" << line << "' contains " << s.size() << " palindromes." << endl;
  }
}
