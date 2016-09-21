#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  int M, N, K, a[10000];
  bool possible[100], nextPossible[100];
  cin >> M;
  for(int cas = 0; cas < M; ++cas) {
    // Read input:
    cin >> N >> K;
    long sum = 0;
    for(int i = 0; i < N; ++i) {
      cin >> a[i];
      if(a[i] < 0)
	a[i] = -a[i];
      sum += a[i];
    }
    //cerr << "Sum=" << sum;
    sum %= K;
    //cerr << ", mod " << K << "=" << sum << endl;
    for(int i = 0; i < K; ++i) {
      possible[i] = (sum == i);
    }
    for(int i = 0; i < N; ++i) {
      for(int j = 0; j < K; ++j)
	nextPossible[j] = false;
      // find all divisible:
      int add = 2*K*a[i]-2*a[i];
      for(int j = 0; j < K; ++j) {
	if(possible[j])
	  nextPossible[(j+add)%K] = true;
      }

      //cerr << "After a[" <<i <<"]=" << a[i] << ": add=" << add << "%K=" << add%K << endl;
      for(int j = 0; j < K; ++j) {
	possible[j] = nextPossible[j] || possible[j];
	//if(possible[j]) cerr << j << " ";
      }
      //cerr << endl;
    }
    if(possible[0])
      cout << "Divisible" << endl;
    else
      cout << "Not divisible" << endl;
  }
  return 0;
}
