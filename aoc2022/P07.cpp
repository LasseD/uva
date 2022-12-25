struct DIR {
  DIR *p;
  map<string,DIR*> c;
  map<string,long> files;
  long size;
  string name;
};

long answer1 = 0, answer2 = 0;

long wc(DIR *dir) {
  if(dir->size != -1) {
    return dir->size;
  }
  
  long sum = 0;

  for(map<string,long>::iterator it = dir->files.begin(); it != dir->files.end(); it++) {
    sum += it->second;
  }
  for(map<string,DIR*>::iterator it = dir->c.begin(); it != dir->c.end(); it++) {
    sum += wc(it->second);
  }
  
  dir->size = sum;
  if(sum < 100000) {
    answer1 += sum;
  }
  //cout << "SIZE " << dir->name << ": " << sum << endl;
  return sum;
}

long smallestOver(DIR *dir, long goal) {
  long best = -1;
  if(dir->size >= goal) {
    best = dir->size;
  }
  
  for(map<string,DIR*>::iterator it = dir->c.begin(); it != dir->c.end(); it++) {
    long x = smallestOver(it->second,goal);
    if(x > 0 && x < best) {
      best = x;
    }
  }
  return best;
}

int main() {
  DIR root, *cur;
  root.p = NULL;
  root.size = -1;
  cur = &root;

  string cmd;
  cin >> cmd; // &
  bool ok = true;
  while(ok && (cin >> cmd)) {
    if(cmd == "ls") {
      //cout << "> ls" << endl;
      while(true) {
	ok = (cin >> cmd);
	if(!ok || cmd == "$")
	  break;
	if(cmd == "dir") {
	  cin >> cmd; // dir name
	  if(cur->c.find(cmd) == cur->c.end()) {
	    DIR *d = new DIR();
	    d->p = cur;
	    d->size = -1;
	    d->name = cmd;
	    cur->c.insert(pair<string,DIR*>(cmd, d));
	  }
	  //cout << "DIR " << cmd << endl;
	}
	else { // File
	  long size = stol(cmd);
	  cin >> cmd; // File
	  if(cur->files.find(cmd) == cur->files.end()) {
	    cur->files.insert(pair<string,long>(cmd,size));
	  }
	  //cout << cmd << ": " << size << endl;
	}
      }
    }
    else if (cmd == "cd") { // 
      GS(where);
      //cout << " cd " << where << endl;
      if(where == "/") {
	cur = &root;
      }
      else if(where == "..") {
	cur = cur->p;
      }
      else { // cd dir
	if(cur->c.find(where) == cur->c.end()) {
	  cerr << "TODO" << endl;
	}
	else {
	  cur = (cur->c.find(where))->YY;
	}
      }
      cin >> cmd; // &
    }
    else {
      cerr << "Unknown command " << cmd << endl;
    }
  }

  wc(&root);

  cout << "Answer 1: " << answer1 << endl;
  long all = 70000000;
  long goal = 30000000;
  long rem = all - root.size;
  cout << "Answer 2: " << smallestOver(&root,goal-rem) << endl;
} // int main
