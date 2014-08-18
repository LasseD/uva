#include <iostream>
#include <set>

struct BitVector {
  unsigned long long* rows;
  int n;
  BitVector() {
  }
  BitVector(const BitVector &b) : n(b.n) {
    rows = new unsigned long long[n];
    for(int i = 0; i < n; ++i) {
      rows[i] = b.rows[i];
    }
  }
  BitVector(int n) : n(n) {
    rows = new unsigned long long[n];
    for(int i = 0; i < n; ++i) {
      rows[i] = 0;
    }
  }
  ~BitVector() {
    delete[] rows;
  }
  void flip(const int x, const int y) {
    unsigned long long mask = 1;
    for(int i = 0; i < x; ++i) {
      mask <<= 1;
    }
    if((rows[y] | mask) == rows[y]) {
      rows[y] -= mask;
    }
    else {
      rows[y] += mask;
    }
  }
  bool operator<(const BitVector &b) const {
    for(int i = 0; i < n; ++i) {
      if(rows[i] != b.rows[i])
	return rows[i] < b.rows[i];
    }
    return false;
  }
  bool operator[](int i) const {
    int x = i%n;
    int y = i/n;
    unsigned long long mask = 1;
    for(int i = 0; i < x; ++i) {
      mask <<= 1;
    }
    return (rows[y] | mask) == rows[y];
  }
};

void print(const BitVector &v, int n) {
  for(int y = 0; y < n; ++y) {
    for(int x = 0; x < n; ++x) {
      std::cerr << (v[n*y+x] ? 'X' : 'O');
    }
    std::cerr << std::endl;
  }
}

int main() {
  while(true) {
    int n;
    std::cin >> n;
    if(n == 0)
      return 0;
    std::set<BitVector > set;
    BitVector v1(n);
    BitVector v2(n);
    BitVector v3(n);
    BitVector v4(n);
    
    bool player1 = true;
    bool won = false;
    for(int i = 0; i < 2*n; ++i) {
      int x, y;
      std::string sign;
      std::cin >> x >> y >> sign;
      --x;
      --y;
      if(won)
	continue;
      v1.flip(x, y);
      v2.flip(y, n-1-x);      
      v3.flip(n-1-x, n-1-y);
      v4.flip(n-1-y, x);
      /*      
      std::cerr << "After turn " << i << std::endl;
      print(v1, n);
      print(v2, n);
      print(v3, n);
      print(v4, n);//*/
      if(set.find(v1) != set.end() || set.find(v2) != set.end() || set.find(v3) != set.end() || set.find(v4) != set.end()) {
	won = true;
	if(player1) {
	  std::cout << "Player 2 wins on move " << (i+1) << std::endl;
	}
	else {
	  std::cout << "Player 1 wins on move " << (i+1) << std::endl;
	}
	continue;
      }
      set.insert(v1);
      player1 = !player1;
    }
    if(!won)
      std::cout << "Draw" << std::endl;    
  }
}
