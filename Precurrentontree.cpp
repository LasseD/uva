#define MOD 1000000007
#define FIB_STORE_LEN 100000
#define F0 first
#define F1 second
typedef pair<LL,LL> FF;

LL FIB_STORE[FIB_STORE_LEN];

// Quick fib from http://fusharblog.com/solving-linear-recurrence-for-programming-contest/
typedef vector<vector<LL> > matrix;
const int K = 2;

// computes A * B
matrix mul(matrix A, matrix B) {
  matrix C(K, vector<LL>(K));
  FORI(K)  {
    FORJ(K) {
      FORK(K) {
	C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
      }
    }
  }
  return C;
}

// computes A ^ p
matrix pow(matrix A, int p) {
  if (p == 1)
    return A;
  if (p % 2)
    return mul(A, pow(A, p-1));

  matrix X = pow(A, p/2);
  return mul(X, X);
}

// returns the N-th term of Fibonacci sequence
LL fib(long N) {
  if (N < FIB_STORE_LEN)
    return FIB_STORE[N];
  ++N;

  // create vector F1
  vector<LL> F1(K);
  F1[0] = 1;
  F1[1] = 1;
  // create matrix T
  matrix T(K, vector<LL>(K));
  T[0][0] = 0, T[0][1] = 1;
  T[1][0] = 1, T[1][1] = 1;

  // raise T to the (N-1)th power
  T = pow(T, N-1);
  // the answer is the first row of T . F1
  LL ret = 0;
  FORI(K)
    ret = (ret + T[0][i] * F1[i]) % MOD;
  //cerr << "  fib("<<N-1<<")=" << ret << endl;
  return ret;
}

LL getEdgeAdd(FF ff, int x) {
  if(x == 0)
    return ff.F0;
  else if(x == 1)
    return ff.F1;
  return (fib(x-1)*ff.F1 + fib(x-2)*ff.F0);
}

vector<long> dfs(int N, FF NFF, vector<int> *neighbours, int *C, bool *visited, LL &sum) {
  //cerr << "Run " << N << ", NFF=(" << NFF.F0 << "," << NFF.F1 << ")" << endl;
  visited[N] = true;

  vector<long> ret;
  ret.push_back(C[N]);
  FORIT(vector<int>, neighbours[N]) {
    int neighbour = *it;
    if(visited[neighbour])
      continue;

    // First add N->neighbour to ret:
    LL edgeAdd = getEdgeAdd(NFF, C[neighbour]);
    LL edgeAdd1 = getEdgeAdd(NFF, C[neighbour]+1);
    sum = (sum + 2*edgeAdd) % MOD;
    //cerr << " Adding " << 2*edgeAdd << " for " << N << "->" << neighbour << endl;

    // Compute FF for the neighbour:
    // Neighbour F0 = edgeAdd.
    //           F1 = 
    FF neighbourFF(edgeAdd, edgeAdd1);

    // Call recursively:
    vector<long> neighbourWeights = dfs(neighbour, neighbourFF, neighbours, C, visited, sum);
    // Update ret and NFF
    FORIT(vector<long>, neighbourWeights) {
      LL x = *it;
      //cerr << " Weight returned from " << neighbour << ": " << x << endl;
      ret.push_back(x);

      NFF.F0 += fib(x + C[N]);
      NFF.F1 += fib(x + 1 + C[N]);
      NFF.F0 %= MOD;      
      NFF.F1 %= MOD;      
      //cerr << " Updated " << N << ", NFF=(" << NFF.F0 << "," << NFF.F1 << ")" << endl;

    }
  }
  return ret;
}

int main() {
  FIB_STORE[0] = FIB_STORE[1] = 1;
  for(int i = 2; i < FIB_STORE_LEN; ++i)
    FIB_STORE[i] = (FIB_STORE[i-1] + FIB_STORE[i-2]) % MOD;

  // Read input:
  int n;
  cin >> n;
  vector<int> *neighbours = new vector<int>[n];
  FORI(n-1) {
    int A, B;

    cin >> A;
    --A;
    cin >> B;
    --B;

    neighbours[A].push_back(B);
    neighbours[B].push_back(A);
  }

  int *C = new int[n];
  bool *visited = new bool[n];
  LL ret = 0;
  FORI(n) {
    cin >> C[i];
    visited[i] = false;
    ret += fib(C[i]);
    ret %= MOD; // Now contains all unit adds.
  }
  //cerr << "RET init: " << ret << endl;

  srand(n*32684);
  int bestStart = rand()%n;
  // TODO: Find better bestStart!
  dfs(bestStart, FF(fib(C[bestStart]),fib(C[bestStart]+1)), neighbours, C, visited, ret);
  cout << ret << endl;
}
