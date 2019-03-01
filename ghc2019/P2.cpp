struct Image {
  vector<int> tags;
  int i1, i2; // -1 for no i2
};

int cmpSize(Image &a, Image &b) {
  return a.tags.size() > b.tags.size();
}

int overlap(Image &a, Image &b) {
  int ret = 0;

  unsigned int idxA = 0, idxB = 0;
  while(idxA < a.tags.size() && idxB < b.tags.size()) {
    int ta = a.tags[idxA], tb = b.tags[idxB];
    if(ta < tb) {
      idxA++;
    }
    else if(ta > tb) {
      idxB++;
    }
    else {
      ret++;
      idxA++;
      idxB++;
    }
  }
  return ret;
}

int score(Image &a, Image &b) {
  int A = 0, B = 0, C = 0;

  unsigned int idxA = 0, idxB = 0;
  while(idxA < a.tags.size() && idxB < b.tags.size()) {
    int ta = a.tags[idxA], tb = b.tags[idxB];
    if(ta < tb) {
      A++;
      idxA++;
    }
    else if(ta > tb) {
      B++;
      idxB++;
    }
    else {
      C++;
      idxA++;
      idxB++;
    }
  }
  while(idxA < a.tags.size()) {
    A++;
    idxA++;
  }
  while(idxB < b.tags.size()) {
    B++;
    idxB++;
  }
  //cerr << "ABC=" << A << " " << B << " " << C << endl;

  if(A < B) {
    return A < C ? A : C;
  }
  else {
    return B < C ? B : C;
  }
}

void output(Image &a) {
  cout << a.i1;
  if(a.i2 >= 0) {
    cout << " " << a.i2;
  }
  cout << endl;
}

int myrandom (int i) { return rand()%i;}

int main() {
  // Read images:
  GI(N);

  srand ( unsigned ( time(0) ) );

  vector<Image> vertical, horizontal;
  map<string,int> words;

  FORI(N) {
    if(i % 1000 == 0)
      cerr << ",";
    GS(type);

    Image image; image.i1 = i; image.i2 = -1;

    GI(M);
    FORJ(M) {
      GS(tag);
      if(words.find(tag) == words.end()) {
        words[tag] = (int)words.size()+1;
      }
      image.tags.push_back(words[tag]);
    }
    sort(image.tags.begin(), image.tags.end());

    if(type[0] == 'V') {
      vertical.push_back(image);
    }
    else {
      horizontal.push_back(image);
    }
  }
  cerr << "Data read" << endl;

  cout << (horizontal.size() + (vertical.size()/2)) << endl;

  // Pair the verticals:
  //sort(vertical.begin(), vertical.end(), cmpSize);
  random_shuffle(vertical.begin(), vertical.end(), myrandom);

  // Improve vertical shuffling:
  

  cerr << "Verticals sorted" << endl;

  int W = 1000;
  for(int i = 0; i < (int)vertical.size(); i+=2) {
    if(i % 1000 == 0)
      cerr << ";";
    Image &a = vertical[i];

    // Find best neighbour:
    int bestScore = 1000;
    int bestJ = -1;
    for(int j = i+1; j <= W+i && j < (int)vertical.size(); j++) {
      Image &b = vertical[j];
      int v = overlap(a, b);
      if(v < bestScore) {
        bestScore = v;
        bestJ = j;
      }
    }
    swap(vertical[i+1], vertical[bestJ]);

    Image &b = vertical[i+1];
    Image mix;
    mix.i1 = a.i1;
    mix.i2 = b.i1;
    // Merge tags:
    unsigned int idxA = 0, idxB = 0;
    while(idxA < a.tags.size() && idxB < b.tags.size()) {
      int ta = a.tags[idxA], tb = b.tags[idxB];
      if(ta < tb) {
        mix.tags.push_back(ta);
        idxA++;
      }
      else if(ta > tb) {
        mix.tags.push_back(tb);
        idxB++;
      }
      else {
        mix.tags.push_back(ta);
        idxA++;
        idxB++;
      }
    }
    while(idxA < a.tags.size()) {
      int t = a.tags[idxA++];
      mix.tags.push_back(t);
    }
    while(idxB < b.tags.size()) {
      int t = b.tags[idxB++];
      mix.tags.push_back(t);
    }
    horizontal.push_back(mix);
  }
  
  
  cerr << "MIXING" << endl;
  random_shuffle(horizontal.begin(), horizontal.end(), myrandom);
  cerr << "MIXING DONE" << endl;

  /*
  cout << "DEBUG" << endl;
  for(int i = 0; i < (int)horizontal.size(); i++) {
    Image &a = horizontal[i];
    output(a);
  }
  cout << "DEBUG END" << endl;*/

  int w = 20000;
  int total = 0;
  for(int i = 0; i < (int)horizontal.size(); i++) {
    if(i % 1000 == 0)
      cerr << ".";
    Image &a = horizontal[i];
    output(a); // Improve ahead:
    if(i+2 >= (int)horizontal.size()) {
      continue; // Don't improve if nothingg ahead.
    }
    int bestScore = -1;
    int bestJ = -1;
    for(int j = i+1; j <= w+i && j < (int)horizontal.size(); j++) {
      Image &b = horizontal[j];
      int v = score(a, b);
      if(v > bestScore) {
        bestScore = v;
        bestJ = j;
      }
    }
    total += bestScore;
    swap(horizontal[i+1], horizontal[bestJ]);
  }
  cerr << "TOTAL: " << total << endl;
}
