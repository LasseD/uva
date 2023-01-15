// Replace Mg with g, Ca with a, Al with l, Si with S, Th with h, Ti with i, Ar with A, Rn with R.
// Remove lines starting with CR, as it is never used.
// 
// Always repace N with HS. TODO.
// Doublers: a -> aa, i -> ii DONE.

#include <random>

LL hashCode(string &s) {
  LL ret = 0;
  FORUI(s.size()) {
    ret = 41*ret + s[i];
  }
  return ret;
}

int iteration = 1;

vector<PS> V;
string start = "e";
int best = 999;
int cnt = 0;
map<LL,int> seen;
map<string,int> built;

void reduce(string s, int iterations) {
  if(s == start) {
    best = min(best, iterations);
    return;
  }
  if(iterations > best) {
    return; // Too deep.
  }

  // Try a and i replacement:
  string::size_type pos;
  while((pos = s.find("aaa")) != string::npos) {
    s = s.replace(pos, 3, "aa");
    iterations++;
  }
  while((pos = s.find("iii")) != string::npos) {
    s = s.replace(pos, 3, "ii");
    iterations++;
  }
  
  LL hash = hashCode(s);
  if(seen.find(hash) == seen.end()) {
    seen[hash] = iterations;
  }
  else {
    int old = seen[hash];
    if(old <= iterations) {
      return; // Already done better.
    }
    cout << "Improved path to " << s << " from " << seen[hash] << " to " << iterations << endl;
    seen[hash] = iterations;
  }

  if(cnt++ % 1000000 == 0)
    cout << cnt << " Best: " << best << ", now: " << iterations << " Trying " << s << " of size " << s.size() << endl;
  
  FORIT(vector<PS>, V) {
    string from = it->first;
    string to = it->second;
    //cout << "Trying replacement " << from << " -> " << to << endl;

    pos = -1;
    while((pos = s.find(to, pos+1)) != string::npos) {
      string s2 = s;
      s2 = s2.replace(pos, to.size(), from);
      reduce(s2, iterations+1);
      pos++;
    }
  }
}

bool cmp(const PS &a, const PS &b) {
  if(a.second.size() != b.second.size())
    return a.second.size() > b.second.size();

  if(a.second != b.second)
    return a.second < b.second;
  return a.first < b.first;
}

int main() {
  GI(N);  
  FORI(N) {
    GS(from);
    GS(arrow);
    GS(to);
    V.push_back(PS(from,to));
  }
  GS(target);
  cout << N << " lines" << endl;

  sort(V.begin(), V.end(), cmp);

  FORIT(vector<PS>, V) {
    string from = it->first;
    string to = it->second;
    cout << " " << from << " -> " << to << endl;
  }

  cout << "Target size: " << target.size() << endl;

  reduce(target, 0);

  cout << best << endl;
}
