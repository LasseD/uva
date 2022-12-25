// Remove : from input.
struct Monkey {
  bool done, dirty;
  LL v;
  string a, b, name;
  char op;
};

typedef map<string,Monkey*> MAP;
MAP m;

PLL test(LL hum) {
  // Reset:
  FORIT(MAP,m) {
    Monkey *monkey = it->second;
    monkey->done = !monkey->dirty;
  }
  m["humn"]->v = hum;
  m["humn"]->done = true;
  
  while(!m["root"]->done) {
    FORIT(MAP,m) {
      Monkey *monkey = it->second;

      //cout << it->first << "." << monkey->name << ": " << monkey->a << " " << monkey ->op << " " << monkey->b << " done? " << monkey->done << endl;

      if(monkey->done)
	continue;
      // Monkey not done:
      Monkey *a = m[monkey->a];
      Monkey *b = m[monkey->b];
      if(!a->done || !b->done)
	continue; // Not ready
      switch(monkey->op) {
      case '+':
	monkey->v = a->v + b->v;
	break;
      case '-':
	monkey->v = a->v - b->v;
	break;
      case '*':
	monkey->v = a->v * b->v;
	if(b->v != monkey->v / a->v) {
	  cerr << "Overflow error!" << endl;
	  return PLL(0,1);
	}
	break;
      case '/':
	monkey->v = a->v / b->v;
	// Check:
	if(b->v * monkey->v != a->v) {
	  //cerr << "Division error!" << endl;
	  return PLL(0,1);
	}
	break;
      default:
	cerr << "Unknown operation: " << monkey->op << endl;
	die();
      }
      monkey->done = true;
    }
    //cout << endl;
  }

  Monkey *root = m["root"];
  cout << "Test HUM " << hum << ": " << m[root->a]->v << " vs " <<  m[root->b]->v << " diff " << (m[root->a]->v-m[root->b]->v) << endl;

  return PLL(m[root->a]->v - m[root->b]->v,0);
}

int main() {
  // Scan monkeys:
  string line;
  while(getline(cin, line)) {
    Monkey *monkey = new Monkey();
    
    stringstream ss;
    ss << line;
    if(ss >> monkey->name >> monkey->a >> monkey->op >> monkey->b) {
      monkey->done = false;
    }
    else {
      monkey->done = true;
      monkey->op = 'x';
      monkey->v = stoi(monkey->a);
    }
    m[monkey->name] = monkey;
  }
  cout << "Scanned " << m.size() << " monkeys" << endl;

  // Part 2 below:
  // Root finding!
  // First clean the monkeys:
  m["humn"]->done = false; // No human input yet!
  m["humn"]->a = "root";
  m["humn"]->b = "root";
  bool improved = true;
  while(improved) {
    improved = false;
    FORIT(MAP,m) {
      Monkey *monkey = it->second;
      if(monkey->done)
	continue;
      
      // Monkey not done:
      Monkey *a = m[monkey->a];
      Monkey *b = m[monkey->b];
      if(!a->done || !b->done)
	continue; // Not ready
      
      switch(monkey->op) {
      case '+':
	monkey->v = a->v + b->v;
	break;
      case '-':
	monkey->v = a->v - b->v;
	break;
      case '*':
	monkey->v = a->v * b->v;
	if(b->v != monkey->v / a->v) {
	  cerr << "Overflow error!" << endl;
	  die();
	}
	break;
      case '/':
	monkey->v = a->v / b->v;
	// Check:
	if(b->v * monkey->v != a->v) {
	  cerr << "Division error!" << endl;
	  die();
	}
	break;
      default:
	cerr << "Unknown operation: " << monkey->op << endl;
	die();
      }
      monkey->op = 'x';
      improved = true;
      monkey->done = true;
    }
  }

  cout << "Dirty monkeys:" << endl;
  int dirty = 0;
  FORIT(MAP,m) {
    Monkey *monkey = it->second;
    monkey->dirty = !monkey->done;
    if(!monkey->done) {
      cout << monkey->name << ": " << monkey->a << " " << monkey ->op << " " << monkey->b << endl;
      dirty++;
    }
  }
  cout << dirty << " dirty monkeys" << endl;
  cout << endl;

  // Manual binary search because it was quicker than debugging below...
  /*for(LL x = 3059361843100; true; x+=10) {
    if(test(x)) {
      cout << "Answer 2: " << x << endl;
      return 0;
    }
  }
  */
  
  LL low = -10000000000000, high = 10000000000000; // TODO: Numbers might have to be larger!
  while(low < high) {
    LL mid = (low+high)/2;
    //cout << "Test low: " << low << ", mid: " << mid << ", high: " << high << endl;
    PLL v = test(mid);
    if(v.YY > 0) {
      // Division error: Bump high!
      high++;
    }
    else if(v.XX == 0) {
      cout << "Answer 2: " << mid << endl;
      return 0;
    }
    else if(v.XX < 0) { // TODO: Swap > with < here if the search does not converge.
      high = mid;
    }
    else {
      low = mid;
    }
  }

  
  // For part 1, do the stuff below:
  /*
   while(!m["root"]->done) {
    FORIT(MAP,m) {
      Monkey *monkey = it->second;

      cout << it->first << "." << monkey->name << ": " << monkey->a << " " << monkey ->op << " " << monkey->b << " done? " << monkey->done << endl;

      if(monkey->done)
	continue;
      // Monkey not done:
      Monkey *a = m[monkey->a];
      Monkey *b = m[monkey->b];
      if(!a->done || !b->done)
	continue; // Not ready
      switch(monkey->op) {
      case '+':
	monkey->v = a->v + b->v;
	break;
      case '-':
	monkey->v = a->v - b->v;
	break;
      case '*':
	monkey->v = a->v * b->v;
	if(b->v != monkey->v / a->v) {
	  cerr << "Overflow error!" << endl;
	  die();
	}
	break;
      case '/':
	monkey->v = a->v / b->v;
	// Check:
	if(b->v * monkey->v != a->v) {
	  cerr << "Division error!" << endl;
	  die();
	}
	break;
      default:
	cerr << "Unknown operation: " << monkey->op << endl;
	die();
      }
      monkey->done = true;
      cout << "DONE!" << endl;
    }
    cout << endl;
  }
  cout << "root: " << m["root"]->v << endl;
  */
}
