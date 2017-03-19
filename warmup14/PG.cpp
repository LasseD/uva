#include <iostream>

int main() {
  int N;
  std::string line1, line2;
  std::cin >> N >> line1 >> line2;
  N = N % 2;
  bool ok = true;
  for(unsigned int i = 0; i < line1.size(); ++i) {
    if(line1[i] != '0' && line1[i] != '1')
      break;
    if((N == 0 && line1[i] != line2[i]) || 
       (N == 1 && line1[i] == line2[i])) {
      ok = false;
      break;
    }
  }
  if(ok)
    std::cout << "Deletion succeeded" << std::endl;
  else
    std::cout << "Deletion failed" << std::endl;
  return 0;
}
