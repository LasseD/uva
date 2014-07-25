#include <iostream>
#include <stdio.h>
#include <vector>
#include <sstream>

struct Word {
  Word *next;
  std::string word;
};

struct Rule {
  std::vector<std::string> from;
  std::string to;

  Rule(std::string to, std::string a) : to(to) {
    std::istringstream ss(a);
    std::string sub;
    while(std::getline(ss, sub, ' ')) {
      from.push_back(sub);
    } 
    //std::cerr << "Made rule: " << to << " => '" << a << "', size: " << from.size() << std::endl;
  }

  bool apply(Word * w) const {
    while(w != NULL) {
      // apply rule, return true if changed.
      Word *trial = w;
      bool found = true;
      for(std::vector<std::string>::const_iterator it = from.begin(); it != from.end(); ++it, trial = trial->next) {
	if(trial == NULL || (!(*it == "*" && trial->word[0] != '<') && trial->word != *it)) {
	  //std::cerr << "Testing fail: " << from.size() << ", " << trial->word << "!=" << *it << std::endl;
	  found = false;
	  break;
	}
      }
      if(found) {
	//std::cerr << "Testing ok: " << from.size() << ": " << to << std::endl;
	w->word = to;
	w->next = trial;
	return true;
      }
      w = w->next;
    }
    return false;
  }
};

bool isWovel(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';// || c == 'y';
}

int main() {
  std::vector<Rule> rules;
  rules.push_back(Rule("<A>", "a"));
  rules.push_back(Rule("<A>", "e"));
  rules.push_back(Rule("<A>", "i"));
  rules.push_back(Rule("<A>", "o"));
  rules.push_back(Rule("<A>", "u"));
  rules.push_back(Rule("<MOD>", "ga"));
  rules.push_back(Rule("<MOD>", "ge"));
  rules.push_back(Rule("<MOD>", "gi"));
  rules.push_back(Rule("<MOD>", "go"));
  rules.push_back(Rule("<MOD>", "gu"));
  rules.push_back(Rule("<BA>", "ba"));
  rules.push_back(Rule("<BA>", "be"));
  rules.push_back(Rule("<BA>", "bi"));
  rules.push_back(Rule("<BA>", "bo"));
  rules.push_back(Rule("<BA>", "bu"));
  rules.push_back(Rule("<DA>", "da"));
  rules.push_back(Rule("<DA>", "de"));
  rules.push_back(Rule("<DA>", "di"));
  rules.push_back(Rule("<DA>", "do"));
  rules.push_back(Rule("<DA>", "du"));
  rules.push_back(Rule("<LA>", "la"));
  rules.push_back(Rule("<LA>", "le"));
  rules.push_back(Rule("<LA>", "li"));
  rules.push_back(Rule("<LA>", "lo"));
  rules.push_back(Rule("<LA>", "lu"));
  //  rules.push_back(Rule("<PREDA>", "*"));

  rules.push_back(Rule("<predstring>", "<predstring> <A> <predstring>"));
  rules.push_back(Rule("<predstring>", "<predstring> <PREDA>"));
  rules.push_back(Rule("<predstring>", "<PREDA>"));
  rules.push_back(Rule("<predname>", "<LA> <predstring>"));
  rules.push_back(Rule("<verbpred>", "<MOD> <predstring>"));

  rules.push_back(Rule("<sentence>", "<DA> <predstring>"));
  rules.push_back(Rule("<sentence>", "<predname> <BA> <predstring>"));
  rules.push_back(Rule("<sentence>", "<predname> <verbpred> <predname>"));
  rules.push_back(Rule("<sentence>", "<predname> <verbpred>"));

  while(true) {
    // Read line:
    Word start;
    bool first = true;
    Word *last;
    while(true) {
      std::string s;
      std::cin >> s;
      if(s[0] == '#')
	return 0;

      Word *w;
      if(first) {
	w = &start;
	first = false;
      }
      else {
        w = new Word;
	last->next = w;
      }
      last = w;
      const std::size_t dotAt = s.find(".");
      if(dotAt != std::string::npos) {
	w->word = s.substr(0, dotAt);
      }
      else {
	w->word = s;
      }
      // predicate transform:
      if(!isWovel(w->word[w->word.size()-1])) {
	w->word = "<predname>";
      }
      else if(w->word.size() == 5 && 
	 !isWovel(w->word[0]) &&
	 !isWovel(w->word[3]) &&
         isWovel(w->word[1]) != isWovel(w->word[2])) {
	w->word = "<PREDA>";
      }
      if(dotAt != std::string::npos) {
	break;
      }
    }
    last->next = NULL;
    // print:
    /*{
	  Word *w = &start;
	  while(w != NULL) {
	    std::cerr << w->word << " ";
	    w = w->next;
	  }
	  std::cerr << std::endl;
    }//*/

    // Apply rules:
    bool ruleApplied = true;
    while(ruleApplied) {
      ruleApplied = false;
      for(std::vector<Rule>::const_iterator it = rules.begin(); it != rules.end(); ++it) {
	if(it->apply(&start)) {
	  ruleApplied = true;
	  /*	  Word *w = &start;
	  while(w != NULL) {
	    std::cerr << w->word << " ";
	    w = w->next;
	  }
	  std::cerr << std::endl;//*/
	  break;
	}
      }
    }
    if(start.next == NULL && start.word == "<sentence>") {
      std::cout << "Good" << std::endl;
    }
    else {
      std::cout << "Bad!" << std::endl;
    }
  }
  return 0;
}
