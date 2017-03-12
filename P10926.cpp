typedef pair<ULL,ULL> BitVector;

int countBits(ULL x) {
  int ret = 0;
  while(x > 0) {
    if((x & 1) == 1)
      ++ret;
    x >>= 1;
  }
  return ret;
}
int cnt(BitVector v) {
  return countBits(v.first) + countBits(v.second);
}

BitVector create(int pos) {
  BitVector v(0,0);
  if((pos & 1) == 1) {
    v.second = ((ULL)1) << (pos>>1);
  }
  else {
    v.first = ((ULL)1) << (pos>>1);
  }
  return v;
}
std::ostream& operator<<(std::ostream& os, const BitVector& v) {
  FORI(100) {
    if((i & 1) == 1) {
      if(0 != (v.second & (((ULL)1) << (i>>1))))
	os << " " << i;
    }
    else {
      if(0 != (v.first & (((ULL)1) << (i>>1))))
	os << " " << i;
    }
  }
  return os;
}

int main() {
  int N, T, Q, outdegree[101];
  BitVector dependencies[101];
  vector<int> in[101];

  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    FORI(N) {
      in[i].clear();
      dependencies[i] = create(i);
    }

    stack<int> q;
    FORI(N) {
      cin >> T;
      outdegree[i] = T;
      if(outdegree[i] == 0)
	q.push(i);
      FORJ(T) {
	cin >> Q; --Q;
	in[Q].push_back(i);
      } // j
    } // i

    while(!q.empty()) {
      int x = q.top();
      q.pop();
      FORIT(vector<int>, in[x]) {
	int y = *it;
	BitVector v = dependencies[x];
	dependencies[y].first |= v.first;
	dependencies[y].second |= v.second;
	--outdegree[y];
	if(outdegree[y] == 0)
	  q.push(y);
      }
    }
    int ret = 0;
    FORI(N) {
      /*
      if(cnt(dependencies[i]) > 0)
	cerr << "Dependencies of " << i+1 << ":" << dependencies[i] << " = " << cnt(dependencies[i]) << endl;//*/
      if(cnt(dependencies[i]) > cnt(dependencies[ret]))
	ret = i;
    }
    cout << ret+1 << endl;
  } // while(true)
} // int main
