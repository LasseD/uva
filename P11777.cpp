#include <iostream>
#include <algorithm>

//#define MAX (20+20+30+10+20) = 100

char grade(int score) {
  if(score >= 90)
    return 'A';
  if(score >= 80)
    return 'B';
  if(score >= 70)
    return 'C';
  if(score >= 60)
    return 'D';
  return 'F';
}

int main() {
  int T, t1, t2, f, a, c[3];
  std::cin >> T;
  for(int cas = 1; cas <= T; ++cas) {
    std::cin >> t1 >> t2 >> f >> a >> c[0] >> c[1] >> c[2];
    std::sort(c, c+3);
    int score = t1+t2+f+a+((c[1]+c[2])/2);
    std::cout << "Case " << cas << ": " << grade(score) << std::endl;
  }
}
