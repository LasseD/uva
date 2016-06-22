#include <iostream>
#include <stdio.h>
#include <set>
#include <string>
#include <sstream>

typedef std::string String;
typedef std::stringstream SS;
typedef std::set<String> Set;

String readLine() {
  char w[100];
  gets(w);  
  int len = 0;
  while(isprint(w[len]))
    ++len;
  w[len] = '\0';    
  return String(w);
}

int main() {
  int K, n;
  SS ss1; ss1 << readLine();
  ss1 >> K;
  
  for(int cas = 0; cas < K; ++cas) {
    SS ss2; ss2 << readLine();
    ss2 >> n;

    String *v1 = new String[n];
    String *v2 = new String[n];
    Set below;

    for(int i = 0; i < n; ++i)
      v1[n-1-i] = readLine();      
    for(int i = 0; i < n; ++i)
      v2[n-1-i] = readLine();      
    
    int v1I = 0;
    int v2I = 0;
    for(;v2I < n;++v2I) {      
      while(v1I < n && v1[v1I] != v2[v2I]) {
	//std::cerr << "Stacking " << v1[v1I] <<"!="<< v2[v2I] << std::endl;
	below.insert(v1[v1I++]);
      }
      if(v1I < n && v1[v1I] == v2[v2I]) {
	v1I++;
      }	
      if(below.find(v2[v2I]) != below.end()) {
	std::cout << v2[v2I] << std::endl;	
      }
    }
    delete[] v1;
    delete[] v2;
    std::cout << std::endl;
  }
  return 0;
}
