#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>

unsigned int readUInt() {
  unsigned int ret = 0;

  char w[20];
  std::cin.getline(w, 20);
  for(int i = 0; i < 20; ++i) {
    if(!(w[i] >= '0' && w[i] <= '9'))
      break;
    ret = ret * 10 + (w[i]-'0');
  }
  //std::cerr << ret << " words:" << std::endl;
  return ret;
}

void readWordIntoDictionary(std::vector<std::string> *dictionary) {
  char w[20];
  std::cin.getline(w, 20);

  int i = 0;
  for(; i < 20; ++i) {
    if(!(w[i] >= 'a' && w[i] <= 'z')) {
      w[i] = '\0';
      break;
    }    
  }
  std::string ws(w);
  //std::cerr << " " << ws << std::endl;
  dictionary[i-1].push_back(ws);
}

bool readLine(std::vector<std::string> &line) {
  line.clear();
  char w[100];
  if(!std::cin.getline(w, 100))
    return false;
    
  int start = 0;
  for(int i = 0; i < 100; ++i) {
    if(w[i] >= 'a' && w[i] <= 'z')
      continue;
    bool done = w[i] != ' ';
    w[i] = '\0';
    std::string ws(&w[start]);
    line.push_back(ws);
    start = i+1;
    if(done)
      break;
  }
  return true;
}

bool tryUseWordToEncode(const std::string &fromLine, const std::string &fromDictionary, int *mapping, bool *lettersMapped) {
  //std::cerr << "  " << fromLine << " -> " << fromDictionary << ": ";
  int newMapping[26];
  bool newLettersMapped[26];
  for(int i = 0; i < 26; ++i) {
    newMapping[i] = mapping[i];
    newLettersMapped[i] = lettersMapped[i];
  }

  // Try to match (early return on fail):
  for(unsigned int i = 0; i < fromLine.size(); ++i) {
    char a = fromLine[i];
    char b = fromDictionary[i];
    if(newMapping[a-'a'] == -1) {
      if(newLettersMapped[b-'a']) {
	//std::cerr << "Letter " << b << " already mapped at position " << i << std::endl;
	return false; // New letter already mapped.
      }
      newMapping[a-'a'] = b-'a';
      newLettersMapped[b-'a'] = true;
    }
    else if(newMapping[a-'a']+'a' != b) {
      //std::cerr << "Mismatch (" << b << "!=" << ((char)(newMapping[a-'a']+'a')) << ") at position " << i << std::endl;
      return false; // Mapping mismatch
    }
  }

  // Update mapping:
  for(int i = 0; i < 26; ++i) {
    mapping[i] = newMapping[i];
    lettersMapped[i] = newLettersMapped[i];
  }
  //std::cerr << "OK!" << std::endl;
  return true;
} 

bool runForWord(unsigned int wordIndex, const std::vector<std::string> &line, int *mapping, bool *lettersMapped, std::vector<std::string> *dictionary) {
  if(wordIndex == line.size())
    return true;
  // Try all words of proper length:
  unsigned int wordLength = line[wordIndex].size();
  for(std::vector<std::string>::const_iterator it = dictionary[wordLength-1].begin(); it != dictionary[wordLength-1].end(); ++it) {
    int newMapping[26];
    bool newLettersMapped[26];
    for(int i = 0; i < 26; ++i) {
      newMapping[i] = mapping[i];
      newLettersMapped[i] = lettersMapped[i];
    }
    
    if(tryUseWordToEncode(line[wordIndex], *it, newMapping, newLettersMapped) &&
       runForWord(wordIndex+1, line, newMapping, newLettersMapped, dictionary)) {
      for(int i = 0; i < 26; ++i) {
	mapping[i] = newMapping[i];
	lettersMapped[i] = newLettersMapped[i];
      }
      return true;
    }
  }
  return false;
}

int main() {
  int mapping[26];
  bool lettersMapped[26];

  std::vector<std::string> dictionary[16]; // dictionary[0] with words of length 1, 

  // Read dictionary size:
  unsigned int SIZE_DICTIONARY = readUInt();

  // Read dictionary:
  for(unsigned int i = 0; i < SIZE_DICTIONARY; ++i) {
    readWordIntoDictionary(dictionary);
  }

  // Read ignore words: 
  std::vector<std::string> line;
  while(readLine(line)) {
    for(int i = 0; i < 26; ++i) {
      mapping[i] = -1;
      lettersMapped[i] = false;
    }
    // Compute:
    bool ok = runForWord(0, line, mapping, lettersMapped, dictionary);
    
    // Output:
    if(!ok) {
      // Output stars:
      for(std::vector<std::string>::const_iterator it = line.begin(); it != line.end(); ++it) {
	if(it != line.begin())
	  std::cout << " ";
	const std::string &s = *it;
	for(unsigned int i = 0; i < s.size(); ++i) {
	  std::cout << "*";
	}
      }
      std::cout << std::endl;
    }
    else {
      // Output decrypted:
      for(std::vector<std::string>::const_iterator it = line.begin(); it != line.end(); ++it) {
	if(it != line.begin())
	  std::cout << " ";
	const std::string &s = *it;
	for(unsigned int i = 0; i < s.size(); ++i) {
	  std::cout << (char)(mapping[s[i]-'a']+'a');
	}
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
