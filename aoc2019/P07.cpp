#define SIZE 10000

LL w[SIZE];
int size = 0;

struct Amplifier {
  LL v[SIZE];
  int idx;
  int inputIdx;

  Amplifier() {
    idx = 0;
    inputIdx = 0;
    FORI(size) {
      v[i] = w[i];
    }
  }

  LL get(vector<int> &modes, int param, int i) {
    int mode = param-1 < modes.size() ? modes[param-1] : 0;
    if(i+param < 0 || i+param >= size) {
      cerr << "Parameter out of bounds: " << i << " + " << param << endl;
      die();
    }
    LL x = v[i+param];
    if(mode == 1) { // 1 => immediate mode
      return x;
    }
    else { // 0 => position mode
      if(x < 0 || x >= size) {
	cerr << "Position mode parameter out of bounds: " << x << endl;
	die();
      }
      return v[x];
    }
  }

  LL run(LL input1, LL input2, bool &halt) {
    halt = false;
    //idx = 0;
    LL input[2] = {input1, input2};
    //inputIdx = 0;
    cout << "run " << input1 << ", " << input2 << endl;

    while(true) {
      int opcode = v[idx]%100;
      int modeBits = v[idx]/100;
      vector<int> modes;
      while(modeBits > 0) {
	modes.push_back(modeBits % 2);
	modeBits/=10;
      }
      /*cout << "Run OPCODE " << opcode << " on " << endl;
	FORK(size) {
	if(k == idx)
	cout << " (";
	else
	cout << " ";
	cout << v[k];
	if(k == idx)
	cout << ")";
	}
	cout << endl;//*/
    
      if(opcode == 1) {
	LL val = get(modes, 1, idx) + get(modes, 2, idx);
	v[v[idx+3]] = val;
	idx+=4;
      }
      else if(opcode == 2) {
	LL val = get(modes, 1, idx) * get(modes, 2, idx);
	v[v[idx+3]] = val;
	idx+=4;
      }
      else if(opcode == 3) {
	LL val;
	if(inputIdx > 0) {
	  val = input[1]; // Not clearly stated in problem definition!
	}
	else {
	  val = input[0];
	  inputIdx++;
	}
      
	v[v[idx+1]] = val;
	//cout << "Reading input value " << val << " into " << v[idx+1] << endl;
	idx+=2;
      }
      else if(opcode == 4) {
	idx+=2;
	return get(modes, 1, idx-2);
      }
      else if(opcode == 5) {
	LL check = get(modes, 1, idx);
	LL pointer = get(modes, 2, idx);
	if(check != 0) {
	  idx = pointer;
	}
	else {
	  idx+=3;
	}
      }
      else if(opcode == 6) {
	LL check = get(modes, 1, idx);
	LL pointer = get(modes, 2, idx);
	if(check == 0) {
	  idx = pointer;
	}
	else {
	  idx+=3;
	}
      }
      else if(opcode == 7) {
	LL p1 = get(modes, 1, idx);
	LL p2 = get(modes, 2, idx);
	v[v[idx+3]] = p1 < p2 ? 1 : 0;
	idx+=4;
      }
      else if(opcode == 8) {
	LL p1 = get(modes, 1, idx);
	LL p2 = get(modes, 2, idx);
	v[v[idx+3]] = p1 == p2 ? 1 : 0;
	idx+=4;
      }
      else if(opcode == 99) {
	halt = true;
	return 0;
      }
      else {
	cerr << "Unknown opcode: " << opcode << endl;
	die();
      }
    }
  }
};

struct PermutationNode {
  PermutationNode *next;
  int val;  
};
struct PermutationHandler {
  PermutationNode *nodes;
  PermutationHandler(int size) {
    nodes = new PermutationNode[size+1];
    for(int i = 0; i < size; ++i) {
      nodes[i+1].val = i+5; // Without +5 for part 1
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

LL best = -99999999;
int phase[5];

void go(PermutationHandler &ph, const int i) {
  if(i == 5) {
    // RUN:
    set<LL> seen;
    cout << "Trying permutation:";
    FORJ(5) {
      cout << " " << phase[j];
    }
    cout << endl;

    LL input = 0;
    Amplifier amps[5];
    bool halted;
    while(seen.find(input) == seen.end()) { // For part 1, only run once.
      seen.insert(input);
      FORJ(5) {
	LL x = amps[j].run(phase[j], input, halted);
	if(halted)
	  break;
	input = x;
      }
      best = max(best, input);
      cout << " LOOP -> " << input << endl;
    }
    cout << "Permutation -> " << input << " seen before" << endl;
    return;
  }
  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from phaseutation:
    node->next = n->next;

    phase[i] = n->val;
    go(ph, i+1);

    // re-insert in phaseutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
}

// replace , with space in input
int main() {
  LL x;
  while(cin >> x) {
    w[size++] = x;
  }

  PermutationHandler ph(5);
  go(ph, 0);
  cout << "Answer: " << best << endl;
}
