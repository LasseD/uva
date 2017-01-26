// IO:
#include <iostream>
#include <cstdio>
// Data structures:
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <stack>
// Functions:
#include <algorithm>
#include <string>
#include <sstream>
#include <cstring>
#include <limits>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((b) < (a) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))

#define FORCAS int cases; cin >> cases; for(int cas = 0; cas < cases; ++cas)
#define FORI(N) for(int i = 0; i < (N); ++i)
#define FORJ(N) for(int j = 0; j < (N); ++j)
#define FORK(N) for(int k = 0; k < (N); ++k)
#define FORX(N) for(int x = 0; x < (N); ++x)
#define FORY(N) for(int y = 0; y < (N); ++y)
#define FORUI(N) for(unsigned int i = 0; i < (N); ++i)
#define FORUJ(N) for(unsigned int j = 0; j < (N); ++j)
#define FORUK(N) for(unsigned int k = 0; k < (N); ++k)
#define FORUX(N) for(unsigned int x = 0; x < (N); ++x)
#define FORUY(N) for(unsigned int y = 0; y < (N); ++y)

typedef unsigned long long ULL;
typedef long long LL;
typedef long double LD;

typedef pair<int,int> PI;
typedef pair<long,long> PL;
typedef pair<LL,LL> PLL;
typedef pair<ULL,ULL> PULL;
typedef pair<double,double> PD;
typedef pair<string,int> PSI;
typedef pair<int,string> PIS;
typedef pair<ULL,string> PULLS;
typedef pair<int,char> PIC;
typedef pair<char,int> PCI;

typedef PI Point;
typedef PD Point2D;
#define XX first
#define YY second
#define P1 first
#define P2 second

void die() {int *a = NULL; a[3] = 2;}
