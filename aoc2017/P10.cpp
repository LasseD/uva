// Replace commas with spaces in input and prefix with size for Part 1. For part 2, keep input.
int main() {
  int size = 256;
  int v[256];
  FORI(size) {
    v[i] = i;
  }
  int x, pos = 0, skipSize = 0;
  // Part 2 input processing:
  GS(input);
  vector<int> v1;
  FORUI(input.size()) {
    v1.push_back((int)input[i]);
  }
  v1.push_back(17);
  v1.push_back(31);
  v1.push_back(73);
  v1.push_back(47);
  v1.push_back(23);
  // For part 1, ignore these 5 above and don't add '0'.

  FORK(64) { // 1 for Part 1
    FORIT(vector<int>, v1) {
      x = *it;
      for(int i = pos, j = pos+x-1; i < j; i++, j--) {
	swap(v[i%size],v[(j+size)%size]);
      }
      pos = (pos + x + skipSize)%size;
      skipSize++;
      //FORI(size)
      //  cout << " " << v[i];
      //cout << endl;
    }
  }

  // Compute dense hash:
  printf("Dense hash:\n");
  uint8_t y = 0;
  FORI(size) {
    y = y ^ v[i];
    if(i%16 == 15) {
      printf("%02x",y);
      y = 0;
    }
  }
  printf("\n");  
  //cout << (v[0]*v[1]) << endl; // Part 1
  
}
