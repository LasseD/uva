// Clean up input by replacing - with space

// Merge a and b into c
void merge(const vector<PLL> &a, const vector<PLL> &b, vector<PLL> &c) {
  vector<PLL>::const_iterator ita = a.begin(), itb = b.begin();
  LL last = -1;
  while(!(ita == a.end() && itb == b.end())) {
    if(ita == a.end()) {
      PLL p(max(last+1,itb->first),itb->second);
      if(p.first <= p.second) {
	c.push_back(p);
	last = p.second;
      }
      itb++;
    }
    else if(itb == b.end()) {
      PLL p(max(last+1,ita->first),ita->second);
      if(p.first <= p.second) {
	c.push_back(p);
	last = p.second;
      }
      ita++;
    }
    else if(ita->second < itb->first) {
      PLL p(max(last+1,ita->first),ita->second);
      if(p.first <= p.second) {
	c.push_back(p);
	last = p.second;
      }
      ita++;
    }
    else if(itb->second < ita->first) {
      PLL p(max(last+1,itb->first),itb->second);
      if(p.first <= p.second) {
	c.push_back(p);
	last = p.second;
      }
      itb++;
    }
    else { // Merge
      LL low = min(ita->first, itb->first);
      LL high = max(ita->second, itb->second);
      low = max(low, last+1);
      if(low <= high) {
	c.push_back(PLL(low,high));
	last = high;
      }
      ita++;
      itb++;
    }
  }  
}

void clean(vector<PLL> &a, vector<PLL> &b) {
  LL last = -1;
  FORIT(vector<PLL>, a) {
    if(last == -1) {
      b.push_back(*it);
      last = it->second;
    }
    else if(last == it->first-1) {
      last = b[b.size()-1].second = it->second;
    }
    else if(last < it->first-1) {
      b.push_back(*it);
      last = it->second;      
    }
  }
}

int main() {
  vector<PLL> b0, b1, b2;

  LL low, high;
  while(cin >> low >> high) {
    b0.push_back(PLL(low,high));
    merge(b0, b1, b2);
    b0.clear();
    b1.clear();
    clean(b2,b1);
    b2.clear();    
  } // while read
  
  cout << "Answer 1: " << (b1[0].second+1) << endl;
  LL answer2 = 0;
  for(int i = 0; i+1 < (int)b1.size(); i++) {
    answer2 += (b1[i+1].first - b1[i].second) -1;
  }
  answer2 += 4294967295L - b1[b1.size()-1].second;
  cout << "Answer 2: " << answer2 << endl;
}
