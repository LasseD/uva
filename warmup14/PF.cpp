#include <iostream>

std::string n[5] = {
  "***   * *** *** * * *** *** *** *** *** ",
  "* *   *   *   * * * *   *     * * * * * ",
  "* *   * *** *** *** *** ***   * *** *** ",
  "* *   * *     *   *   * * *   * * *   * ",
  "***   * *** ***   * *** ***   * *** *** ",
};

int main() {
  std::string m[5];
  for(int i = 0; i < 5; ++i) {
    getline(std::cin, m[i]);
  }
  int num = 0;
  for(int i = 0; i < m[0].size(); i+=4) {
    bool valid_digit = false;
    for(int j = 0; j <= 9; ++j) {
      bool ok = true;
      for(int line = 0; line < 5; ++line) {
	for(int x = 0; x < 3; ++x) {
	  if(m[line][i+x] != n[line][4*j+x]) {
	    //std::cerr << "Letter " << (i/4) << " is not " << j << ", line=" << line << ", x=" << x << ", " << m[line][i+x] << "!=" << n[line][4*j+x] << std::endl;
	    ok = false;
	    break;
	  }
	}
	if(!ok)
	  break;
      }
      if(ok) {
	num = 10*num + j;
	valid_digit = true;
	break;
      }
    }
    if(!valid_digit) {
      std::cout << "BOOM!!" << std::endl;
      return 0;
    }
  }
  //std::cerr << num << std::endl;
  if(num % 6 == 0) {
    std::cout << "BEER!!" << std::endl;
  }
  else {
    std::cout << "BOOM!!" << std::endl;
  }
  return 0;
}
