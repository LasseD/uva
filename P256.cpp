#include <iostream>
#include <stdio.h>

/*
hm+l = (l+h)^2 = l^2 + h^2 + 2lh
=>
h^2 + (2l-m)h + l^2-l = 0
l^2 + (2h-1)l + h^2-hm = 0
l = (-2h+1 +- sqrt((2h-1)^2-4(h^2-hm))) / 2 =>
l = (-2h+1 +- sqrt(h(-2+4m)+1)) / 2
(2h-1)^2-4(h^2-hm) = 4h^2-2h+1-4h^2+4hm = h(-2+4m)+1
 */
void printQuirksomeSquares(int mult, int width) {
  for(int high = 0; high < mult; ++high) {
    int b = high*mult;
    for(int low = 0; low < mult; ++low) {
      int c = b+low;
      if(c == (low+high)*(low+high)) {
	switch(width) {
	case 2:
	  printf("%.2d\n", c);
	  break;
	case 4:
	  printf("%.4d\n", c);
	  break;
	case 6:
	  printf("%.6d\n", c);
	  break;
	case 8:
	  printf("%.8d\n", c);
	  break;
	}
      }
    }
  }
}
/*
00
01
81
0000
0001
2025
3025
9801
000000
000001
088209
494209
998001
00000000
00000001
04941729
07441984
24502500
25502500
52881984
60481729
99980001
*/

int main() {
  int n;
  while(std::cin >> n) {
    switch(n) {
    case 2:
      printf("00\n");
      printf("01\n");
      printf("81\n");
      //printQuirksomeSquares(10, 2);
      break;
    case 4:
      printf("0000\n");
      printf("0001\n");
      printf("2025\n");
      printf("3025\n");
      printf("9801\n");
      //printQuirksomeSquares(100, 4);
      break;
    case 6:
      printf("000000\n");
      printf("000001\n");
      printf("088209\n");
      printf("494209\n");
      printf("998001\n");
      //printQuirksomeSquares(1000, 6);
      break;
    case 8:
      printf("00000000\n");
      printf("00000001\n");
      printf("04941729\n");
      printf("07441984\n");
      printf("24502500\n");
      printf("25502500\n");
      printf("52881984\n");
      printf("60481729\n");
      printf("99980001\n");
      //printQuirksomeSquares(10000, 8);
      break;
    }
  }
  return 0;
}
