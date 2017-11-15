struct INFO {
  int a, b, op;
  INFO *from;
};

string ops[7] = {"fill A", "fill B", "empty A", "empty B", "pour A B", "pour B A", "success"};  
INFO infos[5000];
int infoI;

void add(int a, int b, int op, INFO *from, set<PI> &seen, queue<INFO*> &q) {
  if(seen.find(PI(a, b)) != seen.end())
    return; // Already seen.
  seen.insert(PI(a, b));
  INFO *g = &infos[infoI++];
  g->a = a; g->b = b; g->op = op; g->from = from; q.push(g);
}

int main() {
  infos[0].a = infos[0].b = 0; infos[0].from = NULL;
  
  int ca, cb, n;
  while(cin >> ca >> cb >> n) {
    infoI = 1;
    queue<INFO*> q;
    q.push(&infos[0]);
    set<PI> seen;
    INFO *f;
    while(true) {
      if(q.empty()) {
	cerr << "NOO!" << endl;
	return 0;
      }
      f = q.front(); q.pop();
      if(f->b == n)
	break; // done!
      // Try all ops:
      // Fill a:
      if(f->a != ca) {
	add(ca, f->b, 0, f, seen, q);
      }
      // Fill b:
      if(f->b != cb) {
	add(f->a, cb, 1, f, seen, q);
      }
      // Empty a:
      if(f->a != 0) {
	add(0, f->b, 2, f, seen, q);
      }
      // Empty b:
      if(f->b != 0) {
	add(f->a, 0, 3, f, seen, q);
      }
      // Pour A B:
      int potB = cb - f->b;
      int diffA2B = MIN(potB, f->a);
      if(f->a != 0 && f->b != cb) {
	add(f->a - diffA2B, f->b + diffA2B, 4, f, seen, q);
      }
      // Pour B A:
      int potA = ca-f->a;
      int diffB2A = MIN(potA, f->b);
      if(f->a != ca && f->b != 0) {
	add(f->a+diffB2A, f->b-diffB2A, 5, f, seen, q);
      }
    } // while true
    stack<int> s;
    while(f->from != NULL) {
      s.push(f->op);
      f = f->from;
    }
    while(!s.empty()) {
      cout << ops[s.top()] << endl;
      s.pop();
    }
    cout << ops[6] << endl;
  }
}
