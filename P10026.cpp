#include <iostream>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <algorithm>

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

  bool operator<(const Real &b) const {
    return nom*b.denom < b.nom*denom;
  }
};

typedef std::pair<Real,int> TT;

/*
If all times were 1: Order by fine decreasing.
If all fines were 1: Order by time increasing
 */
int main() {
  int cases, N;
  TT a[1000];

  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    std::cin >> N;
    for(int i = 0; i < N; ++i) {
      std::cin >> a[i].first.nom >> a[i].first.denom; // tt.TIME >> tt.FINE;
      a[i].second = i;
    }
    std::sort(a, a+N);

    for(int i = 0; i < N; ++i) {
      if(i != 0)
	std::cout << " ";
      std::cout << (a[i].second+1);
    }
    std::cout << std::endl;
  }
  return 0;
}
