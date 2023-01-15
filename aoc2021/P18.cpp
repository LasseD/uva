string s;
int idx = 0;

struct P {
  P *a, *b, *parent;
  LL va, vb; // Used when a and b are null
};

void print(P *a) {
  if(a == NULL) {
    cout << "NULL";
    return;
  }
    
  cout << "[";
  if(a->a == NULL)
    cout << a->va;
  else
    print(a->a);
  cout << ",";
  if(a->b == NULL)
    cout << a->vb;
  else
    print(a->b);
  cout << "]";
}

LL magnitude(P *a) {
  LL left = (a->a == NULL ? a->va : magnitude(a->a));
  LL right = (a->b == NULL ? a->vb : magnitude(a->b));
  return 3*left + 2*right;
}

void insertUpLeft(P *a, P *child, LL v) {
  cout << "Inserting " << v << " up left into "; print(a); cout << endl;
  if(a == NULL) {
    return; // Nothing to insert up into!
  }
  
  if(child == a->b) { // From the right child: Insert in left side:
    if(a->a == NULL) {
      a->va+=v;
    }
    else {
      P *c = a->a;
      while(c->b != NULL)
	c = c->b;
      c->vb+=v;
    }
  }
  else { // From the left child: Insert in parents right!
    insertUpLeft(a->parent, a, v);
  }
}

void insertUpRight(P *a, P *child, LL v) {
  cout << "Inserting " << v << " up right into "; print(a); cout << endl;
  if(a == NULL) {
    return; // Nothing to insert up into!
  }
  
  if(child == a->a) { // From left child: Insert into right
    if(a->b == NULL) {
      a->vb+=v;
    }
    else {
      P *c = a->b;
      while(c->a != NULL)
	c = c->a;
      c->va+=v;
    }
  }
  else {
    insertUpRight(a->parent, a, v);
  }
}

bool explode(P *a, int lv) {
  if(a == NULL || lv > 4) {
    cerr << "NULL or Unexpected debth: " << lv << endl;
    die();
  }
  if(lv <= 3) {
    if(a->a != NULL) {
      if(explode(a->a, lv+1))
	return true;
    }
    if(a->b != NULL) {
      return explode(a->b, lv+1);
    }
    return false;
  }
  else { // lv is 4: explode!
    if(a->a != NULL || a->b != NULL) {
      cerr << "Non-regular values!" << endl;
      die();
    }
    cout << "Exploding "; print(a); cout << " at level 4 " << endl;
    P* p = a->parent;
    insertUpLeft(p, a, a->va);
    insertUpRight(p, a, a->vb);
    if(a == p->a) {
      p->va = 0; // Replace a with 0
      p->a = NULL;
    }
    else {
      p->vb = 0;
      p->b = NULL;
    }
    delete a;
    cout << "Explosion done! Parent now: "; print(p); cout << endl;
    return true;
  }
}

bool split(P *a) {
  if(a == NULL) {
    cout << "CANNOT SPLIT NULL" << endl;
    die();
  }
  if(a->a == NULL) {
    if(a->va >= 10) {
      cout << "SPLITTING LEFT "; print(a); cout << endl;
      P *x = new P;
      x->parent = a;
      a->a = x;
      x->a = x->b = NULL;
      x->va = a->va/2;
      x->vb = a->va - x->va;
      return true;
    }
  }
  if(a->a != NULL) {
    if(split(a->a))
      return true;
  }
  // Left OK. Proceed with right:
  if(a->b == NULL) {
    if(a->vb >= 10) {
      cout << "SPLITTING RIGHT "; print(a); cout << endl;
      P *x = new P;
      x->parent = a;
      a->b = x;
      x->a = x->b = NULL;
      x->va = a->vb/2;
      x->vb = a->vb - x->va;
      return true;
    }
  }
  if(a->b != NULL) {
    return split(a->b);
  }
  return false;
}

P* add(P *a, P *b) { // a and b are not NULL
  P *ret = new P;
  ret->a = a;
  ret->b = b;
  ret->parent = NULL;
  a->parent = ret;
  b->parent = ret;

  cout << "After addition: ";
  print(ret);
  cout << endl;
  
  // Reduce:
  while(explode(ret, 0) || split(ret)) {
    cout << "AFTER REDUCTION: "; print(ret); cout << endl;
  }

  return ret;
}

P* read(LL &v, P *parent) {
  char c = s[idx++];

  if(c == '[') {
    P *ret = new P;
    ret->parent = parent;
    ret->a = read(ret->va, ret);
    c = s[idx++];
    if(c != ',') {
      cerr << "Expected comma, found: " << c;
      die();
    }
    ret->b = read(ret->vb, ret);
    c = s[idx++];
    if(c != ']') {
      cerr << "Expected ], found: " << c;
      die();
    }
    return ret;
  }
  else {
    // Read value and return null!
    v = c-'0';
    while((c = s[idx++]) != ',' && c != ']') {
      v = 10*v + (c-'0');
    }
    idx--; // Don't walk over last token.    
    return NULL;
  }
}

vector<string> v;
P* readP() {
  if(!(cin >> s))
    return NULL;
  v.push_back(s);
  idx = 0;
  LL ignore;
  return read(ignore, NULL);
}

int main() {
    
  P *a = NULL, *b;
  while((b = readP()) != NULL) {
    cout << "Read ";
    print(b);
    cout << endl;
    
    if(a == NULL)
      a = b;
    else {
      a = add(a, b);
    }

    cout << endl << "Sum now: "; print(a); cout << endl << endl;
  }
  cout << "Answer 1: " << magnitude(a) << endl;

  // Part 2:
  LL answer2 = -1;
  for(int i = 0; i < (int)v.size(); i++) {
    for(int j = 0; j < (int)v.size(); j++) {
      if(i == j)
	continue;
      LL ignore;
      s = v[i];
      idx = 0;
      a = read(ignore, NULL);
    
      s = v[j];
      idx = 0;
      b = read(ignore, NULL);

      a = add(a,b);
      answer2 = max(answer2, magnitude(a));
      // Compare i and j:
    }
  }
  cout << "Answer 2: " << answer2 << endl;
}
