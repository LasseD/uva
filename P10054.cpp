struct Node {
  Node *prev, *next;
  PI ele;
}; 

std::ostream& operator<<(std::ostream& os, const Node& n) {
  os << n.ele.first << " " << n.ele.second;
  return os;
}

int main() {
  int m, a, b;

  Node* lastToColor[51];
  set<Node*> adjacent[51];
  Node list[1010];

  FORCAS {
    if(cas != 0)
      cout << endl;
    cout << "Case #" << (cas+1) << endl;

    // Reset data:
    FORI(51) {
      adjacent[i].clear();
      lastToColor[i] = NULL;
    }

    // Read data:
    cin >> m;
    FORI(m) {
      cin >> a >> b; 
      list[i].ele = PI(a,b);
      if(i == 0)
        continue;
      adjacent[a].insert(&list[i]);
      if(a != b)
	adjacent[b].insert(&list[i]);
    }

    Node *first = &list[0];
    lastToColor[first->ele.second] = first;
    // Always maintain a closed necklace:
    first->next = first;
    first->prev = first;

    // Try to reconstruct necklace:
    bool ok = true;
    Node *last = first;
    int retSize = 1;
    while(retSize < m && ok) {
      int lastColor = last->ele.second;
      if(adjacent[lastColor].empty()) {
	// Find one that can be stitched in:
	bool foundAny = false;
	FORI(51) {
	  if(adjacent[i].empty() || lastToColor[i] == NULL)
	    continue;
	  first = lastToColor[i]->next;
	  last = lastToColor[i];
	  //cerr << "New first: " << *first << ", last: " << *last << endl;
	  lastColor = i;
	  foundAny = true;
	  break;
	}
	if(!foundAny) {
	  ok = false;
	  break;
	}
      }
      Node* node = retSize%2 == 1 ?
	*adjacent[lastColor].begin() : 
	*adjacent[lastColor].rbegin();
      adjacent[lastColor].erase(node);
      //cerr << "-> " << *node << endl;
      int nextColor = node->ele.first == last->ele.second ? node->ele.second : node->ele.first;
      if(lastColor != nextColor)
	adjacent[nextColor].erase(node);
      if(node->ele.second != nextColor)
	swap(node->ele.first, node->ele.second); // Redirect node.
      // Stitch in node:
      ++retSize;
      last->next = node;
      node->prev = last;
      node->next = first;
      first->prev = node;
      last = node;
      // Update aux. structures:
      lastToColor[nextColor] = node;
    }

    if(last->ele.second != first->ele.first) {
      ok = false;
    }

    if(ok) {
      Node *cur = first;
      do {
	cout << *cur << endl;
	cur = cur->next;
      } while(cur != first);
    }
    else {
      cout << "some beads may be lost" << endl;
    }
  } // FORCAS
  return 0;
} 
