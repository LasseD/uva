#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>

struct Title {
  std::vector<std::string> *words;
  std::string *title;

  Title() {
  }

  Title(std::string *title) {
    words = new std::vector<std::string>();
    std::transform(title->begin(), title->end(),title->begin(), ::tolower);
    std::stringstream ss(*title);

    std::string buf;
    while(ss >> buf)
      words->push_back(buf);
  }

  void print(int highlight) const {
    for(int i = 0; i < words->size(); ++i) {
      if(i != 0) {
	std::cout << " ";
      }
      std::string str = (*words)[i];
      if(i == highlight) {
	std::transform(str.begin(), str.end(),str.begin(), ::toupper);
      }
      std::cout << str;	
    }
    std::cout << std::endl;
  }

  bool operator<(const Title& b) const {
    return *title < *(b.title);
  }
};

struct TTitle {
  Title *title;
  int pos;

  void print() const {
    title->print(pos);
  }
  
  bool operator<(const TTitle& b) const {
    long long pointerA = (long long)&(*title);
    long long pointerB = (long long)&(*(b.title));
    if(pointerA < pointerB)
      return true;
    if(pointerB < pointerA)
      return false;

    return pos < b.pos;
  }
};

void print(std::set<TTitle> &set) {
  //std::cerr << "Printing " << set.size() << " items" << std::endl;
  for(std::set<TTitle>::const_iterator it = set.begin(); it != set.end(); ++it) {
    it->print();
  }
}

int main() {
  std::set<std::string> ignore;
  std::multimap<std::string,TTitle> map;
  Title titles[200];
  int titleI;

  // Read ignore words:
  char w[200];
  while(std::cin.getline(w, 12)) {
    for(int i = 0; i < 13; ++i) {
      if(!(w[i] >= 'a' && w[i] <= 'z')) {
	w[i] = '\0';
	break;
      }
    }
    std::string ws(w);
    if(ws.size() == 0)
      break;
    ignore.insert(ws);
    //std::cerr << "Ignore word: '" << ws << "'" << std::endl;
  }

  // Read titles:
  while(std::cin.getline(w, 200)) {
    std::string *ws = new std::string(w);
    Title title(ws);
    titles[titleI++] = title;
    for(int i = 0; i < title.words->size(); ++i) {
      std::string word = (*(title.words))[i];
      if(ignore.find(word) != ignore.end())
	continue;

      TTitle tt;
      tt.title = &(titles[titleI-1]);
      tt.pos = i;
      map.insert(std::make_pair(word,tt));
    }
  }

  // output:
  std::set<TTitle> set;
  std::string word;
  for(std::multimap<std::string,TTitle>::iterator it = map.begin(); it != map.end(); ++it) {
    if(set.empty() || word == it->first) {
      //std::cerr << "Pilling up for " << word << std::endl;
      set.insert(it->second);
    }
    else {
      print(set);

      word = it->first;
      set.clear();
      set.insert(it->second);
    }
  }  
  if(!set.empty())
    print(set);
  return 0;
}
