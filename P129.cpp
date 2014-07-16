#include <iostream>

bool check(char const * const s, const int size) {
  if(s[size-1] == s[size-2]) { 
    ///std::cerr << "  "<< s << " TRIVIALLY BAD" << std::endl;
    return false;
  }
  // check from right and go left... super fast!
  char lastC = s[size-1];
  for(int i = size-2; i >= 0; --i) {
    if(s[i] != lastC) { 
      continue;
    }

    bool duplicate = true;
    for(int j = 1; size-1-j > i; ++j) {
      if(i-j < 0) {
	///std::cerr << "  EARLY " << s << std::endl;
	return true;
      }
      if(s[size-1-j] != s[i-j]) {
	duplicate = false;
	break;
      }
    }
    if(duplicate) {
      ///std::cerr << "  " <<s << " contains duplicates" << std::endl;
      return false;
    }
  }
  ///std::cerr << "  LATE  " << s << std::endl;
  return true;
}

// return how many written.
void compute(char *cs, const int i, const int L, int &remaining) {
  ///std::cerr << "Running " << cs << ", i=" << i << ", L=" << L << ", rem=" << remaining << std::endl;
  if(remaining == 0) {
    return;
  }
  for(char l = 'A'; l < 'A'+L; ++l) {
    cs[i] = l;
    cs[i+1] = '\0';
    ///std::cerr << " Test " << cs << ", i=" << i << ", L=" << L << ", rem=" << remaining << std::endl;
    if(check(cs, i+1)) {
      --remaining;
      if(remaining == 0) {
	///std::cerr << " Last check OK " << cs << ", i=" << i << ", L=" << L << ", rem=" << remaining << std::endl;
	return;
      }
      compute(cs, i+1, L, remaining);      
      if(remaining == 0) {
	///std::cerr << " RECURSE => OK " << cs << ", i=" << i << ", L=" << L << ", rem=" << remaining << std::endl;
	return;
      }
    }
    ///std::cerr << " DONE Test " << cs << ", i=" << i << ", L=" << L << ", rem=" << remaining << std::endl;
    cs[i] = '\0';
  }
}

void output(char const * const s) {
  int i = 0;
  for(; s[i] != '\0'; ++i) {
    if(i > 0 && i % 4 == 0) {
      if(i % 64 == 0) {
	std::cout << std::endl;
      }
      else {
	std::cout << ' ';
      }
    }
    std::cout << s[i];
  }
  std::cout << std::endl << i << std::endl;
}

int main() {
  while(true) {
    // Read input
    int n, L;
    std::cin >> n >> L;
    if(L == 0)
      return 0;
    ///std::cerr << "RUNNING n " << n << " L " << L << std::endl;
    // Set up:
    char cs[100];
    compute(cs, 0, L, n);
    output(cs);
  }
}
