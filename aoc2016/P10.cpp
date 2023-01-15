struct Bot {
  int id, low, high, vals[2],numVals;
};

/*
  Clean input, rm "gives low to " and "and high to ", "goes to bot "
 */
int main() {
  map<int,Bot*> bots;
  vector<PI> input; // value x goes to bot y

  string op;
  while(cin >> op) {
    if(op == "bot") {
      Bot *bot = new Bot;
      bot->numVals = 0;
      
      cin >> bot->id;
      GS(t1);
      GI(a); // low
      if(t1 == "output")
	a = -a-1;
      bot->low = a;
      GS(t2);
      GI(b); // high
      if(t2 == "output")
	b = -b-1;
      bot->high = b;
      
      bots[bot->id] = bot;
    }
    else if(op == "value") {
      GI(a); GI(b);
      input.push_back(PI(a,b));
    }
    else {
      die(); // unknown command!
    }
  }

  stack<int> ready;
  map<int,int> output;
  
  // Initial values:
  FORIT(vector<PI>, input) {
    int value = (*it).first;
    int botId = (*it).second;
    Bot *bot = bots[botId];
    bot->vals[bot->numVals++] = value;
    if(bot->numVals == 2) {
      ready.push(botId);
    }
  }

  while(!ready.empty()) {
    Bot *bot = bots[ready.top()];
    ready.pop();
    sort(bot->vals, bot->vals+2);

    cout << "Bot " << bot->id << " which gives low (" << bot->vals[0] << ") to " << bot->low << " and high (" << bot->vals[1] << ") to " << bot->high << endl;
    if(bot->vals[0] == 17 && bot->vals[1] == 61) {
      cout << "HANDLES!" << endl;
    }

    // Handle low:
    if(bot->low < 0) {
      int o = -bot->low-1;
      output[o] = bot->vals[0];
      cout << "Output " << o << ": " << bot->vals[0] << endl;
    }
    else {
      Bot *b2 = bots[bot->low];
      b2->vals[b2->numVals++] = bot->vals[0];
      if(b2->numVals == 2) {
	ready.push(b2->id);
      }
    }
    // Handle high:
    if(bot->high < 0) {
      int o = -bot->high-1;
      output[o] = bot->vals[1];
      cout << "Output " << o << ": " << bot->vals[1] << endl;
    }
    else {
      Bot *b2 = bots[bot->high];
      b2->vals[b2->numVals++] = bot->vals[1];
      if(b2->numVals == 2) {
	ready.push(b2->id);
      }
    }
  }
  cout << "Answer 2: " << (output[0]*output[1]*output[2]) << endl;
}
