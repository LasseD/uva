int btod(string s) {
  int ret = 0;
  FORUI(s.size()) {
    ret <<= 1;
    if(s[i] == '1')
      ret+=1;
  }
  return ret;
}

int main() {
  ULL gamma = 0, epsilon = 0;
  int cnt0[100], cnt1[100];
  FORI(100)
    cnt0[i] = cnt1[i] = 0;
  vector<string> o2, co2;
  string s;
  int size;
  while(cin >> s) {
    size = (int)s.size();
    o2.push_back(s);
    co2.push_back(s);
    FORI(size) {
      if(s[i] == '0')
	cnt0[i]++;
      else
	cnt1[i]++;
    }
  }
  FORI(size) {
    gamma<<=1;
    epsilon<<=1;
    if(cnt0[i] > cnt1[i]) {
      epsilon++;
    }
    else {
      gamma++;
    }   
  }
  cout << "epsilon: " << epsilon << ", gamma: " << gamma << ", answer 1: " << (gamma*epsilon) << endl;
  // Part 2:
  int numCO2, numO2;
  
  FORI(size) {
    vector<string> o, c;

    int c0 = 0, c1 = 0;
    FORIT(vector<string>, o2) {
      if((*it)[i] == '1')
	c1++;
      else
	c0++;
    }
    
    FORIT(vector<string>, o2) {
      char keep = c1 >= c0 ? '1' : '0';
      if((*it)[i] == keep)
	o.push_back(*it);
    }
    o2 = o;
    cout << "After " << i << ": " << o2.size() << " o2 left:" << endl;
    FORIT(vector<string>, o2) {
      cout << " " << *it << ": " << btod(*it) << endl;
    }
    if(o2.size() == 1) {
      numO2 = btod(o2[0]);
      cout << "Count O2 set: " << numO2 << endl;
    }


    c0 = 0, c1 = 0;
    FORIT(vector<string>, co2) {
      if((*it)[i] == '1')
	c1++;
      else
	c0++;
    }
    
    FORIT(vector<string>, co2) {
      char keep = c0 <= c1 ? '0' : '1';
      if((*it)[i] == keep)
	c.push_back(*it);
    }
    co2 = c;
    /*cout << "After " << i << ": " << co2.size() << " co2 left" << endl;
    FORIT(vector<string>, co2) {
      cout << " " << *it << ": " << btod(*it) << endl;
      }*/
    if(co2.size() == 1) {
      numCO2 = btod(co2[0]);
      //cout << "Count CO2 set: " << numCO2 << endl;
    }
  }
  cout << "Answer 2: " << (numO2*numCO2) << endl;
}
