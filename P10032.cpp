#include <iostream>
#include <cstring>

typedef unsigned long long ull;

#define MAX_WEIGHT (450*51+1)
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))

/*
There are at most 50 people one one side of the line, so using a 64 bit int (like unsigned long long) bit number i, each bit (in the range 0 - 63) can represent info for (i+1) people.

There is an int for each obtainable accumulated weight. For each weight w the bits in the e[i] is '1' if w can be obtained using bit+1 people.

For a person with weight w2, the e[w2] gets a '1' bit because the weight can be constructed using 1 person. Also. For every non-zero e[w], e[w+w2] should be updated since every '1'-bit in e[w2] indicates that w2 can be obtained with i+1 people, then e[w2+w] must be obtained with i+2 people.
 */
int main() {
  ull *e = new ull[MAX_WEIGHT+1]; // e[i] = indicators for all group sizes for which weight i can be constructed.

  int cases, n, person;
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    std::cin >> n;
    int sumAllPeople = 0;
    memset(e, 0, MAX_WEIGHT);
    for(int i = 0; i < n; ++i) {
      std::cin >> person;
      sumAllPeople += person;
      // Update e:
      for(int j = MIN(sumAllPeople, MAX_WEIGHT); j >= person; --j) {
	if(e[j-person] != 0)
	  e[j] |= e[j-person]<<1;
      }
      e[person] |= 1; // You can construct the person
    }

    // Compute output!
    int j = sumAllPeople/2;
    ull mask1 = (ull)1 << (n/2-1);
    ull mask2 = (ull)1 << (n/2);

    if(n % 2 == 0) {
      for(; j > 0; --j) {
	if((e[j] & mask1) != 0)
	  break;
      }
    }
    else {
      for(; j > 0; --j) {
	if(((e[j] & mask1) != 0) || ((e[j] & mask2) != 0))
	  break;
      }
    }
    std::cout << j << " " << (sumAllPeople-j) << std::endl;
  }

  delete[] e;
  return 0;
}
