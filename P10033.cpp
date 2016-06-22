#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

int readLine(int *ram) {
  std::string line;
  if(!std::getline(std::cin, line))
    return 0;
  std::stringstream ss; ss << line;
  
  int ret = 0;
  while(ss >> ram[ret])
    ++ret;
  return ret;
}

int countInstructions(int *ram) {
  int registers[10];
  for(int i = 0; i < 10; ++i)
    registers[i] = 0;

  int ret = 1;
  int ramIndex = 0;
  int val;
  while(ramIndex < 1000 && (val = ram[ramIndex++]) != 100) {
    ++ret;
    int d1 = val/100;
    int d2 = (val/10)%10;
    int d3 = val%10;
    switch(d1) {
    case 2:
      registers[d2] = d3;
      break;
    case 3:
      registers[d2] = (d3+registers[d2])%1000;
      break;
    case 4:
      registers[d2] = (d3*registers[d2])%1000;
      break;
    case 5:
      registers[d2] = registers[d3];
      break;
    case 6:
      registers[d2] = (registers[d3]+registers[d2])%1000;
      break;
    case 7:
      registers[d2] = (registers[d3]*registers[d2])%1000;
      break;
    case 8:
      registers[d2] = ram[registers[d3]];
      break;
    case 9:
      ram[registers[d3]] = registers[d2];
      break;
    case 0:
      if(registers[d3] != 0) {
	ramIndex = registers[d2];
	//std::cerr << "Goto " << ramIndex << std::endl;
      }
      break;
    default:
      break;
    }
  }
  return ret;
}

/*
10 registers 
1000 ram
3 digit int 0-999, mod 1000
Initial address: 0
 */
int main() {
  int cases, ram[1001];
  readLine(ram);
  cases = ram[0];
  readLine(ram); // Read empty line  
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    int line = 0;
    int readNumbers;
    while((readNumbers = readLine(&ram[line])) > 0)
      line += readNumbers;
    //std::cerr << "Program size: " << line << std::endl;
    for(; line < 1000; ++line)
      ram[line] = 0;
    std::cout << countInstructions(ram) << std::endl;
  }
  return 0;
}
