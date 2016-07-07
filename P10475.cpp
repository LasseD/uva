#include <iostream>
#include <stdio.h>
#include <set>
#include <vector>
#include <algorithm>

typedef std::string String;
typedef std::pair<int,String> Topic;
typedef std::pair<Topic,Topic> Pair;
typedef std::set<Pair> Set;
typedef std::vector<int> Vector;

Topic getTopic() {
  std::string s;
  std::cin >> s;
  std::transform(s.begin(),s.end(),s.begin(),::toupper);
  return Topic((int)(-s.size()), s);
}

void outputTopics(const int i, const int permutationSize, int * const permutation, 
		  const Vector &remainingIndices, Topic * const topics,
		  const Set &forbiddenPairs) {
  if(i == permutationSize) {
    std::cout << topics[permutation[0]].second;
    for(int j = 1; j < permutationSize; ++j) {
      std::cout << " " << topics[permutation[j]].second;
    }
    std::cout << std::endl;
    return;
  }
  for(unsigned int j = 0; j < remainingIndices.size(); ++j) {
    int remainingIndex1 = remainingIndices[j];
    Vector remainingIndices2;
    for(unsigned int k = j+1; k < remainingIndices.size(); ++k) {
      int remainingIndex2 = remainingIndices[k];
      if(forbiddenPairs.find(Pair(topics[remainingIndex1],topics[remainingIndex2])) == forbiddenPairs.end())
	remainingIndices2.push_back(remainingIndex2);
    }
    permutation[i] = remainingIndex1;
    outputTopics(i+1, permutationSize, permutation, remainingIndices2, topics, forbiddenPairs);
  }
}


int main() {
  int n, t, p, s;
  std::cin >> n;
  for(int cas = 1; cas <= n; ++cas) {
    std::cin >> t >> p >> s; // t=|topics|, p=|prohibited pairs|, s=topic pr. speech.
    Topic *topics = new Topic[t];
    Set forbiddenPairs;

    for(int i = 0; i < t; ++i)
      topics[i] = getTopic();
    std::sort(topics, topics+t);

    for(int i = 0; i < p; ++i) {
      Topic t1 = getTopic();
      Topic t2 = getTopic();
      if(forbiddenPairs.find(Pair(t1,t2)) == forbiddenPairs.end())
	forbiddenPairs.insert(Pair(t1,t2));
      if(forbiddenPairs.find(Pair(t2,t1)) == forbiddenPairs.end())
	forbiddenPairs.insert(Pair(t2,t1));
    }
    int *permutation = new int[s];
    Vector remainingIndices;
    for(int i = 0; i < t; ++i)
      remainingIndices.push_back(i);
    std::cout << "Set " << cas << ":" << std::endl;
    outputTopics(0, s, permutation, remainingIndices, topics, forbiddenPairs);
    std::cout << std::endl;

    delete[] topics;
  }
  return 0;
}
