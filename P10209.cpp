#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main() {
  double a15 = 15.0*M_PI/180.0;
  //std::cerr << "15 degrees in radians: " << a15 << std::endl;
  double pizzaSlize = M_PI/12;
  //std::cerr << "Pizza slize area: " << pizzaSlize << std::endl;
  double pizzaSlizeTriangle = sin(2*a15)/2;
  //std::cerr << "PizzaSlizeTriangle area: " << pizzaSlizeTriangle << std::endl;
  double pizzaSlizeCrust = pizzaSlize - pizzaSlizeTriangle;
  //std::cerr << "PizzaSlize crust area: " << pizzaSlizeCrust << std::endl;
  double cPlusTwoCrust = tan(a15)/4.0;
  //std::cerr << "C + 2 crust: " << cPlusTwoCrust << std::endl;
  double c = cPlusTwoCrust-2*pizzaSlizeCrust;
  //std::cerr << "C: " << c << std::endl;
  double b = 1-M_PI/4-2*c;
  double a = 1-4*c-4*b;

  double sideLength;
  while(std::cin >> sideLength) {
    //std::cerr << "Side length: " << sideLength << std::endl;
    double area = sideLength*sideLength;
    //std::cerr << "Area: " << area << std::endl;
    printf("%.3f %.3f %.3f\n", a*area, 4*b*area, 4*c*area);
  }
}
