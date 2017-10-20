#include <iostream>

using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  if(a == 0 && b == 0) {
    cout << "Not a moose" << endl;
    return 0;
  }
  if(a == b) {
    cout << "Even " << a + b << endl;
  }
  else {
    if(b > a)
      a = b;
    cout << "Odd " << 2*a << endl;
  }
  return 0;
}
