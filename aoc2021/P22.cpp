// Clean up input by removing all non-numbers and "on" "off"
struct T {
  LL x1, x2, y1, y2, z1, z2;

  T(LL _x1, LL _x2, LL _y1, LL _y2, LL _z1, LL _z2) {
    x1 = _x1; x2 = _x2;
    y1 = _y1; y2 = _y2;
    z1 = _z1; z2 = _z2;
  }

  T(const T &t) {
    x1=t.x1; x2=t.x2;
    y1=t.y1; y2=t.y2;
    z1=t.z1; z2=t.z2;
  }

  bool intersects(const T &t) const {
    if(x2 < t.x1 || y2 < t.y1 || z2 < t.z1)
      return false;
    if(t.x2 < x1 || t.y2 < y1 || t.z2 < z1)
      return false;
    return true;
  }

  T intersection(const T &t) const {
    T ret(max(x1,t.x1), min(x2,t.x2),
	  max(y1,t.y1), min(y2,t.y2),
	  max(z1,t.z1), min(z2,t.z2));
    return ret;
  }

  LL size() const {
    return (x2-x1+1)*(y2-y1+1)*(z2-z1+1);
  }
};

ostream& operator<<(ostream& os, const T& t)
{
  os << '[' << t.x1 << ';' << t.x2 << ", " << t.y1 << ';' << t.y2 <<", " << t.z1 << ';' << t.z2 << ']';
  return os;
}

vector<T> add, sub;

LL computeSize() {
  LL ret = 0;
  FORIT(vector<T>, add) {
    ret+=it->size();
  }
  FORIT(vector<T>, sub) {
    ret-=it->size();
  }
  return ret;
}

void off(const T &t) {
  // For all in add, include the intersection in sub!
  vector<T> toSub;
  FORIT(vector<T>, add) {
    T x = *it;
    if(x.intersects(t)) {
      toSub.push_back(x.intersection(t));
    }
  }
  // For all in sub, include the intersection in add!
  FORIT(vector<T>, sub) {
    T x = *it;
    if(x.intersects(t)) {
      add.push_back(x.intersection(t));
    }
  }
  FORIT(vector<T>, toSub) {
    sub.push_back(*it);
  }
}

void on(const T &t) {
  off(t);
  add.push_back(t);
}

void printState() {
  cout << "ADD" << endl;
  FORIT(vector<T>, add) {
    cout << *it << endl;
  }
  cout << "REM" << endl;
  FORIT(vector<T>, sub) {
    cout << *it << endl;
  }
  cout << "SIZE " << computeSize() << endl;
}

int main() {
  LL x1, x2, y1, y2, z1, z2; string op;
  cout << "Initial size: " << computeSize() << endl;
  while(cin >> op >> x1 >> x2 >> y1 >> y2 >> z1 >> z2) {
    if(op == "on") {
      T t(x1, x2, y1, y2, z1, z2);
      on(t);
      //cout << "Turned on " << t << "." << endl;
      //printState();
    }
    else { // off
      T t(x1, x2, y1, y2, z1, z2);
      off(t);
      //cout << "Turned off " << t << "." << endl;
      //printState();
    }
  }

  LL answer = computeSize();
  cout << "Answer 2: " << answer << endl;
  T answer1Box(-50,50,-50,50,-50,50);
  off(answer1Box);
  LL smallerAnswer = computeSize();
  
  cout << "Answer 1: " << (answer-smallerAnswer) << endl;
}
