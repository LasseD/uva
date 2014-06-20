#include <iostream>
#include <vector>

#define LETTERS 26
#define LINE_SIZE 200

void rel(bool *m, const int a, const int b, bool *letters) {
  if(a == b || m[a+b*LETTERS])
    return;
  //std::cerr << "Adding " << (char)(a+'a') << "->" << (char)(b+'a') << std::endl;
  m[a+b*LETTERS] = true;
  // update for a and b:
  for(int i = 0; i < LETTERS; ++i) {
    if(!letters[i])
      continue;
    if(m[i+a*LETTERS])
      rel(m,i,b,letters);
    if(m[b+i*LETTERS])
      rel(m,a,i,letters);
  }
}

void output(int *stack, int stackI, int size, bool *m, bool *letters, int *counters) {
  /*std::cerr << "Output for stackI=" << stackI << " size=" << size << std::endl;
  std::cerr << "Stack:" << std::endl;
  for(int i = 0; i <= stackI; ++i) {
    std::cerr << (char)(stack[i]+'a');
  }
  std::cerr << std::endl;
  std::cerr << "Counters:" << std::endl;
  for(int i = 0; i < LETTERS; ++i) {
    std::cerr << " " << counters[i];
  }
  std::cerr << std::endl;//*/

  // Find all zeroes and iterate.
  std::vector<int> zeroes;
  for(int i = 0; i < LETTERS; ++i) {
    if(letters[i] && counters[i] == 0)
      zeroes.push_back(i);
  }
  // For each letter in zeroes, remove it from counters and recurse:
  for(std::vector<int>::const_iterator it = zeroes.begin(); it != zeroes.end(); ++it) {
    int letter = *it;
    stack[stackI++] = letter;
    if(stackI == size) {
      // output stack:
      for(int i = 0; i < size; ++i) {
	std::cout << (char)(stack[i]+'a');
      }
      std::cout << std::endl;
    }
    else {
      // decrease counters
      --counters[letter]; // -1
      for(int i = 0; i < LETTERS; ++i) {
	if(m[letter+i*LETTERS])
	  --counters[i];
      }
      output(stack, stackI, size, m, letters, counters);
      ++counters[letter]; // -0
      for(int i = 0; i < LETTERS; ++i) {
	if(m[letter+i*LETTERS])
	  ++counters[i];
      }
    }
    stackI--;
  }
}

int main() {
  bool letters[LETTERS];
  bool m[LETTERS*LETTERS]; // a+b*LETTERS true if a < b specified
  int counters[LETTERS]; // in
  char line[LINE_SIZE];

  bool first = true;
  while(std::cin.getline(line, LINE_SIZE)) {
    // Reset state:
    for(int i = 0; i < LETTERS; ++i) {
      letters[i] = false;
      counters[i] = 0;
    }
    for(int i = 0; i < LETTERS*LETTERS; ++i) {
      m[i] = false;
    }

    // Find eligible letters:
    int numberOfLetters = 0;
    for(int i = 0; i < LINE_SIZE; ++i) {
      char c = line[i];
      if(c == ' ')
	continue;
      else if(c >= 'a' && c <= 'z') {
	letters[c-'a'] = true;
	++numberOfLetters;
      }
      else {
	break; // done line.
      }
    }

    // Fill m:
    std::cin.getline(line, LINE_SIZE);
    int size = 0;
    while(line[size] == ' ' || (line[size] >= 'a' && line[size] <= 'z'))
      ++size;
    //std::cerr << "End with: '" << line[size] << "': " << (int)line[size] << std::endl;
    ++size;
    //std::cerr << (size/4) << " relations: size=" << size << std::endl;
    for(int i = 0; i < size; i+=4) {
      int a = line[i]-'a';
      int b = line[i+2]-'a';
      //std::cerr << "Original relation: " << (char)(a+'a') << "->" << (char)(b+'a') << std::endl;
      rel(m,a,b,letters);
    }

    /*for(int a = 0; a < LETTERS; ++a) {
      if(!letters[a])
	continue;
      for(int b = 0; b < LETTERS; ++b) {
	if(!letters[b])
	  continue;
	if(m[a+b*LETTERS])
	  std::cerr << " " << (char)(a+'a') << "->" << (char)(b+'a') << std::endl;
      }
    }//*/

    // Output:
    // Make in-counters for all letters, queue up when in-counter i 0.
    if(!first)
      std::cout << std::endl;
    first = false;
    int counters[LETTERS] = {0};
    for(int a = 0; a < LETTERS; ++a) {
      if(!letters[a])
	continue;
      for(int b = 0; b < LETTERS; ++b) {
	if(!letters[b])
	  continue;
	if(m[a+b*LETTERS])
	  ++counters[b];
      }
    }
    int stack[20];
    output(stack, 0, numberOfLetters, m, letters, counters);
  }
}
