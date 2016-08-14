#include <iostream>

typedef std::string String;
typedef unsigned long long ul;

int hexToInt(char c) {
  if(c >= '0' && c <= '9')
    return c-'0';
  return 10 + c - 'A';
}

int minBase(String &s) {
  int ret = 2;
  for(unsigned int i = 0; i < s.size(); ++i) {
    int base = hexToInt(s[i]);
    if(base >= ret)
      ret = base + 1;
  }
  return ret;
}

ul decode(String &s, int base) {
  ul ret = 0;
  for(unsigned int i = 0; i < s.size(); ++i)
    ret = base*ret + hexToInt(s[i]);
  //std::cerr << s << " base " << base << " = " << ret << std::endl;
  return ret;
}

int main() {
  String a, b;
  ul decodedA[36], decodedB[36];
  while(std::cin >> a >> b) {
    int minBaseA = minBase(a);
    int minBaseB = minBase(b);
    for(int baseA = minBaseA; baseA <= 36; ++baseA) {      
      decodedA[baseA-1] = decode(a, baseA);
    }
    for(int baseB = minBaseB; baseB <= 36; ++baseB) {
      decodedB[baseB-1] = decode(b, baseB);
    }
    bool printed = false;
    for(int baseA = minBaseA; !printed && baseA <= 36; ++baseA) {      
      for(int baseB = minBaseB; !printed && baseB <= 36; ++baseB) {
	if(decodedA[baseA-1] == decodedB[baseB-1]) {
	  std::cout << a << " (base " << baseA << ") = " << b << " (base " << baseB << ")" << std::endl;
	  printed = true;
	}
      }
    }
    if(!printed)
      std::cout << a << " is not equal to " << b << " in any base 2..36" << std::endl;
  }
  return 0;
}
