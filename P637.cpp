#include <iostream>
#include <cstdio>

using namespace std;

void printSheet(int sheet, bool front, int left, int right) {
  if(left == 0 && right == 0)
    return;
  cout << "Sheet " << sheet+1 << ", ";
  if(front)
    cout << "front: ";
  else
    cout << "back : ";
  if(left == 0)
    cout << "Blank";
  else
    cout << left;
  cout << ", ";
  if(right == 0)
    cout << "Blank";
  else
    cout << right;
  cout << endl;
}

int main() {
  int N;
  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    cout << "Printing order for " << N << " pages:" << endl;
    if(N == 1) {
      printSheet(0, true, 0, 1);
      continue;
    }
    int numSheets = (N+3)/4;
    int leftStart = 4*numSheets;
    for(int sheet = 0; sheet < numSheets; ++sheet) {
      // Front:
      printSheet(sheet, true, leftStart-2*sheet > N ? 0 : leftStart-2*sheet, 2*sheet+1);
      printSheet(sheet, false, 2*sheet+2, leftStart-2*sheet-1 > N ? 0 : leftStart-2*sheet-1);
      
    }
  }
}
