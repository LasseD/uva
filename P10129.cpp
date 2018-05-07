// This is a simple question of checking if a graph has an Euler path.
// We can check if a graph has an euler path by connecting the start and end edge and instead ask if it has an Euler cycle.
// A graph has an euler cycle if all nodes have inDegree=outDegree and are strongly connected.

int inDegree[26], outDegree[26];
bool connects[26][26]; // [a][b] iff a->b
bool connectsReverse[26][26]; // [a][b] iff b->a

// Mark the reachable nodes.
void dfsMark(int x, bool *reachable, bool g[][26]) {
  FORI(26) {
    if(i == x)
      continue;
    if(reachable[i])
      continue; // Already visited.
    if(!g[x][i])
      continue; // No edge.
    reachable[i] = true;
    dfsMark(i, reachable, g);
  }
}

// Use "Kosaraju using DFS":
bool isStronglyConnected() {
  bool reachable[26];
  bool reachableReverse[26];
  FORI(26)
    reachableReverse[i] = reachable[i] = false;
  // Find starting node:
  int start = -1;
  FORI(26) {
    if(inDegree[i] != 0) {
      start = i;
      break;
    }    
  }
  if(start == -1) {
    //cerr << "EMPTY GRAPH" << endl;
    return true; // Empty graph.
  }

  /*
  //cerr << "CONNECTS:" << endl;
  FORI(26) {
    if(inDegree[i] == 0)
      continue;
    //cerr << ((char)('a'+i)) << " ->";
    FORJ(26) {
      if(connects[i][j])
	//cerr << " " << ((char)(j+'a'));
    }
    //cerr << endl;
  }
  //cerr << "REVERSE:" << endl;
  FORI(26) {
    if(inDegree[i] == 0)
      continue;
    //cerr << ((char)('a'+i)) << " ->";
    FORJ(26) {
      if(connectsReverse[i][j])
	//cerr << " " << ((char)(j+'a'));
    }
    //cerr << endl;
  }
  //*/

  reachable[start] = reachableReverse[start] = true;
  dfsMark(start, reachable, connects);
  dfsMark(start, reachableReverse, connectsReverse);
  FORI(26) {
    if(inDegree[i] == 0)
      continue;
    if(!reachable[i]) {
      //cerr << (char)(i+'a') << " not reachable from " << ((char)(start+'a')) << endl;
      return false;
    }
    if(!reachableReverse[i]) {
      //cerr << (char)(i+'a') << " not REVERSE reachable from " << ((char)(start+'a')) << endl;
      return false;
    }
  }
  return true;
}

bool hasEulerPath() {
  int start = -1;
  int end = -1;
  // Find start and end:
  FORI(26) {
    if(inDegree[i] == outDegree[i]) {
      // OK!
    }
    else if(inDegree[i] == outDegree[i]+1) {
      if(end != -1) {
	//cerr << "Two end nodes! " << ((char)(end+'a')) << " and " << ((char)(i+'a')) << endl;	
	return false; // More than one end.
      }
      end = i;
    }
    else if(inDegree[i] == outDegree[i]-1) {
      if(start != -1) {
	//cerr << "Two start nodes! " << ((char)(start+'a')) << " and " << ((char)(i+'a')) << endl;	
	return false; // More than one start.
      }
      start = i;
    }
    else {
      //cerr << "More than one in difference for " << ((char)(i+'a')) << ": in degree " << inDegree[i] << ", out degree: " << outDegree[i] << endl;	
      return false; // More than one in difference!
    }
  }

  if(start == -1 && end == -1) {
    // Any start and end will do!
  }
  else if(start == -1 || end == -1) {
    //cerr << "This should not happen!" << endl;
    return false; // Bad state!
  }
  else {
    // There is a distinct start and end... so we just connect end->start and ask if there is an euler cycle instead :)
    ++outDegree[end];
    ++inDegree[start];
    connects[end][start] = true;
    connectsReverse[start][end] = true;
  }
  return isStronglyConnected();
}

int main() {
  FORCAS {
    // Reset data structures:
    FORI(26) {
      inDegree[i] = outDegree[i] = 0;
      FORJ(26) {
	connects[i][j] = false;
	connectsReverse[i][j] = false;
      }
    }
    // Read data:
    GI(N);
    FORI(N) {
      GS(s);
      int from = s[0]-'a';
      int to = s[s.size()-1]-'a';
      ++outDegree[from];
      ++inDegree[to];
      connects[from][to] = true;
      connectsReverse[to][from] = true;
    }
    // Compute:
    if(hasEulerPath())
      cout << "Ordering is possible." << endl;
    else
      cout << "The door cannot be opened." << endl;
  }
  return 0;
}
