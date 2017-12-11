#define ADD 0
#define MINUS 1
#define MULT 2
#define DIV 3

typedef map<long,PL> MAP;

void add(int x, PL from, MAP &s) {
  if(x < -32000 || x > 32000)
    return;
  if(s.find(x) != s.end())
    return;
  s[x] = PL(from);
}

int main() {
  char OPS[4] = {'+', '-', '*', '/'};

  MAP a[101];
  int numbers[101], x;
  FORCAS {
    GI(N);
    FORI(N)
      a[i].clear();
    cin >> x;
    numbers[0] = x;
    a[0][x] = PL(0, 0);
    for(int i = 1; i < N; ++i) {
      cin >> x;
      numbers[i] = x;
      FORIT(MAP, a[i-1]) {
	long y = it->first;
	add(x*y, PL(MULT, y), a[i]);
	if(y%x == 0)
	  add(y/x, PL(DIV, y), a[i]);
	add(x+y, PL(ADD, y), a[i]);
	add(y-x, PL(MINUS, y), a[i]);
      }
    } // for i
    GI(ret);
    if(a[N-1].find(ret) == a[N-1].end())
      cout << "NO EXPRESSION" << endl;
    else {
      stack<int> ops;
      long x = ret;
      for(int i = N-1; i > 0; --i) {
	PL op = a[i][x];
	x = op.second;
	ops.push(op.first);
      }
      cout << numbers[0];
      for(int i = 1; i < N; ++i) {
	cout << OPS[ops.top()];
	ops.pop();
	cout << numbers[i];
      }
      cout << "=" << ret << endl;
    }
  }
  return 0;
}
