struct PermutationNode {
  PermutationNode *next;
  int val;  
};
struct PermutationHandler {
  PermutationNode *nodes;  
  PermutationHandler(int size) {
    nodes = new PermutationNode[size+1];
    for(int i = 0; i < size; ++i) {
      nodes[i+1].val = i;
      nodes[i].next = &(nodes[i+1]);
    }
    nodes[size].next = NULL;
  }
  ~PermutationHandler() {
    delete[] nodes;
  }
  PermutationNode* root() {
    return &(nodes[0]);
  }
};

#define PRIME_LEN 5000000
class PrimeHandler {
  bitset<PRIME_LEN> primes;

public:
  void init() {
    primes.set();
    // Sieve primes:
    for(int i = 0; i*i < PRIME_LEN; ++i) {
      if(!primes[i])
	continue;
      // Mark all uneven multiples as non-prime:
      int basePrime = 1+2*(i+1);
      for(int multiple = 3; true; multiple += 2) {
	int notAPrime = basePrime*multiple;
	int notAPrimeI = notAPrime/2-1;
	if(notAPrimeI >= PRIME_LEN)
	  break;
	primes.set(notAPrimeI, false);
      }
    }
  }

  bool isPrime(int n) const {
    if(n == 2)
      return true;
    if(n < 2 || (n%2==0))
      return false;
    return primes[n/2-1];
  }

  bool isAnagrammaticPrime(const int i, int const * const orig, int *perm, const int len, PermutationHandler &ph) {
    if(i == len) {
      int n = 0;
      for(int j = 0; j < len; ++j) {
	n = 10*n + perm[j];
      }
      return isPrime(n);
    }
    // try all combinations:
    PermutationNode *node = ph.root();
    while(node->next != NULL) {
      PermutationNode *n = node->next;    
      node->next = n->next;

      perm[i] = orig[n->val];
      if(!isAnagrammaticPrime(i+1, orig, perm, len, ph)) {
	node->next = n;
	return false;
      }

      node->next = n; // n->next is already set (never changes)
      node = n;
    }
    return true;
  }

  bool isAnagrammaticPrime(int n) {
    //cerr << "Checking " << n << endl;
    int digits = 0;
    int orig[8];
    int perm[8];
    for(int i = 0; n > 0; ++i) {
      ++digits;
      orig[i] = n%10;
      n/=10;
    }
    PermutationHandler ph(digits);
    return isAnagrammaticPrime(0, orig, perm, digits, ph);
  }

  int nextPrime(int n) const {
    if(n < 2)
      return 2;
    if(n == 2)
      return 3;
    if((n & 1) == 0)
      --n;
    int ni = n/2;
    while(!primes[ni])  {
      ++ni;    
    }
    return 1+(ni+1)*2;
  }
  
  int nextAnagrammaticPrime(int L) {
    int U = 10;
    while(U <= L)
      U*=10;
    L = nextPrime(L);
    //cerr << "Running " << L << " -> " << U << endl;

    while(L < U) {
      if(isAnagrammaticPrime(L))
	return L;
      L = nextPrime(L);
    }
    return 0;
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  long L;
  while(true) {
    cin >> L;
    if(L == 0)
      return 0;
    cout << ph.nextAnagrammaticPrime(L) << endl;      
  }
}
