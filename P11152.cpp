#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

// https://en.wikipedia.org/wiki/Inradius
int main() {
  long a, b, c;
  while(std::cin >> a >> b >> c) {
    double s = (a+b+c)/2.0; // Semiperimeter
    double r = sqrt((s-a)*(s-b)*(s-c)/s); // inradius (of inscribed circle) http://mathworld.wolfram.com/Incircle.html
    double areaSmallCircle = M_PI*(s-a)*(s-b)*(s-c)/s;
    double areaTriangle = s*r; // http://mathworld.wolfram.com/Semiperimeter.html
    double R = a*b*c/(r*s*4); // http://mathworld.wolfram.com/Circumradius.html
    double areaBigCircle = M_PI*R*R;
    /*std::cerr <<"Area small circle: " << areaSmallCircle << std::endl;
    std::cerr <<"Area triangle: " << areaTriangle << std::endl;
    std::cerr <<"Area large circle: " << areaBigCircle << std::endl;//*/

    printf("%.4f %.4f %.4f\n", areaBigCircle-areaTriangle, areaTriangle-areaSmallCircle, areaSmallCircle);
  }
}
