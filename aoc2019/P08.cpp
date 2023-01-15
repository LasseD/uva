#define WIDTH 25
#define HEIGHT 6

int main() {
  int numDigits[1000][10]; // layer, count digit
  int image[HEIGHT][WIDTH];
  FORY(HEIGHT) {
    FORX(WIDTH)
      image[y][x] = 2; // trans
  }
  
  GS(s);
  // Part 2:
  int idx = 0;
  while(idx < (int)s.size()) {
    FORY(HEIGHT) {
      FORX(WIDTH) {
	int pixel = s[idx++]-'0';
	if(pixel == 2)
	  continue;
	if(image[y][x] != 2)
	  continue;
	image[y][x] = pixel;
      }
    }
  }

  FORY(HEIGHT) {
    FORX(WIDTH) {
      if(image[y][x] == 1)
	cout << "#";
      else
	cout << " ";
    }
    cout << endl;
  }

  /* Part 1:
  int layer = 0;
  FORJ(10)
    numDigits[0][j] = 0;

  int layerWithMin0 = 0;
  FORUI(s.size()) {
    int digit = s[i]-'0';
    numDigits[layer][digit]++;
    if(WIDTH*HEIGHT-1 == i%(WIDTH*HEIGHT)) {
      if(numDigits[layer][0] < numDigits[layerWithMin0][0]) {
	layerWithMin0 = layer;
      }
      layer++;
      FORJ(10) {
	numDigits[layer][j] = 0;
      }
    }
  } // FORUI s.size()
  cout << "Answer 1: " << (numDigits[layerWithMin0][1]*numDigits[layerWithMin0][2]) << endl;
  */
}
