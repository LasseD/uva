int main() {
  int T, R, H;
  LL pricesT[20], pricesR[20], pricesH[20];
  int TR[20*20], RH[20*20], HT[20*20];
  while(cin >> T >> R >> H) {
    // T:
    FORI(T) {
      cin >> pricesT[i];
      FORJ(R) {
	cin >> TR[20*i+j];
      }
    }
    // R:
    FORI(R) {
      cin >> pricesR[i];
      FORJ(H) {
	cin >> RH[20*i+j];
      }
    }
    // H:
    FORI(H) {
      cin >> pricesH[i];
      FORJ(T) {
	cin >> HT[20*i+j];
      }
    }
    int bestT = -1, bestR = -1, bestH = -1;    
    LL bestPrice = 0;
    FORI(T) {
      FORJ(R) {
	if(TR[20*i+j] == 1)
	  continue;
	FORK(H) {
	  if(HT[20*k+i] == 1 || RH[20*j+k] == 1)
	    continue;
	  LL sum = pricesT[i] + pricesR[j] + pricesH[k];
	  if(bestT == -1 || sum < bestPrice) {
	    bestT = i;
	    bestR = j;
	    bestH = k;
	    bestPrice = sum;
	  }
	} // K
      } // J
    } // I
    if(bestT == -1) {
      cout << "Don't get married!" << endl;
    }
    else {
      cout << bestT << " " << bestR << " " << bestH << ":" << bestPrice << endl;
    }
  }
  return 0;
} 
