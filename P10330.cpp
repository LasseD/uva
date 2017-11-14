#include <queue>

#define INF numeric_limits<LL>::max()
//9223372036854775807LL

// Run Edmonds–Karp algorithm to ensure quick termination O(VE^2) instead of flow-dependent Ford-Fulkerson.

struct Edge {
  int s, t;
  LL cap, flow;
  Edge *rev;
};

Edge edges[50000];
vector<Edge*> out[203]; // out edges for each node.
int N, M; // nodes, edges
Edge* pred[203];

// Taken from https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm
LL EdmondsKarp() {
  int s = 0;
  int t = 2*N+1;
  LL flow = 0;

  while(true) {
    FORI(2*N+2)
      pred[i] = NULL;

    queue<int> q; // Has push(), pop() and front().
    q.push(s);

    while(!q.empty()) {
      int cur = q.front();
      q.pop();
      FORIT(vector<Edge*>, out[cur]) {
	Edge *e = *it;
	if(pred[e->t] == NULL && e->t != s && e->cap > e->flow) {
	  pred[e->t] = e;
	  q.push(e->t);
	}
      }
    }

    if(pred[t] == NULL) {
      break; // no augmenting path.
    }

    LL df = INF;
    for(Edge *e = pred[t]; e != NULL; e = pred[e->s]) {
      df = MIN(df, e->cap - e->flow);
    }

    for(Edge *e = pred[t]; e != NULL; e = pred[e->s]) {
      e->flow += df;
      e->rev->flow -= df;
    }
    flow += df;
    //cerr << "Flow improvement: " << df << endl;
  }
  return flow;
}

int main() {
  while(cin >> N) {
    // Nodes:
    // 0 = source, 2*N intermediate, 2N+1 = destination.
    // For each node i: 2*i+1 and 2*i+2 are node source and dest.
    
    // Reset graph:
    M = 0; // No edges initially.    
    FORI(2*N+2) {
      out[i].clear();
    }

    // Read capacities of the intermediate nodes:
    FORI(N) {
      GI(cap);
      Edge *e = &edges[M++];
      Edge *f = &edges[M++]; // Reverse edge.
      e->s = f->t = 2*i+1;
      e->t = f->s = 2*i+2;
      e->cap = cap;
      f->cap = 0;
      e->flow = f->flow = 0;
      e->rev = f, f->rev = e;
      out[e->s].push_back(e);
      out[f->s].push_back(f);
    }

    // Read edges:
    GI(m); // little m = number of links.
    FORI(m) {
      Edge *e = &edges[M++];
      Edge *f = &edges[M++]; // Reverse edge->
      cin >> e->s >> e->t >> e->cap;
      e->s = (e->s-1)*2+2;
      e->t = (e->t-1)*2+1;
      e->flow = 0;
      f->s = e->t; f->t = e->s; f->cap = 0; f->flow = 0;
      e->rev = f, f->rev = e;
      out[e->s].push_back(e);
      out[f->s].push_back(f);
    }

    // Read additional edges from source and dest:
    GI(B); GI(D);
    FORI(B) {
      GI(I);--I;
      Edge *e = &edges[M++];
      Edge *f = &edges[M++]; // Reverse edge.
      e->s = f->t = 0;
      e->t = f->s = 2*I+1;
      e->cap = INF;
      f->cap = 0;
      e->flow = f->flow = 0;
      e->rev = f, f->rev = e;
      out[0].push_back(e);
      out[f->s].push_back(f);
    }
    FORI(D) {
      GI(I);--I;
      Edge *e = &edges[M++];
      Edge *f = &edges[M++]; // Reverse edge->
      e->s = f->t = 2*I+2;
      e->t = f->s = 2*N+1;
      e->cap = INF;
      f->cap = 0;
      e->flow = f->flow = 0;
      e->rev = f, f->rev = e;
      out[e->s].push_back(e);
      out[e->t].push_back(f);
    }

    /*
    cerr << "N=" << N << ", number of nodes: " << 2*N+2 << endl;
    FORI(2*N+2) {
      cerr << " " << i << ":";
      FORIT(vector<Edge*>, out[i])
	cerr << " " << (*it)->t << "," << (*it)->cap;
      cerr << endl;
    }//*/

    cout << EdmondsKarp() << endl;
  }
  return 0;
}
