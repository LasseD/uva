int main() {
  FORCAS {
    GI(R);
    int dy = R*3/2;
    int dxLeft = R*45/20;
    int dxRight = R*55/20;
    cout << "Case " << cas+1 << ":" << endl;
    cout << -dxLeft << " " << dy << endl;
    cout << dxRight << " " << dy << endl;
    cout << dxRight << " " << -dy << endl;
    cout << -dxLeft << " " << -dy << endl;
  }
  return 0;
}
