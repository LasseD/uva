// replace , with space in input
int main() {
  LL w[10000], v[10000];
  int size = 0, x;
  while(cin >> x) {
    w[size++] = x;
  }
  w[1] = 12;
  w[2] = 2;
  
  FORX(100) {
    FORY(100) {
      FORI(size)
	v[i] = w[i];
      v[1] = x;
      v[2] = y;
      int idx = 0;
      
      while(true) {
	if(v[idx] == 1) {
	  v[v[idx+3]] = v[v[idx+1]] + v[v[idx+2]];
	  idx+=4;
	}
	else if(v[idx] == 2) {
	  v[v[idx+3]] = v[v[idx+1]] * v[v[idx+2]];
	  idx+=4;
	}
	else if(v[idx] == 99) {
	  break;
	}
	else {
	  die();
	}
	//FORI(size) {cout << " " << v[i];}cout << endl;
      }
      if(19690720 == v[0]) {
	cout << "Answer 2: " << (100*x + y) << endl;
	return 0;
      }
      
      //cout << "Answer 1: " << v[0] << endl; // Remove the x and y stuff for part 1
    }
  }
}
