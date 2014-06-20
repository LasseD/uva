#include <iostream>

int grid(double w, double h) {
  return ((int)w)*((int)h);
}

int skew(double w, double h) {
  if(w < 1 || h < 1)
    return 0;

  int row1 = (int)w;
  int row2 = (int)(w-0.5);

  int rows = 1+(int)((h-1)/0.86602540378);
  //std::cerr << "rows for " << w << "x" << h << ": " << rows << std::endl;
  int numberOfRow2 = rows/2;
  int numberOfRow1 = rows-numberOfRow2;
  return numberOfRow1*row1 + numberOfRow2*row2;
}

int main() {
  double w, h;
  while(std::cin >> w >> h) {
    // compute grid, skew normal and skew other way:
    int g = grid(w,h);
    int s = std::max(skew(w,h),skew(h,w));
    if(s <= g)
      std::cout << g << " grid" << std::endl;
    else
      std::cout << s << " skew" << std::endl;      
  }
  return 0;
}
