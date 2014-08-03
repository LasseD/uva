#include <iostream>
#include <stdio.h>
#include <cmath>
#include <iomanip>

struct Real;
typedef std::pair<Real,Real> Point;
typedef std::pair<Point,Point> Line;
typedef long long ll;
#define XX first
#define YY second
#define p1 first
#define p2 second

ll gcd(ll a, ll b) {
  ll c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

int sign(ll l) {
  if(l < 0)
    return -1;
  return 1;
}

struct Real {
  ll nom, denom;

  Real() : nom(0), denom(0) {}
  Real(ll i) : nom(i), denom(1) {}
  Real(ll nom, ll denom) : nom(sign(denom)*nom), denom(std::abs(denom)) {}
  Real(const std::string &rep) {
    nom = 0;
    denom = 1;
    char c;
    unsigned int i = 0;
    while(((c = rep[i]) != '.') && i < rep.size()) {
      nom = 10*nom + (c-'0');
      ++i;
    }
    ++i;
    while(i < rep.size()) {
      nom = 10*nom + (rep[i]-'0');
      denom*=10;
      ++i;
    }
  }

  Real operator*(const Real &b) const {
    return Real(nom*b.nom, denom*b.denom);
  }
  Real operator+(const Real &b) const {
    return Real(nom*b.denom+b.nom*denom, denom*b.denom);
  }
  Real operator-(const Real &b) const {
    return Real(nom*b.denom-b.nom*denom, denom*b.denom);
  }
  Real operator/(const Real &b) const {
    return Real(nom*b.denom, denom*b.nom);
  }
  bool operator==(const Real &b) const {
    return nom*b.denom == denom*b.nom;
  }
  bool operator<(const Real &b) const {
    return nom*b.denom < b.nom*denom;
  }
  bool operator>(const Real &b) const {
    return nom*b.denom > denom*b.nom;
  }
  bool operator<=(const Real &b) const {
    return nom*b.denom <= denom*b.nom;
  }
  bool operator>=(const Real &b) const {
    return nom*b.denom >= denom*b.nom;
  }
  bool operator<(const ll &b) const {
    return nom < denom*b;
  }
  bool operator>(const ll &b) const {
    return nom > denom*b;
  }
  bool operator<=(const ll &b) const {
    return nom <= denom*b;
  }
  bool operator>=(const ll &b) const {
    return nom >= denom*b;
  }
  bool operator==(const ll &b) const {
    return nom == b*denom;
  }
  Real shorten() const {
    Real ret(nom,denom);
    ll g = gcd(nom,denom);
    ret.nom /= g;
    ret.denom /= g;
    return ret;
  }
};
std::ostream& operator<<(std::ostream& os, const Real& b) {
  os << b.nom << "/" << b.denom;
  //os << (b.nom/(double)b.denom);
  return os;
}
std::ostream& operator<<(std::ostream& os, const Point& b) {
  os << b.XX << "," << b.YY;
  return os;
}
std::ostream& operator<<(std::ostream& os, const Line& b) {
  os << b.p1 << "->" << b.p2;
  return os;
}

Real getX(const Line &l, int y) {
  if(l.p1.YY == y)
    return l.p1.XX;
  if(l.p2.YY == y)
    return l.p2.XX;
  Real a = ((l.p2.XX - l.p1.XX) / (l.p2.YY - l.p1.YY)).shorten();
  return (l.p1.XX + a*y - a*l.p1.YY).shorten();
}

int get(Line *lines) {
  int res = 0;

  for(int y = 1; y <= 99; ++y) {
    Real minX(100);
    Real maxX(0);
    for(int i = 0; i < 3; ++i) {
      Line &l = lines[i];
      if(l.p1.YY <= y && l.p2.YY >= y) {
	if(l.p1.YY == l.p2.YY) {
	  {
	    Real x = l.p1.XX;
	    if(x < minX) {
	      minX = x;
	    }
	    if(x > maxX) {
	      maxX = x;
	    }
	  }
	  {
	    Real x = l.p2.XX;
	    if(x < minX) {
	      minX = x;
	    }
	    if(x > maxX) {
	      maxX = x;
	    }
	  }
	  continue;
	}
	// get x
	Real x = getX(l, y);
	// update minX, maxX
	if(x < minX) {
	  minX = x;
	}
	if(x > maxX) {
	  maxX = x;
	}
      }
    }
    if(minX < 1)
      minX = Real(1);
    if(maxX > 99)
      maxX = Real(99);
    // update res
    if(maxX >= minX) {
      int max = maxX.nom / maxX.denom;
      int min = (minX.nom / minX.denom) + (minX.nom % minX.denom == 0 ? 0 : 1);
      int add = max-min+1;
      res += add;
    }
  }
  return res;
}

int main() {
  Point points[3];
  Line lines[3];
  while(true) {
    bool allZero = true;
    for(int i = 0; i < 3; ++i) {
      std::string s;
      std::cin >> s;
      points[i].XX = Real(s);
      if(points[i].XX.nom != 0)
	allZero = false;
      std::cin >> s;
      points[i].YY = Real(s);
      if(points[i].YY.nom != 0)
	allZero = false;
    }
    if(allZero)
      return 0;
    lines[0] = Line(points[0],points[1]);
    lines[1] = Line(points[1],points[2]);
    lines[2] = Line(points[2],points[0]);
    for(int i = 0; i < 3; ++i) {
      if(lines[i].p1.YY > lines[i].p2.YY) {
	std::swap(lines[i].p1, lines[i].p2);
      }
    }
    // compute trapped trees:
    printf("%4i\n", get(lines));
  }
}
