#include <iostream>

int main() {
  int H, U, D, F; // H=well height, U=strength, D=nightFall, F=fatique
  while(true) {
    std::cin >> H >> U >> D >> F;
    if(H == 0)
      return 0;
    double height = 0;
    for(int day = 0; true; ++day) {
      double climbHeight = U*(1-day*F/100.0);
      if(climbHeight < 0)
	climbHeight = 0;
      //std::cerr << day << ": init " << height << " climb " << climbHeight << " after climb " << (height+climbHeight) << " after sliding " << (height+climbHeight-D) << std::endl;
      height += climbHeight;
      if(height > H) {
	std::cout << "success on day " << (day+1) << std::endl;
	break;
      }
      height -= D;
      if(height < 0) {
	std::cout << "failure on day " << (day+1) << std::endl;
	break;
      }
    }
  }
}
