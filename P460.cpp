typedef pair<PI,PI> Rect;

int main() {
  FORCAS {
    if(cas != 0)
      cout << endl;
    Rect a, b;
    cin >> a.P1.XX >> a.P1.YY >> a.P2.XX >> a.P2.YY;
    cin >> b.P1.XX >> b.P1.YY >> b.P2.XX >> b.P2.YY;
    if(a.P2.XX <= b.P1.XX || 
       a.P2.YY <= b.P1.YY ||
       b.P2.XX <= a.P1.XX || 
       b.P2.YY <= a.P1.YY) {
      cout << "No Overlap" << endl;
      continue;
    }
    PI x(MAX(a.P1.XX,b.P1.XX), MIN(a.P2.XX,b.P2.XX));
    PI y(MAX(a.P1.YY,b.P1.YY), MIN(a.P2.YY,b.P2.YY));
    cout << x.P1 << " " << y.P1 << " " << x.P2 << " " << y.P2 << endl;
  }
  return 0;
}
