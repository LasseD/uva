#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <cstdlib>

struct Factor;
typedef std::set<Factor> Poly;

struct Factor {
  int factor;
  int exponent1;
  int exponent2;
  
  void len(int f, std::stringstream &ss) const {
    if(f < 0) {
      ss << ' ';
      f=-f;
    }
    while(f > 0) {
      ss << ' ';
      f/=10;
    }
  }

  void print(bool first, std::stringstream &a, std::stringstream &b) const {
    // factor:
    if(factor == 0)
      return;
    bool noXY = exponent1 == 0 && exponent2 == 0;
    if(first) {
      if(factor == 1) {
	if(noXY) {
	  a << ' ';
	  b << '1';
	}
      }
      else if(factor == -1) {
	if(noXY) {
	  a << "  ";
	  b << "-1";
	}	
	else {
	  a << ' ';
	  b << '-';
	}
      }
      else {
	len(factor, a);
	b << factor;
      }
    }
    else { // not first:
      a << "   ";
      b << (factor > 0 ? " + " : " - ");

      int f = std::abs(factor);
      if(noXY || f != 1) {
	len(f, a);
	b << f;
      }
    }

    // x:
    if(exponent1 != 0) {
      a << ' ';
      b << 'x';
      if(exponent1 != 1) {
	a << exponent1;
	len(exponent1,b);
      }
    }
    // y:
    if(exponent2 != 0) {
      a << ' ';
      b << 'y';
      if(exponent2 != 1) {
	a << exponent2;
	len(exponent2,b);
      }
    }
  }

  Factor mult(const Factor &f) const {
    Factor res;
    res.factor = factor*f.factor;
    res.exponent1 = exponent1+f.exponent1;
    res.exponent2 = exponent2+f.exponent2;
    return res;
  }

  bool operator<(const Factor &b) const {
    if(exponent1 != b.exponent1)
      return exponent1 > b.exponent1;
    if(exponent2 != b.exponent2)
      return exponent2 < b.exponent2;
    return false;
  }
};

bool okChar(char c) {
  return c == '+' || c == '-' || c == 'x' || c == 'y' || (c >= '0' && c <= '9');
}

void readPoly(char *line, Poly &res) {
  int i = 0;
  while(okChar(line[i])) {
    // read factor:
    Factor f;
    f.factor = 0;
    int neg = false;
    if(line[i] == '-') {
      neg = true;
      ++i;
    }
    else if(line[i] == '+') {
      ++i;
    }
    while(line[i] >= '0' && line[i] <= '9') {
      f.factor = f.factor * 10 + (line[i]-'0');
      ++i;
    }
    if(f.factor == 0)
      f.factor = 1;
    if(neg)
      f.factor = -f.factor;
    //std::cerr << "Factor: " << f.factor << std::endl;
    // read x:
    f.exponent1 = 0;
    f.exponent2 = 0;
    if(line[i] == 'x') {
      ++i;
      while(line[i] >= '0' && line[i] <= '9') {
	f.exponent1 = f.exponent1 * 10 + (line[i]-'0');
	++i;
      }      
      if(f.exponent1 == 0)
	f.exponent1 = 1;
      //std::cerr << "x exponent read: " << f.exponent1 << std::endl;
    }
    if(line[i] == 'y') {
      ++i;
      while(line[i] >= '0' && line[i] <= '9') {
	f.exponent2 = f.exponent2 * 10 + (line[i]-'0');
	++i;
      }      
      if(f.exponent2 == 0)
	f.exponent2 = 1;
      //std::cerr << "y exponent read: " << f.exponent2 << std::endl;
    }
    if(line[i] == 'x') {
      ++i;
      while(line[i] >= '0' && line[i] <= '9') {
	f.exponent1 = f.exponent1 * 10 + (line[i]-'0');
	++i;
      }      
      if(f.exponent1 == 0)
	f.exponent1 = 1;
      //std::cerr << "x exponent read: " << f.exponent1 << std::endl;
    }
    res.insert(f);
  }
}

void mult(const Poly &a, const Poly &b, Poly &res) {
  // multiply factors:
  for(Poly::const_iterator ita = a.begin(); ita != a.end(); ++ita) {
    for(Poly::const_iterator itb = b.begin(); itb != b.end(); ++itb) {
      Factor product = ita->mult(*itb);
      Poly::iterator it = res.find(product);
      if(it != res.end()) {
	product.factor += it->factor;
	res.erase(it);
      }
      res.insert(product);
    }    
  }
}

void printPoly(const Poly &p) {
  std::stringstream s1,s2;
  bool first = true;
  for(Poly::const_iterator it = p.begin(); it != p.end(); ++it) {
    Factor f = *it;
    f.print(first, s1, s2);
    first = false;
  }
  std::cout << s1.str() << std::endl;
  std::cout << s2.str() << std::endl;
}

int main() {
  char line[81];
  while(std::cin.getline(line,81)) {
    // Done?
    if(line[0] == '#')
      break;
    // Construct Polys:
    Poly a, b, c;
    readPoly(line, a);
    std::cin.getline(line,81);
    readPoly(line, b);
    mult(a,b,c);    
    printPoly(c);
  }
  return 0;
}
