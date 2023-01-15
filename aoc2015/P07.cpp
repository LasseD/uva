typedef uint16_t T;

#define NOT 0
#define AND 1
#define OR 2
#define LSHIFT 3
#define RSHIFT 4
#define SET 5

struct OP {
  string v1, v2, o; // input 1, input 2, output
  T t, v3; // type, input 3
};
typedef map<string,T> MAP;

int main() {
  MAP vals;
  vector<OP*> ops;
  
  // Read input:
  string s;
  while(cin >> s) {
    OP *op = new OP;    
    if(s == "NOT") {
      op->t = NOT;
      cin >> op->v1;
      op->v2 = op->v1;
      cin >> s >> op->o;
    }
    else {
      op->v2 = op->v1 = s;
      cin >> s;
      if(s == "OR") {
	op->t = OR;
	cin >> op->v2;
	cin >> s >> op->o;
      }
      else if(s == "AND") {
	op->t = AND;
	cin >> op->v2;
	cin >> s >> op->o;
      }
      else if(s == "LSHIFT") {
	op->t = LSHIFT;
	cin >> op->v3;
	cin >> s >> op->o;
      }
      else if(s == "RSHIFT") {
	op->t = RSHIFT;
	cin >> op->v3;
	cin >> s >> op->o;
      }
      else if(s == "->") {
	cin >> op->o; // Right side
	if(op->v1[0] < '0' || op->v1[0] > '9') {
	  cout << " SET " << op->o << " <- " << op->v1 << endl;
	  op->t = SET;
	}
	else {
	  cout << " SET INT " << op->o << " <- " << op->v1 << endl;
	  vals[op->o] = stoi(op->v1);
	  continue;
	}
      }
      else {
	cerr << "Unknown operator " << s << endl;
	die();
      }
    }
    ops.push_back(op);
  }
  // Hard coded values:
  FORIT(vector<OP*>, ops) {
    OP* op = *it;
    if(op->v1[0] >= '0' && op->v1[0] <= '9') {
      vals[op->v1] = stoi(op->v1);
    }
    if(op->v1 != op->v2 && (op->v2[0] >= '0' && op->v2[0] <= '9')) {
      vals[op->v2] = stoi(op->v2);
    }
  }
  
  while(vals.find("a") == vals.end()) {
    cout << "Known values: " << vals.size() << ":";
    FORIT(MAP,vals) {
      cout << " " << (*it).first;
    }
    cout << endl;
    bool better = false;
    FORIT(vector<OP*>, ops) {
      OP* op = *it;
      
      if(vals.find(op->o) != vals.end()) {
	//cout << " Already computed " << op->o << endl;
	continue; // Already done.	
      }
      if(vals.find(op->v1) == vals.end()) {
	//cout << " Missing L " << op->v1 << endl;
	continue; // Missing input
      }
      if(vals.find(op->v2) == vals.end()) {
	//cout << " Missing R " << op->v2 << endl;
	continue; // Missing input
      }
      
      if(op->t == AND) {
	vals[op->o] = vals[op->v1] & vals[op->v2];
      }
      else if(op->t == OR) {
	vals[op->o] = vals[op->v1] | vals[op->v2];
      }
      else if(op->t == NOT) {
	vals[op->o] = ~vals[op->v1];
      }
      else if(op->t == LSHIFT) {
	vals[op->o] = vals[op->v1] << op->v3;
      }
      else if(op->t == RSHIFT) {
	vals[op->o] = vals[op->v1] >> op->v3;
      }
      else if(op->t == SET) {
	vals[op->o] = vals[op->v1];
      }
      else {
	die();
      }
      cout << " Computed " << op->o << ": " << vals[op->o] << " from " << op->v1 << " and " << op->v2 << endl;
      better = true;
    }
    if(!better) {
      cerr << "No improvements!" << endl;
      die();
    }
  }
  cout << "Answer: " << vals["a"] << endl;
}
