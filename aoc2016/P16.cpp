#define EVEN(a) (((a) & 1) == 0)
#define ODD(a) (((a) & 1) == 1)

bitset<100000000> a, b;
int size;

//    primes.set();
//	primes.set(notAPrimeI, false);

void expand() {
  FORI(size) {
    b[size-1-i] = a[i];
  }
  b.flip();
  a[size] = 0;
  FORI(size) {
    a[size+i+1] = b[i];
  }
  size = 2*size+1;
}

void checksumReduce() {
  for(int i = 0; i < size; i+=2) {
    a[i/2] = a[i] == a[i+1];
  }
  size /= 2;
}

void print() {
  cout << size << " ";
  FORI(size) {
    cout << a[i];
  }
  cout << endl;
}

int main() {
  // Init a:
  GS(s); GI(disk);
  size = (int)s.size();
  FORI(size) {
    a.set(i, s[i] == '1');
  }
  cout << "Input" << endl;
  print();

  cout << "Expanding" << endl;
  while(size < disk) {
    expand();
    //print();
  }

  size = disk;

  cout << "Computing checksum" << endl;
  while(size % 2 == 0) {
    checksumReduce();
  }
  print();
}
