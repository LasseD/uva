#include <iostream>
#include <stdio.h>
#include <sstream>

void count(const int startH, const int endH, const int startM, const int endM,
	   int &timeInZone1, int &timeInZone2, int &timeInZone3) {
  // zone 1:
  if(startH < 18 && (endH > 8 || (endH == 8 && endM > 0))) {
    if(startH < 8 || (startH == 8 && startM == 0)) {
      if(endH >= 18)
	timeInZone1 += 10*60;
      else
	timeInZone1 += (endH-8)*60+endM;      
    }
    else if(endH >= 18)
      timeInZone1 += (18-startH)*60-startM;          
    else
      timeInZone1 += (endH-startH)*60+endM-startM;          
  }
 
  // zone 2:
  if(startH < 22 && (endH > 18 || (endH == 18 && endM > 0))) {
    if(startH < 18 || (startH == 18 && startM == 0)) {
      if(endH >= 22)
	timeInZone2 += 4*60;
      else
	timeInZone2 += (endH-18)*60+endM;      
    }
    else if(endH >= 22)
      timeInZone2 += (22-startH)*60-startM;          
    else
      timeInZone2 += (endH-startH)*60+endM-startM;          
  }
 
  // zone 3 top:
  if(endH > 22 || (endH == 22 && endM > 0)) {
    if(startH >= 22) {
      timeInZone3 += (endH-startH)*60+endM-startM;                
    }
    else {
      timeInZone3 += (endH-22)*60+endM;      
    }
  }

  // zone 3 bottom:
  if(startH < 8) {
    if(endH >= 8) {
      timeInZone3 += (8-startH)*60-startM;          
    }
    else {
      timeInZone3 += (endH-startH)*60+endM-startM;                
    }
  }
}

int main() {
  int rates[15] = {10,6,2, 25,15,5, 53,33,13, 87,47,17, 144,80,30};

  std::string line;
  while(true) {
    getline(std::cin, line);
    if(line[0] == '#')
      return 0;
    std::stringstream ss(line);
    std::string step, number;
    int startH, endH, startM, endM;
    ss >> step >> number >> startH >> startM >> endH >> endM;
    if(startH == endH && startM == endM) {
      startH = startM = endM = 0;
      endH = 24;
    }
      
    //std::cerr << "Test: " << step << " " << number << " " << startH << ":" << startM << " -> " << endH << ":" << endM << std::endl;

    int stepIndex = 3*(step[0]-'A');
    bool wrapAround = (startH == endH && startM > endM) || (startH > endH);
    // test all 3 zones:
    int timeInZone1 = 0; // 8-18
    int timeInZone2 = 0; // 18-22
    int timeInZone3 = 0; // 22-8
    if(wrapAround) {
      count(startH, 24, startM, 0, timeInZone1, timeInZone2, timeInZone3);
      count(0, endH, 0, endM, timeInZone1, timeInZone2, timeInZone3);
    }
    else {
      count(startH, endH, startM, endM, timeInZone1, timeInZone2, timeInZone3);
    }
    float cost1 = rates[stepIndex]/100.0*timeInZone1;
    float cost2 = rates[stepIndex+1]/100.0*timeInZone2;
    float cost3 = rates[stepIndex+2]/100.0*timeInZone3;
    float cost = cost1 + cost2 + cost3;
    printf("%10s%6i%6i%6i%3s%8.2f\n", number.c_str(), timeInZone1, timeInZone2, timeInZone3, step.c_str(), cost);
  }
}
