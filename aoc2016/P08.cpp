/*
Fix input:
'x' -> ' '
'rotate row y=' -> 'y '
' by ' -> ' '
'rotate column  =' -> 'x '
 */
#define W 50
#define H 6

int main() {
  bool D[6][50];
  FORY(H) {
    FORX(W) {
      D[y][x] = false;
    }
  }
  string op;
  int a, b;
  while(cin >> op >> a >> b) {
    if(op == "rect") {
      FORY(b) {
	FORX(a) {
	  D[y][x] = true;
	}
      }
    }
    else if(op == "x") {
      FORI(b) {
	bool last = D[H-1][a];
	for(int y = H-1; y > 0; y--) {
	  D[y][a] = D[y-1][a];
	}
	D[0][a] = last;
      }
    }
    else if(op == "y") {
      FORI(b) {
	bool last = D[a][W-1];
	for(int x = W-1; x > 0; x--) {
	  D[a][x] = D[a][x-1];
	}
	D[a][0] = last;
      }
    }
    else {
      die();
    }
    int on = 0;
    FORY(H) {
      FORX(W) {
	if(D[y][x]) {
	  on++;
	  cout << '#';
	}
	else {
	  cout << '.';
	}
      }
      cout << endl;
    }
    cout << on << endl;
  } // while cin >> ...
}
