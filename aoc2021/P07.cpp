vector<int> v;

int getCost(int destination) {
  int ret = 0;
  FORIT(vector<int>, v) {
    ret += abs(*it-destination);
  }
  return ret;
}

LL getCost2(int destination) {
  LL ret = 0;
  FORIT(vector<int>, v) {
    LL dist = abs(*it-destination);
    ret += (dist+1)*dist/2;
  }
  return ret;
}

int main() {
  int x;
  while(cin >> x) {
    v.push_back(x);
  }
  sort(v.begin(), v.end());
  
  int bestCost = getCost(v[0]); // Cost is now the price of all to the right + 0 for the left-most
  cout << "Initial cost at " << v[0] << ": " << bestCost << endl;
  int cost = bestCost;
  int below = 0, above = (int)v.size()-1;
  for(int i = 1; i < (int)v.size(); i++) {
    int dist = v[i]-v[i-1];
    below++;
    cost -= dist*above;
    above--;
    cost += dist*below;
    bestCost = min(bestCost, cost);
    /*if(cost != getCost(v[i])) {
      cerr << "Error! Cost should be " << getCost(v[i]) << endl;
      return 1;
    }//*/
    cout << "Cost at " << i << " / " << v[i] << ": " << cost << endl;
  }
  cout << "Answer 1: " << bestCost << endl;

  LL bestCost2 = 99999999;  
  for(int i = v[0]; i <= v[v.size()-1]; i++) {
    LL cost2 = getCost2(i);
    bestCost2 = min(bestCost2, cost2);    
  }
  cout << "Answer 2: " << bestCost2 << endl;
}
