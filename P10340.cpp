#include <iostream>
#include <ctype.h>

#define LINE_LENGTH 300000

int main() {
  char w[LINE_LENGTH];
  while(std::cin.getline(w, LINE_LENGTH)) {    
    // Parse input:
    int start1 = -1, end1 = -1, start2 = -1, end2 = -1;
    for(int i = 0; true; ++i) {
      if(!isprint(w[i])) {
	w[i] = '\0';
	end2 = i;
	break;
      }
      if(isalnum(w[i])) {
	if(start1 == -1) {
	  start1 = i;
	}
	else if(end1 != -1 && start2 == -1) {
	  start2 = i;
	}
      }
      else {
	if(start1 != -1 && end1 == -1) {
	  end1 = i;
	  w[i] = '\0';
	}
	else if(start2 != -1 && end2 == -1) {
	  end2 = i;
	  w[i] = '\0';
	  break;
	}	  
      }
    }
    //std::cerr << " Running for '" << std::string(&w[start1]) << "' and '" << std::string(&w[start2]) << "'" << std::endl;

    int i1 = start1;
    for(int i2 = start2; i2 < end2; ++i2) {
      if(w[i2] == w[i1]) {
	//std::cerr << " match at w[" << i1 << "] = w[" << i2 << "] = " << w[i2] << std::endl;
	++i1;
      }
      if(i1 == end1)
	break;
    }
    if(i1 == end1)
      std::cout << "Yes" << std::endl;
    else
      std::cout << "No" << std::endl;
  }
}
