// Part 1:
/*
int main() {
  GI(size);
  int *v = new int[size]; // value is the next in circle.
  FORI(size) {
    v[i] = (i+1)%size;
  }
  int p = 0;
  while(v[p] != p) {
    v[p] = v[v[p]]; // skip
    p = v[p];
  }
  cout << (p+1) << endl;
}*/
// Part 2:
int main() {
  GI(size);
  int *v = new int[size];
  FORI(size) {
    v[i] = (i+1);
  }
  int p = 0;
  while(size > 1) {
    if(size%10000 == 0)
      cout << size << endl;    
    else if(size%1000 == 0)
      cout << "." << endl;    
    int toRemove = (p+size/2) % size;
    if(toRemove == p) {
      cerr << "ERROR" << endl; die();
    }
    //cout << v[p] << " (" << p << ") steals from " << v[toRemove] << " ("<< toRemove << ") size " << size << " -> " << (size-1) << endl;
    for(int i = toRemove; i+1 < size; i++) {
      v[i] = v[i+1];
    }
    size--;
    if(p == size) {
      p = 0;
    }
    else if(toRemove > p) {
      p = (p+1)%size;
    }
  }
  cout << v[0] << endl;
}
