#include <iostream>
#include <stdio.h>
#include <map>
#include <algorithm>

using namespace std;

typedef unsigned long ul;
typedef pair<ul,string> PP;
typedef map<ul,int> Map;

ul encode(char *line) {
  string s(line);
  ul ret = 0;
  sort(s.begin(), s.end());
  for(unsigned int i = 0; i < s.size(); ++i)
    ret = ret*26 + (s[i]-'a');
  return ret;
}

int main() {
  PP dictionary[100];
  int size = 0;
  char line[9];
  while(gets(line)) {
    string s(line);
    if(s.compare("XXXXXX") == 0)
      break;
    //cerr << "Read " << s << ", size " << s.size() << ", encoding: " << encode(line) << endl;
    dictionary[size++] = PP(encode(line), s);    
  }
  sort(dictionary, dictionary+size);
  Map indices;
  for(int i = 0; i < size; ++i) {
    if(i == 0 || dictionary[i].first != dictionary[i-1].first)
      indices.insert(make_pair(dictionary[i].first, i));
  }
  while(gets(line)) {
    string s(line);
    if(s.compare("XXXXXX") == 0)
      break;
    ul encoded = encode(line);
    //cerr << "CMP " << s << ", size " << s.size() << ", encoding: " << encoded << endl;
    bool output = false;
    if(indices.find(encoded) != indices.end()) {
      int i = indices[encoded];
      while(i < size && dictionary[i].first == encoded) {
	if(dictionary[i].second.size() == s.size()) {
	  output = true;
	  cout << dictionary[i].second << endl;
	}
	++i;
      }
    }
    if(!output)
      cout << "NOT A VALID WORD" << endl;
    cout << "******" << endl;
  }
  return 0;
}
