#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n,k;
  cin >> n >> k;

  int len = k;
  string s;
  vector<int> cntOnes(len);
  vector<int> cntZeros(len);

  for(int i = 0; i < n; ++i) {
    cin >> s;
    for(int j = 0; j < k; ++j) {
      if(s[j] == '1')
	cntOnes[j]++;
      else
	cntZeros[j]++;
    }
  }
  for(int i = 0; i < k; ++i) {
    if(cntOnes[i] > cntZeros[i])
      cout << 0;
    else
      cout << 1;
  }
  cout << endl;
  return 0;
}
