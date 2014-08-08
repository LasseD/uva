#include <iostream>
#include <stdio.h>
#include <sstream>
#include <map>

typedef std::map<std::string,std::pair<std::string,int> > mt;

int main() {
  // read tables:
  mt IDDMap;
  mt STDMap;
  while(true) {
    std::string line;
    getline(std::cin, line);
    if(line.compare(0, 6, "000000") == 0)
      break;
    //std::cerr << "Reading line: " << line << std::endl;

    std::stringstream code, locality;
    // get code:
    char c;
    unsigned int i = 0;
    while((c = line[i++]) != ' ') {
      code << c;
    }

    const std::string codeS = code.str();
    // check code is ok:
    if(codeS.size() < 2 || codeS[0] != '0')
      continue;
    bool international = true;
    if(codeS[1] == '0') { // international
      if(codeS.size() > 5 || codeS.size() < 3)
	continue;
    }
    else {
      international = false;
      if(codeS.size() > 6)
	continue;
    }

    // get locality:
    while((c = line[i++]) != '$') {
      locality << c;
    }
    
    // get price:
    int price = 0;
    while(i < line.size()) {
      c = line[i];
      if(c >= '0' && c <= '9')
	price = price * 10 + (c-'0');
      ++i;
    }
    
    // save:
    if(international) {
      //std::cerr << "International number: " << codeS << ", " << locality.str() << ", " << price << std::endl;
      IDDMap.insert(std::make_pair(codeS, std::make_pair(locality.str(),price)));
    }
    else {
      //std::cerr << "Domestic      number: " << codeS << ", " << locality.str() << ", " << price << std::endl;
      STDMap.insert(std::make_pair(codeS, std::make_pair(locality.str(),price)));
    }
  }

  //std::cerr << "Done reading table" << std::endl;

  // find all calls:
  while(true) {
    std::string line;
    getline(std::cin, line);
    if(line[0] == '#')
      return 0;
    //std::cerr << "Reading call: " << line << std::endl;

    std::stringstream number;
    // get code:
    char c;
    unsigned int i = 0;
    while((c = line[i++]) != ' ') {
      number << c;
    }
    // get duration:
    int duration = 0;
    while(i < line.size()) {
      c = line[i];
      if(c >= '0' && c <= '9')
	duration = duration * 10 + (c-'0');
      ++i;
    }

/*
|number| <= 15
time in minutes
Report w. cost

international: (00)(country[1-3])(subscr[4-10])
     national: (0)(area[1-5])(subscr[4-7])
        local: (!0)(*)
 */

    bool found = false;
    std::string numberS = number.str();
    if(numberS[0] != '0') { // local
      printf("%-16sLocal                    %10s%5i%6.2f%7.2f\n", numberS.c_str(), numberS.c_str(), duration, 0.00, 0.00);
      found = true;
      //std::cerr << "779760          Local                        779760    1  0.00   0.00" << std::endl;
    }
    else if(numberS[1] == '0') { // international:
      // country code is 1-3 digits
      for(int countryLength = 1; countryLength <= 3; ++countryLength) {
	int subscrLen = numberS.size() - 2 - countryLength;
	if(subscrLen < 4 || subscrLen > 10)
	  continue;
	std::string key = numberS.substr(0, 2+countryLength);
	mt::iterator it = IDDMap.find(key);
	if(it != IDDMap.end()) {
	  std::string subscr = numberS.substr(2+countryLength, numberS.size()-key.size());
	  std::string countryName = it->second.first;
	  int centPrMinute = it->second.second;
	  // std::map<std::string,std::pair<std::string,int> >
	  printf("%-16s%-25s%10s%5i%6.2f%7.2f\n", numberS.c_str(), countryName.c_str(),subscr.c_str(), duration, centPrMinute/100.00, centPrMinute*duration/100.00);
	  found = true;
	  break;
	}
      }
    }
    else { // domestic:
      for(int areaLength = 1; areaLength <= 5; ++areaLength) {
	int subscrLen = numberS.size() - 1 - areaLength;
	if(subscrLen < 4 || subscrLen > 7)
	  continue;
	std::string key = numberS.substr(0, 1+areaLength);
	mt::iterator it = STDMap.find(key);
	if(it != STDMap.end()) {
	  std::string subscr = numberS.substr(1+areaLength, numberS.size()-key.size());
	  std::string areaName = it->second.first;
	  int centPrMinute = it->second.second;
	  // std::map<std::string,std::pair<std::string,int> >
	  printf("%-16s%-25s%10s%5i%6.2f%7.2f\n", numberS.c_str(), areaName.c_str(),subscr.c_str(), duration, centPrMinute/100.00, centPrMinute*duration/100.00);
	  found = true;
	  break;
	}
      }
    }    
    if(!found) {
      printf("%-16sUnknown                  %10s%5i      %7.2f\n", numberS.c_str(), "", duration, -1.0);
      // todo: unknown
    }
    
    //std::cerr << "Called number '" << number.str() << "' for " << duration << " seconds: " << line << std::endl;
  }
}
