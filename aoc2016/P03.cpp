int main() {
  int y[9], answer = 0;
  
  while(true) {
    FORI(9) {
      int row = i/3;
      int column = i%3;
      int idx = 3*column + row; 
      if(!(cin >> y[idx])) {
	cout << answer << endl;
	return 0;
      }
    }
    
    FORI(3) {
      int *x = &(y[3*i]);
      cout << "Triangle check " << x[0] << " " << x[1] << " " << x[2] << endl;
      sort(x, x+3);      
      if(x[0]+x[1] > x[2]) {
	answer++;
      }
    }
  }
}
