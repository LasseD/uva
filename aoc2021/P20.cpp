string mesh, image;
int width, height = 0, allOn = false;

bool get(int x, int y) {
  if(x < 0 || y < 0 || x >= width || y >= height)
    return allOn;
  return image[width*y + x] == '#';
}

void transform() {
  int w2 = width+2, h2 = height+2;
  stringstream ss;
  FORY(h2) {
    FORX(w2) {
      // Find index:
      int idx = 0;
      for(int yy = y-1; yy <= y+1; yy++) {
	for(int xx = x-1; xx <= x+1; xx++) {
	  idx <<= 1;
	  if(get(xx-1, yy-1))
	    idx++;
	}
      }
      ss << mesh[idx];
    }
  }
  image = ss.str();
  width = w2;
  height = h2;
  if(mesh[0] == '#')
    allOn = !allOn;
}

void print() {
  int on = 0;
  cout << endl;
  FORY(height) {
    FORX(width) {
      if(image[y*width + x] == '#') {
	cout << '#';
	on++;
      }
      else {
	cout << '.';
      }
    }
    cout << endl;
  }
  cout << endl << "Size " << width << " x " << height << " Total on: " << on << endl;
}

int main() {
  string s;
  getline(cin, mesh);
  stringstream ss;
  getline(cin, s); // Empty line.
  while(getline(cin, s)) {
    width = (int)s.size();
    ss << s;
    height++;
  }
  image = ss.str();
  //cout << "Single line: " << image << endl;
  cout << "Initial image:" << endl;
  print();

  FORI(50) { // 2 for part 1, 50 for part 2
    transform();
    cout << "After iteration " << (i+1) << ":" << endl;
    print();
  }
}
