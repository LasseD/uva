#include <iostream>
#include <stdio.h>

/*
n(h,k)
H = max number of stamps
k = types of stamps
n = max val of "$1....$max val"
h+k <= 9 => 

k=1 => n=1 using 1
H=1 => n=k using 1,2,...,k

given H, k:
X0=1,X0<X1<=H+1,X2<=(H+1)^2,...,Xm<=(H+1)*m,...,Xk<=(h+1)^k:
k<=7 => n <= (9-k)^k =>
k=7 => n <= 2^7
 */

bool canBuild(int const * const vals, int n, int h, int k) {
  if(n == 0)
    return true;
  if(k == 1) {
    for(int i = k-1; true; --i) {
      if(vals[i] <= n && n%vals[i]==0) {
	return n / vals[i] <= h;
      }
    }
  }
  if(h == 1) {
    for(int i = 0; i < k; ++i) {
      if(vals[i] == n) {
	return true;
      }
    }    
    return false;
  }

  for(int i = 0; i < k; ++i) {
    if(vals[i] > n)
      return false; // no hope.
    if(canBuild(vals, n-vals[i], h-1, k))
      return true;
  }    
  return false;
}

int getN(int const * const vals, int h, int k, int knownN) {
  /*
  std::cerr << "gen h=" << h << ", k=" << k << ", +=" << knownN << ": {";
  for(int i = 0; i < k; ++i)
    std::cerr << vals[i] << " ";
  //*/
  int n = knownN;
  while(canBuild(vals, n+1, h, k))
    ++n;
  //std::cerr << "} " << n << std::endl;
  return n;
}

void run(int ok, int *vals, int &best, int *bestVals, int h, int k, const int knownN) {
  /*
  std::cerr << "run ok=" << ok << ", h=" << h << ", k=" << k << ", knownN=" << knownN << ", {"; 
  for(int i = 0; i < ok; ++i)
    std::cerr << vals[i] << " ";
  std::cerr << "} " << std::endl;
  //*/

  if(ok == k) {
    int n = knownN;
    if(n > best) {
      //std::cerr << "New best!: " << n << std::endl;
      best = n;
      for(int i = 0; i < k; ++i) {
	bestVals[i] = vals[i];
      }
    }
    return;
  }
  
  // Try all up to (h+1)^ok:  
  for(int xi = vals[ok-1]+1; xi <= h*vals[ok-1]+1; ++xi) {
    vals[ok] = xi;
    int n = getN(vals, h, ok+1, knownN);
    if(n < xi)
      break;
    run(ok+1, vals, best, bestVals, h, k, n);
  }
}

int run(int *vals, int h, int k) {
  //std::cerr << "Running h=" << h << ", k=" << k << std::endl;
  if(h == 1) {
    for(int i = 0; i < k; ++i)
      vals[i] = i+1;
    return k;
  }
  vals[0] = 1;
  if(k == 1) {
    return h;
  }
  int bestVals[8];
  int best = k;
  for(int i = 0; i < k; ++i)
    bestVals[i] = k;
  run(1, vals, best, bestVals, h, k, 1);
  for(int i = 1; i < k; ++i)
    vals[i] = bestVals[i];
  return best;
}

int main() {
  int vals[8];

  while(true) {
    int h, k;
    std::cin >> h >> k;
    if(h == 0 && k == 0)
      return 0;
    // compute:
    int n = run(vals, h, k);
    for(int i = 0; i < k; ++i) {
      printf("%3i", vals[i]);
    }
    printf(" ->%3i\n", n);
  }
}
