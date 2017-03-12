/*
V Videos: Size
C Cache servers: 
E Endpoints: Connect to 0.. cache servers + latencies
R Requests: video x endpoint = number
X: Capacity of cache servers.
Score: Average improvement.
 */

int main() {
  char line[10000];
  gets(line);
  string s(line);
  stringstream ss; ss << s;

  int V, E, R, C, X, dcLatency[1000]; 
  ss >> V>> E>> R>> C>> X;
 
  gets(line);
  string s2(line);
  stringstream ss2; ss2 << s2;
  int *videoSizes = new int[V];
  FORI(V) {
    ss2 >> videoSizes[i];
  }

  int *latencies = new int[E*C]; // endpointIndex * C + cacheServerIndex

  FORI(E) { // Endpoint i
    gets(line);
    string s3(line);
    stringstream ss3; ss3 << s3;
    
    int numConnections;
    ss3 >> dcLatency[i] >> numConnections;
    FORJ(numConnections) {
      gets(line);
      string s4(line);
      stringstream ss4; ss4 << s4;

      int cacheI, latency;
      ss4 >> cacheI >> latency;
      latencies[i*C+cacheI] = latency;
    }
  }

  pair<PI,int> *requests = new pair<PI,int>[R]; // (numReq,video), endpoint
  FORI(R) { // Request i
    gets(line);
    string s4(line);
    stringstream ss4; ss4 << s4;

    int numRequests, videoI, endpointI;
    ss4 >> videoI>> endpointI >> numRequests;
    requests[i] = PI(numRequests;
  }
 
  // Initial filling of cache servers:
  vector<int> content[1000];
  int load[1000]; memset(load, 0, 1000*sizeof(int));
  FORI(C) { // Datacenter i
    int dcl = dcLatency[i];
    vector<PDI> v; // score, video
    FORJ(V) { // Video j
      double score = 0;
      FORK(E) { // Endpoint k
	score += requests[k*V+j]*MAX(0, dcl-latencies[k*C+i]);
      }
      v.push_back(PDI(score/log(videoSizes[j]), j));
    }
    sort(v.begin(), v.end());
    FORIT(vector<PDI>, v) {
      if(videoSizes[it->second]+load[i] <= X) {
	content[i].push_back(it->second);
	load[i] += videoSizes[it->second];
      }
    }
  }

  // TODO: Fancy rebalancing :)

  // Output:
  int ret = 0;
  FORI(C) {
    if(!content[i].empty())
      ++ret;
  }
  long sumAll = 0;
  long sum = 0;
  cout << ret << endl;
  FORI(C) {
    if(content[i].empty())
      continue;
    cout << i;
    FORIT(vector<int>, content[i]) {
      sumAll += videoSizes[*it];
      ++sum;
      cout << " " << *it;
    }
    cout << endl;
  }
  cerr << "Sum all: " << sumAll << " in " << sum << " chunks" << endl;

  return 0;
}

