#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

int main() {
  string line, ingredient, recipe;
  getline(cin, line);
  int numberOfBinders = atoi(line.c_str());
  for(int cas = 0; cas < numberOfBinders; ++cas) {
    getline(cin, line);
    transform(line.begin(), line.end(), line.begin(), ::toupper);
    cout << line << endl;
    getline(cin, line);
    stringstream ss1;
    ss1 << line;
    int m, n, b, price, amount; // ingredients, recipes, budget
    ss1 >> m >> n >> b;
    map<string,int> prices;
    for(int i = 0; i < m; ++i) {
      getline(cin, line);
      stringstream ss2;
      ss2 << line;
      ss2 >> ingredient >> price;
      prices[ingredient] = price;
    }

    pair<int,string> *ret = new pair<int,string>[n];

    for(int i = 0; i < n; ++i) {
      getline(cin, recipe);
      ret[i] = pair<int,string>(0, recipe);
      getline(cin, line);
      int numberOfIngredients = atoi(line.c_str());
      for(int j = 0; j < numberOfIngredients; ++j) {
	getline(cin, line);
	stringstream ss2;
	ss2 << line;
	ss2 >> ingredient >> amount;
	ret[i].first += amount * prices[ingredient];
      }
    }

    sort(ret, ret+n);
    bool any = false;
    for(int i = 0; i < n; ++i) {
      if(ret[i].first > b)
	break;
      any = true;
      cout << ret[i].second << endl;
    }
    if(!any)
      cout << "Too expensive!" << endl;
    cout << endl;
    delete[] ret;
  } // cases
} // main
