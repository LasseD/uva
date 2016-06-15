#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

typedef std::string String;
typedef std::pair<int,int> NM;
typedef std::pair<NM,int> MatrixInfo; // matrix, multiplications.

String readLine() {
  char w[309];
  gets(w);
  return String(w);
}

int die() {
  int *a = NULL;
  a[42] = 666;
  return 0;
}

MatrixInfo parse(const String &s, int &sI, NM const * const matrices) {
  char c = s[sI++];
  if(c != '(')
    return MatrixInfo(matrices[c-'A'], matrices[c-'A'].first < 0 ? die() : 0);

  MatrixInfo left = parse(s, sI, matrices);
  if(left.second < 0) {
    //std::cerr << "Left error!" << std::endl;
    return left;
  }
  MatrixInfo right = parse(s, sI, matrices);
  if(right.second < 0) {
    //std::cerr << "Right error!" << std::endl;
    return right;
  }
  if(left.first.second != right.first.first) {
    //std::cerr << "Error: " << left.first.second << "!=" << right.first.first << std::endl;
    return MatrixInfo(NM(0,0),-1);
  }
  int cnt = left.second + right.second + left.first.first*left.first.second*right.first.second;
  MatrixInfo ret(NM(left.first.first, right.first.second), cnt);
  ++sI; // ')'
  return ret;
}

int main() {
  int N; // Number of matrices.
  std::cin >> N;
  NM matrices[26]; // 0 for A.
  for(int i = 0; i < 26; ++i)
    matrices[i].first = matrices[i].second = -1;
  for(int i = 0; i < N; ++i) {
    String mtx;
    std::cin >> mtx;
    int mI = mtx[0]-'A';
    std::cin >> matrices[mI].first >> matrices[mI].second;
  }
  
  String s;
  while(std::cin >> s) {
    // handle matrix string s:
    int idx = 0;
    MatrixInfo matrixInfo = parse(s, idx, matrices);
    if(matrixInfo.second < 0 )
      std::cout << "error" << std::endl;
    else
      std::cout << matrixInfo.second << std::endl;
  }
  return 0;
}
