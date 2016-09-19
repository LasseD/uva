#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
  char judge[39], contestant[39];
  int cases;
  scanf("%d\n", &cases);
  for(int cas = 1; cas <= cases; ++cas) {
    gets(contestant);
    gets(judge);

    bool containsSpaces = false;
    bool same = true;
    int contestantI = 0;
    int judgeI = 0;

    for(int i = 0; contestant[i] != '\0'; ++i) {
      if(!isalpha(contestant[i]))
	containsSpaces = true;
      else
	contestant[contestantI++] = contestant[i];
    }
    contestant[contestantI] = '\0';

    for(; judge[judgeI] != '\0'; ++judgeI) {
      if(judge[judgeI] == contestant[judgeI])
	continue;
      //cerr << (int)judge[judgeI] <<"!="<< (int)contestant[judgeI] <<endl;
      same = false;
      break;
    }
    if(contestantI != judgeI)
      same = false;
    /*
    cerr << contestant << endl;
    cerr << judge << endl;
    cerr << "cI=" << contestantI << ", jI=" << judgeI << endl;//*/

    cout << "Case " << cas << ": ";
    if(!same) {
      cout << "Wrong Answer" << endl;
    }
    else if(containsSpaces) {
      cout << "Output Format Error" << endl;
    }
    else {
      cout << "Yes" << endl;
    }
  }
  return 0;
}
