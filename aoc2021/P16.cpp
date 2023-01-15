string s; int idx = 0, sumVersions = 0;
bool bits[10000];

int get(int size) {
  int ret= 0;
  FORI(size) {
    ret = 2*ret + (bits[idx++] ? 1 : 0);
  }
  return ret;
}

LL readPacket() {
  int version = get(3);
  sumVersions += version;
  int type = get(3);
  cout << "Type: " << type << endl;
  if(type == 4) { // Read number:
    LL val = 0;
    while(true) {
      bool last = get(1) == 0;
      FORI(4) {
	val = 2*val + get(1);
      }
      if(last)
	break;
    }
    cout << "Read literal " << val << endl;
    return val;
  }
  else {
    int lti = get(1);
    if(lti == 0) {
      int to = get(15) + idx;
      LL ret;
      if(type == 0)
	ret = 0;
      else if(type == 1)
	ret = 1;
      else if(type == 2)
	ret = 9999999999999;
      else if(type == 3)
	ret = -9999999999999;
      else if(type == 5)
	return readPacket() > readPacket() ? 1 : 0;
      else if(type == 6)
	return readPacket() < readPacket() ? 1 : 0;
      else if(type == 7)
	return readPacket() == readPacket() ? 1 : 0;	  
	  
      while(idx < to) {
	cout << "Reading sub-packet because " << idx << " < " << to << endl;
	LL val = readPacket();
	if(type == 0) { // SUM!
	  ret += val;
	}
	else if(type == 1) { // PRODUCT
	  ret *= val;
	}
	else if(type == 2) { // MIN
	  ret = min(ret, val);
	}
	else if(type == 3) { // MAX
	  ret = max(ret, val);
	}
      }
      return ret;
    }
    else {
      int numPackets = get(11);
      LL ret;
      if(type == 0)
	ret = 0;
      else if(type == 1)
	ret = 1;
      else if(type == 2)
	ret = 9999999999999;
      else if(type == 3)
	ret = -9999999999999;
      else if(type == 5)
	return readPacket() > readPacket() ? 1 : 0;
      else if(type == 6)
	return readPacket() < readPacket() ? 1 : 0;
      else if(type == 7)
	return readPacket() == readPacket() ? 1 : 0;	  	  
      
      FORI(numPackets) {
	LL val = readPacket();
	if(type == 0) { // SUM!
	  ret += val;
	}
	else if(type == 1) { // PRODUCT
	  ret *= val;
	}
	else if(type == 2) { // MIN
	  ret = min(ret, val);
	}
	else if(type == 3) { // MAX
	  ret = max(ret, val);
	}
      }
      return ret;
      
    }
  }
}

int main() {
  GS(s);
  cout << "Read string of length " << s.size() << endl;
  // Build bits;
  FORUI(s.size()) {
    char c = s[i];
    int x;
    if(c >= 'A' && c <= 'F')
      x = 10 + c-'A';
    else
      x = c-'0';
    int mask = 1 << 3;
    FORJ(4) {
      bits[idx++] = (x&mask) > 0;
      mask >>=1;
    }
  }
  idx = 0; // Ready to read bits
  
  LL answer2 = readPacket();

  cout << "Answer 1: " << sumVersions << endl;
  cout << "Answer 2: " << answer2 << endl;
}
