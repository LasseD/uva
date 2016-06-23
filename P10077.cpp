#include <iostream>

#define N first
#define D second
typedef std::pair<int,int> Fraction;

int main() {
  Fraction f;
  while(true) {
    std::cin >> f.N >> f.D;
    if(f == Fraction(1,1))
      return 0;
    Fraction right(1,0);
    Fraction left(0,1);
    Fraction cur(1,1);
    while(cur != f) {
      if(f.N*cur.D > f.D*cur.N) { // Go right:
	left = cur;
	cur = Fraction(cur.N+right.N, cur.D+right.D);
	std::cout << "R";
      }
      else { // Go left:
	right = cur;
	cur = Fraction(cur.N+left.N, cur.D+left.D);
	std::cout << "L";
      }
    }
    std::cout << std::endl;
  }
}
