int main() {
  FORCAS {
    GI(Q);
    GI(N);
    FORI(Q) {
      GI(x1); GI(y1); GI(x2); GI(y2);
      if(((x1 & 1) == (y1 & 1)) != ((x2 & 1) == (y2 & 1)))
	cout << "no move" << endl;
      else if(x1 == x2 && y1 == y2)
	cout << 0 << endl;
      else if(y2 == y1 + (x2-x1) || y2 == y1 - (x2-x1))
	cout << 1 << endl;
      else
	cout << 2 << endl;
    } // FORI(Q)
  } // FORCAS
} // int main
