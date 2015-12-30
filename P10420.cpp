#include <iostream>
#include <string>
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
  return ret;
}

void readCountryLine(int *cnt, std::map<std::string,unsigned int> &map) {
  char w[100];
  std::cin.getline(w, 100);
  for(int i = 0; true; ++i) {
    if(w[i] == ' ') {
      w[i] = '\0';
      break;
    }
  }
  std::string s(w);
  std::map<std::string,unsigned int>::iterator it = map.find(s);
  if(it == map.end()) {
    unsigned int idx = map.size();
    cnt[idx] = 1;
    map.insert(std::make_pair(s, idx));
  }
  else {
    cnt[it->second]++;
  }
}

int main() {
  int lines = readUInt();

  int cnt[2000];
  std::map<std::string,unsigned int> map;

  for(int ignore = 0; ignore < lines; ++ignore) {
    readCountryLine(cnt, map);
  }
  for(std::map<std::string,unsigned int>::const_iterator it = map.begin(); it != map.end(); ++it) {
    std::cout << it->first << " " << cnt[it->second] << std::endl;
  }
  return 0;
}
