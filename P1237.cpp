typedef pair<string,PI> Car;
#define LL second.first
#define HH second.second
#define NAME first

int main() {
  FORCAS {
    if(cas > 0)
      cout << endl;
    // Read data:
    int D, q, x;
    cin >> D;
    Car *cars = new Car[D];
    FORI(D)
      cin >> cars[i].NAME >> cars[i].LL >> cars[i].HH;
    
    // Make search tree on results!
    map<PI,int> Q; // (price, queryIndex) -> Car index (-1 for unknown)
    vector<int> QQ; // To remember prices.
    cin >> q;
    FORI(q) {
      cin >> x;
      Q[PI(x,i)] = -1;
      QQ.push_back(x);
    }
    // Mark cars in Q:
    FORI(D) {
      Car &car = cars[i];
      vector<PI> toRemove;
      map<PI,int>::iterator it = Q.lower_bound(PI(car.LL,-1)); // Now points to first query with this or larger price.
      while(it != Q.end() && it->first.first <= car.HH) {
	if(it->second == -1)
	  it->second = i;
	else
	  toRemove.push_back(it->first);
	++it;
      }
      FORIT(vector<PI>, toRemove) {
	Q.erase(*it);
      }
      /*
      cerr << "After " << car.NAME << ": " << car.LL << "->" << car.HH << endl;
      for(it = Q.begin(); it != Q.end(); ++it)
	cout << " " << it->first.first << "," << it->first.second << "->" << it->second << endl;/*/
    }
    FORI(q) {
      if(Q.find(PI(QQ[i],i)) == Q.end() || Q[PI(QQ[i],i)] == -1)
	cout << "UNDETERMINED" << endl;
      else
	cout << cars[Q[PI(QQ[i],i)]].NAME << endl;
    }
    delete[] cars;    
  }
  return 0;
}
