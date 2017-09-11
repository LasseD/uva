bool attacks(PI a, PI b) {
  return (a.XX+a.YY == b.XX+b.YY) || (a.XX-a.YY == b.XX-b.YY);
}

void place(int i, PI *placed, int n, int k, int &cnt, PI lastPos) {
  if(i == k) {
    ++cnt;
    return;
  }
  for(int y = lastPos.YY; y < n; ++y) {
    for(int x = (y == lastPos.YY) ? lastPos.XX+1 : 0; x < n; ++x) {
      bool allOK = true;
      FORJ(i) {
	if(attacks(placed[j], PI(x,y))) {
	  allOK = false;
	  break;
	}
      }
      if(allOK) {
	placed[i] = PI(x,y);
	place(i+1, placed, n, k, cnt, PI(x,y));
      }
    }
  }
}

int main() {
  /*
  PI bishops[16];
  for(int n = 8; n <= 8; ++n) {    
    cout << "int n" << n << "[" << 2*n-2 << "] = {";
    for(int k = 1; k <= 2*n-2; ++k) {
      if(k > 1)
	cout << ", ";
      int cnt = 0;
      int bishopI = 0;
      // Place k bishops on an n x n board:
      place(bishopI, bishops, n, k, cnt, PI(-1,0));
      cout << cnt << endl;
    }
    cout << "};" << endl;
  }//*/

  int n1[2] = {1, 0};
  int n2[4] = {4, 4, 0, 0};
  int n3[6] = {9, 26, 26, 8, 0, 0};
  int n4[8] = {16, 92, 232, 260, 112, 16, 0, 0};
  int n5[10] = {25, 240, 1124, 2728, 3368, 1960, 440, 32, 0, 0};
  int n6[12] = {36, 520, 3896, 16428, 39680, 53744, 38368, 12944, 1600, 64, 0, 0};
  int n7[14] = {49, 994, 10894, 70792, 282248, 692320, 1022320, 867328, 389312, 81184, 5792, 128, 0, 0};
  int n8[14] = {64
, 1736
, 26192
, 242856
, 1444928
, 5599888
, 14082528
, 22522960
, 22057472
, 12448832
, 3672448
, 489536
, 20224
, 256
};
  int *ret[8] = {n1, n2, n3, n4, n5, n6, n7, n8};
  while(true) {
    int NN, KK;
    cin >> NN>>KK;
    //cerr << NN << " " << KK << ": ";
    if(KK == 0) {
      if(NN == 0)
	return 0;
      cout << 1 << endl;
    }
    else if(NN == 1) {
      cout << (KK == 1 ? 1 : 0) << endl;
    }
    else if(KK > 2*NN-2) {
      cout << 0 << endl;
    }
    else
      cout << ret[NN-1][KK-1] << endl;
  }
}
