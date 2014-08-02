#include <iostream>
#include <stdio.h>

int main() {
  int students[25];
  while(true) {
    int N, k;
    std::cin >> N >> k;
    if(N == 0 && k == 0)
      return 0;
    // GOGOGO!
    int store = 1;
    int toDispenseI = 1 % k;
    for(int i = 0; i < N; ++i) {
      students[i] = 0;
    }
    int studentsLeft = N;
    int studentI = 0;
    while(true) {
      // pay student:
      students[studentI] += store;
      if(students[studentI] >= 40) {
	// kick student:
	store = students[studentI]-40;
	students[studentI] = 40;
	printf("%3i", studentI+1);
	--studentsLeft;	
	if(studentsLeft == 0)
	  break;
      }
      else {
	store = 0;
      }

      // update queue:
      do {
	++studentI;
	if(studentI == N)
	  studentI = 0;
	//std::cerr << " Skipping " << studentI <<" N=" <<N << ", left=" << studentsLeft;
      }
      while(students[studentI] == 40);

      // update store:
      if(store == 0) {
	store = toDispenseI+1;
	++toDispenseI;
	if(toDispenseI == k)
	  toDispenseI = 0;
      }
    }
    printf("\n");
  }
}
