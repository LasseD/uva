int main() {
  FORCAS {
    cout << "Case " << cas+1 << ": ";
    long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    //cerr << x1 <<","<< y1 << " -> " << x2 <<","<< y2 << endl;
    long shell1 = x1+y1;
    long shell2 = x2+y2;
							//cerr << "Shell1=" << shell1 << ", shell2=" << shell2 << endl;
    if(shell1 == shell2) {
      cout << x2-x1 << endl;
      continue;
    }
    long stepsBeforeShell2 = (shell2)*(shell2+1)/2;
    long stepsIncludingShell1 = (shell1+2)*(shell1+1)/2;
		       //cerr << "stepsBeforeShell2=" << stepsBeforeShell2 << ", stepsIncludingShell1=" << stepsIncludingShell1 << endl;
													      cout << stepsBeforeShell2+x2+1 - stepsIncludingShell1+(shell1-x1) << endl;
  }
  return 0;
}
