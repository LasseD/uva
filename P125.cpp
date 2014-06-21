#include <iostream>
#include <vector>

int main() {
  int city = 0;
  int initMatrix[60*60]; // one step.
  int sumMatrix[60*60]; // sum for up to n steps.
  int matrix[2*60*60]; // routes from a to b on a+b*n for x steps.
  int n,m;
  std::vector<std::pair<int,int> > junctions;

  while(std::cin >> m) {
    std::cout << "matrix for city " << city << std::endl;
    // Reset junctions and n:
    junctions.clear();
    n = 0;

    int a, b;
    for(int i = 0; i < m; ++i) {
      std::cin >> a >> b;
      if(a > n)
	n = a;
      if(b > n)
	n = b;
      junctions.push_back(std::make_pair(a,b));
    }
    ++n;

    // reset matrices:
    for(int i = 0; i < 2*n*n; ++i) {
      matrix[i] = 0;
    }
    for(int i = 0; i < n*n; ++i) {
      sumMatrix[i] = 0;
      initMatrix[i] = 0;
    }

    // initiate matrix:
    int iPrev = n*n;
    int iCurrent = 0;

    for(int i = 0; i < m; ++i) {
      std::pair<int,int> p = junctions[i];
      a = p.first;
      b = p.second;
      ++matrix[a+n*b];
      ++sumMatrix[a+b*n];
      ++initMatrix[a+b*n];
    }

    // build matrix:
    for(int steps = 2; steps <= n; ++steps) {
      /*std::cerr << "Sums before step " << steps << std::endl;
      for(int a = 0; a < n; ++a) {
	for(int b = 0; b < n; ++b) {
	  if(b != 0)
	    std::cerr << " ";
	  std::cerr << sumMatrix[a+b*n];
	}	
	std::cerr << std::endl;
	}//*/

      std::swap(iPrev, iCurrent);
      for(int a = 0; a < n; ++a) {
	for(int b = 0; b < n; ++b) {
	  if(sumMatrix[a+b*n] == -1) {
	    matrix[iCurrent+a+b*n] = -1;
	    continue;
	  }

	  matrix[iCurrent+a+b*n] = 0;
	  for(int c = 0; c < n; ++c) {
	    if(sumMatrix[a+c*n] == -1 && sumMatrix[c+b*n] !=  0 || 
	       sumMatrix[a+c*n] !=  0 && sumMatrix[c+b*n] == -1) {
	      matrix[iCurrent+a+b*n] = -1;
	      break;	      
	    }

	    int toC = matrix[iPrev+a+c*n];
	    if(toC != 0 && initMatrix[c+b*n] != 0) {
	      // can go a-c-b:
	      if(toC == -1 || a == b || sumMatrix[c+c*n] == -1 || sumMatrix[a+a*n] == -1 || sumMatrix[b+b*n] == -1) {
		matrix[iCurrent+a+b*n] = -1;
		break;
	      }
	      else {
		matrix[iCurrent+a+b*n] += initMatrix[c+b*n]*matrix[iPrev+a+c*n];
	      }	      
	    }
	  } 
	  if(matrix[iCurrent+a+b*n] == -1) {
	    sumMatrix[a+b*n] = -1;
	  }
	  else {
	    sumMatrix[a+b*n] += matrix[iCurrent+a+b*n];
	  }
	}	
      }
    }

    // output matrix:
    for(int a = 0; a < n; ++a) {
      for(int b = 0; b < n; ++b) {
	if(b != 0)
	  std::cout << " ";
	std::cout << sumMatrix[a+b*n];
      }	
      std::cout << std::endl;
    }
    
    ++city;
  }
  return 0;
}
