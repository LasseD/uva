#include <iostream>

void die() {
  int *die = NULL;
  die[0] = 666;
}

int sToI(std::string s) {
  int ret = 0;
  for(unsigned int i = 0; i < s.length(); ++i) {
    if(!isdigit(s[i]))
      die();
    ret = 10*ret + (s[i]-'0');
  }
  return ret;
}

int main() {
  int N, M, p, q;
  std::string s;
  std::cin >> N >> M;
  for(int cas = 0; cas < N; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    //std::cerr << "Problem size " << M << " for line '" << line[0] << "'" << std::endl;
    int *a = new int[M];
    for(int i = 0; i < M; ++i)
      a[i] = i;
    int good = 0;
    int bad = 0;
    while(true) {
      if(!(std::cin >> s)) {
	//std::cerr << "End break" << std::endl;
	break;
      }
      if(!(s[0] == 'c' || s[0] == 'q')) {
	M = sToI(s);
	break;
      }
      if(!(std::cin >> p >> q))
	die();
      --p;
      --q;
      if(p < 0 || q < 0 || p >= M || q >= M)
	 die();
      if(s[0] == 'c') {
	//std::cerr << "Merging " << p << " & " << q << std::endl;
	if(a[p] == a[q])
	  continue;
	int from = a[q];
	//int to = a[p];
	for(int i = 0; i < M; ++i) {
	  if(a[i] == from)
	    a[i] = a[p];
	}
      }
      else { // c == 'q'
	//std::cerr << "Query " << p << " & " << q << std::endl;
	if(a[p] == a[q])
	  ++good;
	else
	  ++bad;
      }
    } // while true
    std::cout << good << "," << bad << std::endl;
    delete[] a;
  } // for cas
  return 0;
}
