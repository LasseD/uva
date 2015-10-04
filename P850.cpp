#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
#include <ctype.h>

#define MAX_LINE_LENGTH 100

unsigned int readUInt() {
  unsigned int ret = 0;

  char w[MAX_LINE_LENGTH];
  std::cin.getline(w, MAX_LINE_LENGTH);
  for(int i = 0; isprint(w[i]); ++i) {
    if(w[i] >= '0' && w[i] <= '9')
      ret = ret * 10 + (w[i]-'0');
  }
  //std::cerr << ret << " words:" << std::endl;
  return ret;
}

bool readLine(std::vector<std::string> &lines, bool *lettersRequired) {
  char w[MAX_LINE_LENGTH];
  std::cin.getline(w, MAX_LINE_LENGTH);

  int length = 0;
  while(isprint(w[length])) {
    if(w[length] >= 'a' && w[length] <= 'z')
      lettersRequired[w[length]-'a'] = true; // Mark letter required for decryption.
    ++length;
  }
  if(length == 0)
    return false;
  w[length] = '\0';
  std::string ws(w);
  lines.push_back(ws);
  return true;
}

bool tryDecode(std::string encrypted, int *mapping, bool const * const lettersRequired) {
  std::string key = "the quick brown fox jumps over the lazy dog";
  if(encrypted.size() != key.size())
    return false;

  // Reset mapping:
  bool lettersMapped[26];
  for(int i = 0; i < 26; ++i) {
    mapping[i] = -1;
    lettersMapped[i] = false;
  }

  // Perform attempt at decryption:
  for(unsigned int i = 0; i < encrypted.size(); ++i) {
    char s = encrypted[i];
    char k = key[i];
    if((s == ' ') != (k == ' '))
      return false; // Space mismatch.
    if(k == ' ')
      continue; // space.
    if(lettersMapped[k-'a'] || mapping[s-'a'] != -1) { // must match:
      if(mapping[s-'a'] != k-'a') // Includes mapping[s-'a'] == -1
	return false; // Other char mapped
    }
    else {
      lettersMapped[k-'a'] = true;
      mapping[s-'a'] = k-'a';
    }
  }
  
  // Ensure the decryption is sufficient:
  for(int i = 0; i < 26; ++i) {
    if(lettersRequired[i] && !lettersMapped[i])
      return false;
  }
  return true;
}

int main() {
  int mapping[26];
  bool lettersRequired[26];

  unsigned int NUMBER_OF_CASES = readUInt();
  
  // Read dictionary:
  for(unsigned int i = 0; i < NUMBER_OF_CASES; ++i) {
    if(i != 0)
      std::cout << std::endl;
    for(int i = 0; i < 26; ++i) {
      lettersRequired[i] = false;
    }

    std::vector<std::string> lines;
    readLine(lines, lettersRequired);
    while(readLine(lines, lettersRequired))
      ;

    // Try all lines:
    bool ok = false;
    for(std::vector<std::string>::const_iterator it = lines.begin(); it != lines.end(); ++it) {
      const std::string &s = *it;
      if(tryDecode(s, mapping, lettersRequired)) {
	ok = true;
	break;
      }
    }    

    // Output:
    if(!ok) {
      std::cout << "No solution." << std::endl;
    }
    else {
      // Output decrypted:
      for(std::vector<std::string>::const_iterator it = lines.begin(); it != lines.end(); ++it) {
	const std::string &s = *it;
	for(unsigned int i = 0; i < s.size(); ++i) {
	  if(s[i] == ' ')
	    std::cout << ' ';
	  else
	    std::cout << (char)(mapping[s[i]-'a']+'a');
	}
	std::cout << std::endl;
      }
    }
    
  }
  return 0;
}
