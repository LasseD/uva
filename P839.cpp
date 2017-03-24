int read() {
  int wl, dl, wr, dr; cin >> wl >> dl >> wr >> dr;
  if(wl == 0)
    wl = read();
  if(wr == 0)
    wr = read();
  //cerr << wl << "*" << dl <<"=="<< wr<<"*"<<dr << endl;
  if(wl > 0 && wr > 0 && wl*dl == wr*dr)
    return wl+wr;
  return -1;
}

int main() {
  FORCAS {
    if(cas != 0)
      cout << endl;
    if(read() > 0)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}
