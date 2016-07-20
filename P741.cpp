#include <iostream>
#include <stdio.h>
#include <algorithm>

void die() {std::cerr<<"ABORT!"<<std::endl;int *a = NULL; a[2]=3;}

struct String {
  char *a;
  int start, size;
  bool initiated;

  String() : initiated(false) {}
  String(const String &s) : a(s.a), start(s.start), size(s.size), initiated(s.initiated) {}
  ~String() {} // Not to worry about - we only have 300 in total...

  void reset(int size) {
    if(initiated)
      delete[] a;
    this->size = size;
    start = size;
    a = new char[size+1];
    a[size] = '\0';
    initiated = true;
  }

  void push_front(char c) {
    if(start == 0)
      die();
    a[--start] = c;
  }

  void print() const {
    std::cout << &a[start] << std::endl;
  }

  bool operator<(const String &b) const {
    if(size != b.size || start != b.start)
      die();
    for(int i = start; i < size; ++i) {
      if(a[i] != b.a[i])
	return a[i] < b.a[i];
    }
    return false;
  }
};

/*
BANANA:

Input: NNBAAA 4

Reconstruct: (First line is sorted characters):
A----N
A----N
A----B
B----A
N----A
N----A

AN => All before N must be A and all after A must be N:
NA, BA, AB, AN
A---AN
A---AN
A----B
BA---A
NA---A
NA---A

Or just do it the official way and insert sorted column before all, then sort all.
https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform

function inverseBWT(s ending with '~' (larger than any alphanumaric ascii value))
   create empty table
   repeat length(s) times
       // first insert creates first column
       insert s as a column of table before first column of the table
       sort rows of the table alphabetically
   return (row that ends with '~')
 */
int main() {
  String a[300];
  std::string s;
  int n;
  bool first = true;
  while(true) {
    std::cin >> s >> n;
    if(s == "END" && n == 0)
      return 0;

    if(!first)
      std::cout << std::endl;
    first = false;

    int size = (int)s.size();
    for(int i = 0; i < size; ++i)
      a[i].reset(size);

    for(unsigned int i = 0; i < s.size(); ++i) {
      for(int i = 0; i < size; ++i)
	a[i].push_front(s[i]);
      std::sort(a, a+size);
      /*for(int i = 0; i < size; ++i)
	a[i].print();//*/
    }
    a[n-1].print();
  }
}
